/*
Motor 1 & 3: Right 
Logic 1 - P9_12 - GPIO1[28]
Logic 2 - P9_15 - GPIO1[16]
PWM 1 - P9_23 - GPIO1[17]
Motor 2 & 4: Left
Logic 1 - P8_7 - GPIO2[2]
Logic 2 - P8_8 - GPIO2[3]
PWM 1 - P8_9 - GPIO2[5]

Read an input pin using memory map
Encoder r - A: P8_11
	    B: P8_12
Encoder l - A: P8_15
	    B: P8_16
*/
#include <fcntl.h>

#define HIGH 1
#define LOW 0

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <native/task.h>
#include <native/timer.h>
#include <rtdk.h>
#include <signal.h>
#include <native/queue.h>
#include <native/sem.h>
#include <math.h>

#define OE_ADDR 0x134
#define GPIO_DATAOUT 0x13C
#define GPIO_DATAIN 0x138
#define GPIO0_ADDR 0x44E07000
#define GPIO1_ADDR 0x4804C000
#define GPIO2_ADDR 0x481AC000
#define GPIO3_ADDR 0x481AF000

#define period1 1000000//800000
#define period2 1000000//800000
#define period_gtg 1000000

#define duty1 period1*0.25
#define duty2 period2*0.25

#define period 100000

#define MAX_BUF 64

RT_TASK rEncoder_task;
RT_TASK lEncoder_task;
RT_TASK Odo_task;
RT_TASK rMotor_task;
RT_TASK lMotor_task;
RT_TASK stop_rMotor;
RT_TASK stop_lMotor;
RT_TASK gtg_task;

RT_SEM rSem;
RT_SEM lSem;
RT_SEM xSem;
RT_SEM ySem;
RT_SEM tSem;

int rtick = 0;
int ltick = 0;
double x = 0;
double y = 0;
double theta = 0;

//robot dimension
#define R .030
#define L .185
#define N 1000/3 //Ticks per revolution
#define pi 3.14159
#define m_per_tick 2*pi*R/N
#define v 0.15 //in m/s
#define Kp 4
#define Ki 0.01
#define Kd 0.01

const int x_g = 1;
const int y_g = 1;

void gtg(void *arg){

	double u_x, u_y, theta_g;
	double e_k = 0;
	double  e_P = 0;
	double e_D = 0;
	double e_I = 0;
	double  e_k_1 = 0;
	double w = 0;
	double E_k = 0;

	RTIME prev, now, dt;

	rt_task_set_periodic(NULL, TM_NOW, period_gtg); 
	prev = rt_timer_read();	

	while(1){
		rt_task_wait_period(NULL);

		u_x = x_g - x;
		u_y = y_g - y; 
		theta_g = atan2(u_y, u_x);

		rt_printf("Goal angle is: %lf\n", theta_g);

		e_k = theta_g - theta;
		e_k = atan2(sin(e_k), cos(e_k));
		rt_printf("Error in heading is: %lf\n", e_k);
	 	now  = rt_timer_read();
		dt = now-prev;
		prev = now;

		e_P = e_k;
		e_I = E_k + e_k*dt;
		e_D = (e_k - e_k_1)/dt;

		w = Kp*e_P + Ki*e_I + Kd*e_D;
		E_k = e_I;
		e_k_1 = e_k;
		rt_printf("calcualted the error");
		rt_printf("v and w are: %lf, %lf \n", v, w);
		//[vel_r_d, vel_l_d] = uni_to_diff(v, w);
	}
}

void stoprMotor(void *arg){
	int fd = open("/dev/mem",O_RDWR | O_SYNC);
    	ulong* pinconf1 =  (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO1_ADDR);	
	pinconf1[OE_ADDR/4] &= pinconf1[OE_ADDR/4] &= (0xFFFFFFFF ^ ((1 << 28)|(1<<16)|(1<<17))); 
	//configure logic pins
	rt_printf("stop r motor\n");
     	pinconf1[GPIO_DATAOUT/4]  &= ~(1 << 28); //clear pin  P9_12
     	pinconf1[GPIO_DATAOUT/4]  &= ~(1 << 16); // clear pin P9_15
        pinconf1[GPIO_DATAOUT/4]  &= ~(1 << 17); // clear pin P9_15
}

void stoplMotor(void *arg)
{
        int fd = open("/dev/mem",O_RDWR | O_SYNC);
        ulong* pinconf2 =  (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO2_ADDR);     
        pinconf2[OE_ADDR/4] &= pinconf2[OE_ADDR/4] &= (0xFFFFFFFF ^ ((1<<2)|(1 << 3)|(1<<5))); 
        //configure logic pins
	rt_printf("stop l motor\n");
        pinconf2[GPIO_DATAOUT/4]  &= ~(1 << 2); //set pin  P8_7
     	pinconf2[GPIO_DATAOUT/4]  &= ~(1 << 3); // clear pin P8_8
        pinconf2[GPIO_DATAOUT/4] &= ~(1<<5);
}
void rMotor(void *arg)
{
        RT_TASK *curtask;
        RT_TASK_INFO curtaskinfo;
	RTIME now, previous;
	long MAX = 0;

	int fd = open("/dev/mem",O_RDWR | O_SYNC);
    	ulong* pinconf1 =  (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO1_ADDR);	
	pinconf1[OE_ADDR/4] &= pinconf1[OE_ADDR/4] &= (0xFFFFFFFF ^ ((1 << 28)|(1<<16)|(1<<17))); 
	//configure logic pins
     	pinconf1[GPIO_DATAOUT/4]  |= (1 << 28); //set pin  P9_12
     	pinconf1[GPIO_DATAOUT/4]  &= ~(1 << 17); // clear pin P9_15
	rt_task_set_periodic(NULL, TM_NOW, period1);
        rt_printf("Controling Right Motors!\n");
//	previous = rt_timer_read();
	while (1){
                rt_task_wait_period(NULL);
		previous = rt_timer_read();
		pinconf1[GPIO_DATAOUT/4] |= (1 << 17); //PWM on pin P9_23
		rt_task_sleep(duty1);
		pinconf1[GPIO_DATAOUT/4] &= ~(1 << 17); //toggle pin
//		rt_printf("right Motor PWM, time taken:%ld. %06ld ms\n", (long)(now-previous)/1000000, (long)(now-previous)%1000000);
		now = rt_timer_read();
		if((long)((now - previous)%1000000) > MAX){
			MAX = (long)((now - previous)%1000000) ;
		}
//		rt_printf("WCET Right Motor: %ld \n", MAX);
		//previous = now;
	}
}

void lMotor(void *arg)
{
        RT_TASK *curtask;
        RT_TASK_INFO curtaskinfo;
        RTIME now, previous;
	long MAX = 0;
        int fd = open("/dev/mem",O_RDWR | O_SYNC);
        ulong* pinconf2 =  (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO2_ADDR);     
        pinconf2[OE_ADDR/4] &= pinconf2[OE_ADDR/4] &= (0xFFFFFFFF ^ ((1<<2)|(1 << 3)|(1<<5))); 
        //configure logic pins
        pinconf2[GPIO_DATAOUT/4]  |= (1 << 2); //set pin  P8_7
     	pinconf2[GPIO_DATAOUT/4]  &= ~(1 << 3); // clear pin P8_8
        rt_task_set_periodic(NULL, TM_NOW, period2);
        rt_printf("Controling Left Motors!\n");
        //previous = rt_timer_read();
        while (1){
                rt_task_wait_period(NULL);
                previous = rt_timer_read();
                pinconf2[GPIO_DATAOUT/4] |= (1 << 5); //PWM on pin P8_9
                rt_task_sleep(duty2);
                pinconf2[GPIO_DATAOUT/4] &= ~(1 << 5); //toggle pin
  //              rt_printf("Left Motor PWM, time taken:%ld. %06ld ms\n", (long)(now-previous)/1000000, (long)(now-previous)%1000000); 
                now = rt_timer_read();
		if((long)((now - previous)%1000000) > MAX){
                        MAX = (long)((now - previous)%1000000) ;
                }
//                rt_printf("WCET Left Motor: %ld \n", MAX);

		//previous = now;
        }
}


void rEncoder(void *arg)
{
	int rEnc, lEnc, fd;
        char buf[MAX_BUF];
        char val[4]; //stores 4 digits ADC value
        snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/48302000.epwmss/48302180.eqep/position");
	RTIME now, previous;
	long MAX = 0;
        rt_task_set_periodic(NULL, TM_NOW, period);
        rt_printf("Reading right Encoder!\n");

        while (1){
                rt_task_wait_period(NULL);
		previous = rt_timer_read();
		fd = open(buf, O_RDONLY); //Open ADC as read only

        	if(fd < 0){
                	perror("Problem opening right Encoder");
        	}

        	read(fd, &val, 4); //read upto 4 digits 0-1799
        	close(fd);

        	rEnc = atoi(val); //return integer value
		
		rt_sem_p(&rSem, 0);
		rtick = rEnc;
		rt_sem_v(&rSem);
//        	rt_printf("right Encoder ticks: %d\n", rtick);
		now = rt_timer_read();
		if((long)((now - previous)%1000000) > MAX){
			MAX = (long)((now - previous)%1000000) ;
		}
		//rt_printf("WCET Right Motor: %ld \n", MAX);
//		rt_queue_write(&rqueue, rEnc, sizeof(rEnc), Q_NORMAL);
	}
	return;
}


void lEncoder(void *arg)
{
        int rEnc, lEnc, fd;
        char buf[MAX_BUF];
        char val[4]; //stores 4 digits ADC value
        snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/48304000.epwmss/48304180.eqep/position");
        RTIME now, previous;
        long MAX = 0;
        rt_task_set_periodic(NULL, TM_NOW, period);
        rt_printf("Reading Left Encoder!\n");

        while (1){
                rt_task_wait_period(NULL);
                previous = rt_timer_read();
                fd = open(buf, O_RDONLY); //Open ADC as read only

                if(fd < 0){
                        perror("Problem opening ADC");
                }

                read(fd, &val, 4); //read upto 4 digits 0-1799
                close(fd);

                lEnc = atoi(val); //return integer value
                rt_sem_p(&lSem, 0);
                ltick = lEnc;
                rt_sem_v(&lSem);

  //              rt_printf("Left Encoder ticks: %d\n", ltick);
                now = rt_timer_read();
                if((long)((now - previous)%1000000) > MAX){
                        MAX = (long)((now - previous)%1000000) ;
                }
    //            rt_printf("WCET left Motor: %ld \n", MAX);
        	//rt_queue_write(&lqueue, lEnc, sizeof(lEnc), Q_NORMAL);

        }
        return;
} 


void Odo(void *arg){

	double rtick_prev = 0;
	double ltick_prev = 0;
	double dtick_r = 0;
	double dtick_l = 0;
	char r_mesg[40], l_mesg[40];
	int r_tick, l_tick;

        double Dr, Dc, Dl, x_dt, y_dt, theta_dt, x_new, y_new, theta_new;

	Dr = Dc = Dl = 0;
	x = y = theta = 0;
	x_new=y_new=theta_new = 0;
	x_dt = y_dt = theta_dt = 0;

	rt_task_set_periodic(NULL, TM_NOW, period);	

	while(1){
		rt_task_wait_period(NULL);
	
//		rt_queue_read(&rqueue, r_mesg, sizeof(r_mesg), TM_INFINITE);
//		rt_queue_read(&lqueue, l_mesg, sizeof(l_mesg), TM_INFINITE);

//		r_tick = atoi(r_mesg);
//		l_tick = atoi(l_mesg);

		r_tick = rtick;
		l_tick = ltick;
		//rt_printf("int data: %d \n", l_tick);
		//rt_printf("data r : %d \n", r_tick);

		dtick_r = r_tick - rtick_prev;
                dtick_l = l_tick - ltick_prev;

		Dr = m_per_tick*dtick_r;
                Dl = m_per_tick*dtick_l;
		Dc = (Dr+Dl)/2;

		x_dt = Dc*cos(theta);
		y_dt = Dc*sin(theta);
		theta_dt = (Dr-Dl)/L;

		theta_new = theta + theta_dt;
		x_new = x + x_dt;
		y_new = y + y_dt;

		rtick_prev = r_tick;
		ltick_prev = l_tick;
		
		rt_sem_p(&xSem, 0);
		x = x_new;
		rt_sem_v(&xSem);
		rt_sem_p(&ySem, 0);
		y = y_new;
		rt_sem_v(&ySem);
		rt_sem_p(&tSem, 0);
		theta = theta_new;
		rt_sem_v(&tSem);

	//	rt_printf("Robot pose (x, y, theta) is: %lf, %lf, %lf\n", x, y, theta);
		

	}

}

void init_xenomai(){
	rt_print_auto_init(1);
        mlockall(MCL_CURRENT|MCL_FUTURE);
}

void startup(){

	//rt_queue_create(&rqueue, "rQueue", QUEUE_SIZE, 40, Q_FIFO);
        //rt_queue_create(&lqueue, "lQueue", QUEUE_SIZE, 40, Q_FIFO);
	
	rt_sem_create(&rSem, "rSem", 1, S_FIFO);
        rt_sem_create(&lSem, "lSem", 1, S_FIFO);

	rt_sem_create(&xSem, "xSem", 1, S_FIFO);
        rt_sem_create(&ySem, "ySem", 1, S_FIFO);
        rt_sem_create(&tSem, "tSem", 1, S_FIFO);


        rt_task_create(&rEncoder_task, "rEnc Task", 0, 50, 0);
        rt_task_start(&rEncoder_task, &rEncoder, 0);

       
        rt_task_create(&lEncoder_task, "lEnc Task", 0, 50, 0);
      	rt_task_start(&lEncoder_task, &lEncoder, 0);
 
        rt_task_create(&Odo_task, "Odo Task", 0, 60, 0);
        rt_task_start(&Odo_task, &Odo, 0);
 
        rt_task_create(&gtg_task, "GTG Task", 0, 70, 0);
        rt_task_start(&gtg_task, &gtg, 0);

    	char str[10];
	sprintf(str, "rMotor");
	rt_task_create(&rMotor_task, str, 0, 50, 0);
	rt_task_start(&rMotor_task, &rMotor, 0);

        sprintf(str, "lMotor"); 
        rt_task_create(&lMotor_task, str, 0, 50, 0);
        rt_task_start(&lMotor_task, &lMotor, 0);

        sprintf(str, "StoplMotor"); 
        rt_task_create(&stop_lMotor, str, 0, 90, 0);

        sprintf(str, "StoprMotor"); 
        rt_task_create(&stop_rMotor, str, 0, 90, 0);

	//rt_sem_broadcast(&rsem);

}

void catch_signal(int sig){
	//empty signal handler to allow execution of cleanup code
}
void wait_for_ctrl_c(){
	signal(SIGTERM, catch_signal);
	signal(SIGINT, catch_signal);

	//wait for CTRL+C
	pause();
}

void cleanup(){
        rt_task_delete(&rEncoder_task);
        rt_task_delete(&lEncoder_task);
        rt_task_delete(&Odo_task);
	rt_task_delete(&gtg_task);

        rt_task_start(&stop_lMotor, &stoplMotor, 0);
        rt_task_start(&stop_rMotor, &stoprMotor, 0);

        rt_task_delete(&lMotor_task);
        rt_task_delete(&rMotor_task);
	rt_task_delete(&stop_lMotor);
	rt_task_delete(&stop_rMotor);

//	rt_task_delete(&rEncoder_task);
//        rt_task_delete(&lEncoder_task);
//	rt_task_delete(&Odo_task);

}


int main(int argc, char* argv[])
{
	double timeD;
	time_t begin, end;

	printf("\n Press Ctrl+c to quit\n\n");

	init_xenomai();

	startup();
	begin = time(NULL);
	while(timeD < 3){
		end = time(NULL);
		timeD = (end - begin);	
	}
	//wait_for_ctrl_c();

	cleanup();

	printf("\n Ending program!\n\n");

}
