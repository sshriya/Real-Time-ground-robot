#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/nman.h>
#include <native/task.h>
#include <native/timer.h>

#include <rtdk.h>
RT_TASK helloWorld_task;

void helloWorld(void *arg){
	RT_TASK *currtask;
	RT_TASK_INFO curtaskinfo;

	rt_printf("Hello World!\n");

	curtask = rt_task_self();
	rt_task_inquire(curtask, &curtaskinfo);

	rt_printf("Task name : %s \n", curttaskinfo.name);
}

int main(int argc, char* argv[]){
	char str[10];
	//Perform auto-init of rt-print buffers
	rt_print_auto_init(1);
	//Lock memory for this program
	mlockall(MCL_CURRENT|MCL_FUTURE);

	rt_printf("Start task\n");

	/* Arguments: &task, name, stack size, (0-default)
			priority, mode(FPU, start, suspend,..)
	*/

	sprintf(str, "hello");
	rt_task_create(&helloWorld_task, str, 0, 50, 0);

	/* Arguments: &task, task function, function argument */
	rt_task_start(&helloWorld_task, &helloWorld, 0);
}
