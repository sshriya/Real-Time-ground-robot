/*
 Read an input pin using memory map
Encoder r - A: P8_11
	    B: P8_12
Encoder l - A: P8_15
	    B: P8_16
*/
#include <fcntl.h>
#define OE_ADDR 0x134
#define GPIO_DATAOUT 0x13C
#define GPIO_DATAIN 0x138
#define GPIO0_ADDR 0x44E07000
#define GPIO1_ADDR 0x4804C000
#define GPIO2_ADDR 0x481AC000
#define GPIO3_ADDR 0x481AF000

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

#define period 1000000

RT_TASK rEnc_task;
RT_TASK lEnc_task;
RT_TASK lOdo_task;

//robot dimension
#define R 30
#define L 185
#define N 1000/3 //Ticks per revolution
#define pi 3.14159
#define m_per_tick 2*pi*R/N

#define QUEUE_SIZE 255
RT_QUEUE rqueue;
//RT_QUEUE lqueue;


float rtick = 0;
float ltick = 0;

void rEnc(void *arg)
{
 	int i = 0;
	int rtick_prev = 0;
	int d_tick_r = 0;
    	int r_last = LOW;
    	int inr = 0;
    	int inrB = 0;
    	char logicA = '1';
    	char logicB = '2';
	char msg[10];

    	int fd = open("/dev/mem",O_RDWR | O_SYNC);
    	ulong* pinconf1 =  (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO1_ADDR);
    	//configure encoder pins as input
    	pinconf1[OE_ADDR/4]  |= ((1<<13)|(1 << 12)); //P8_11, P8_12, P8_15, P8_16   

        rt_task_set_periodic(NULL, TM_NOW, period);
        rt_printf("Reading right Encoder!\n");

        while (1){
                rt_task_wait_period(NULL);

                if(pinconf1[GPIO_DATAIN/4] & (1 << 13)){
                        inr = HIGH;
                }else{
                        inr = LOW;
                }


		if((r_last == LOW)&&(inr == HIGH)){
			if(pinconf1[GPIO_DATAIN/4] & (1 << 12)) {
        	                inrB = HIGH;
                	}else{
                        	inrB = LOW;
                	}

			if(inrB == LOW){
				rtick--;
			}else{
				rtick++;
			}
		}
		r_last = inr;
		rt_printf("Right ticks: %d \n", rtick);
		//d_tick_r = rtick - rtick_prev;
		//send to odometry task
		//rt_queue_write(&rqueue, d_tick_r, sizeof(d_tick_r), Q_NORMAL);
        }
	return;
}

void lEnc(void *arg)
{
        int i = 0;
        int lPose = 0;
        int r_last = LOW;
        int inr = 0;
        int inrB = 0;
        char logicA = '1';
        char logicB = '2';
        int fd = open("/dev/mem",O_RDWR | O_SYNC);
        ulong* pinconf1 =  (ulong*) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO1_ADDR);
        //configure encoder pins as input
        pinconf1[OE_ADDR/4]  |= ((1<<15)|(1<<14)); //P8_11, P8_12, P8_15, P8_16   

        rt_task_set_periodic(NULL, TM_NOW, period);
        rt_printf("Reading Left Encoder!\n");

        while (1){
                rt_task_wait_period(NULL);

                if(pinconf1[GPIO_DATAIN/4] & (1 << 15)){
                        inr = HIGH;
                }else{
                        inr = LOW;
                }

		 if((r_last == LOW)&&(inr == HIGH)){
                        if(pinconf1[GPIO_DATAIN/4] & (1 << 14)) {
                                inrB = HIGH;
                        }else{
                                inrB = LOW;
                        }

                        if(inrB == LOW){
                                ltick--;
                        }else{
                                ltick++;
                        }
                }
                //r_last = inr;
                rt_printf("Left ticks: %d \n", ltick);
		
                //send to odometry task
//                rt_queue_write(&lqueue, lPose, sizeof(lPose), Q_NORMAL);

        }
        return;
}

void lOdo(void *arg){

	float Dr;
	int rtick_prev = 0;
	int ltick_prev = 0;
	int dtick_r = 0;
	int dtick_l = 0;


	rt_task_set_periodic(NULL, TM_NOW, period);	

	while(1){
		rt_task_wait_period(NULL);
//		rt_queue_read(&rqueue, r_tick, sizeof(r_tick), TM_INFINITE);
		//rt_queue_read(&lqueue, ltick, sizeof(ltick), TM_INFINITE);
	
		rt_printf("rdiff is: %d \n", rtick);
		sleep(0.1);
                rt_printf("ldiff is: %d \n", ltick);

		//dtick_r = rtick - rtick_prev;
                //dtick_l = ltick - ltick_prev;

		//Dr = m_per_tick*dtick_r;
	}

}

void init_xenomai(){
	rt_print_auto_init(1);
        mlockall(MCL_CURRENT|MCL_FUTURE);
}

void startup(){

	rt_queue_create(&rqueue, "rQueue", QUEUE_SIZE, 40, Q_FIFO);
  //      rt_queue_create(&lqueue, "lQueue", QUEUE_SIZE, 10, Q_FIFO);
        //&task, name, stack size (0 - default), priority, mode 
        rt_task_create(&rEnc_task, "rEnc Task", 0, 50, 0);
        //&task, task function, function argument
        rt_task_start(&rEnc_task, &rEnc, 0);

        //&task, name, stack size (0 - default), priority, mode 
//        rt_task_create(&lEnc_task, "lEnc Task", 0, 50, 0);
        //&task, task function, function argument
//        rt_task_start(&lEnc_task, &lEnc, 0);


        //&task, name, stack size (0 - default), priority, mode 
        rt_task_create(&lOdo_task, "lOdo Task", 0, 60, 0);
        //&task, task function, function argument
        rt_task_start(&lOdo_task, &lOdo, 0);



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
	rt_task_delete(&rEnc_task);
        rt_task_delete(&lEnc_task);

}


int main(int argc, char* argv[])
{
	printf("\n Press Ctrl+c to quit\n\n");

	init_xenomai();

	startup();

	wait_for_ctrl_c();

	cleanup();

	printf("\n Ending program!\n\n");

}
