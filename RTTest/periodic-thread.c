#include <unistd.h>
#include <pthread.h>

#ifndef __KERNEL__
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#else
#include <linux/types.h>
#define printf printk
#endif

#include "periodic_tasks.h"
#include "task_bodies.h"

struct th_info {
  int period;
  void (*body)(void);
};

static void *thread_body(void *p)
{
    struct periodic_task *t;
    struct th_info *t_i = p;

    t = start_periodic_timer(2000000, t_i->period);
    if (t == NULL) {
        printf("Start Periodic Timer");

        return NULL;
    }

    while(1) {
        wait_next_activation(t);
        t_i->body();
    }

    return NULL;
}

static pthread_t *create_threads(void)
{
    static struct th_info t_1, t_2, t_3;
    static pthread_t id[3];
    int err;

    t_1.body = task1;
    t_1.period = 20000;
    err = pthread_create(&id[0], NULL, thread_body, &t_1);
    if (err) {
        printf("PThread Create");
    }

    t_2.body = task2;
    t_2.period = 50000;
    err = pthread_create(&id[1], NULL, thread_body, &t_2);
    if (err) {
        printf("PThread Create");
    }

    t_3.body = task3;
    t_3.period = 70000;
    err = pthread_create(&id[2], NULL, thread_body, &t_3);
    if (err) {
        printf("PThread Create");
    }

    return id;
}

static void kill_threads(pthread_t *id)
{
    int i;

    for (i = 0; i < 3; i++) {
        pthread_cancel(id[i]);
    }
    for (i = 0; i < 3; i++) {
        pthread_join(id[i], NULL);
    }

}

#ifndef __KERNEL__
int main(int argc, char *argv[])
{
    pthread_t *id;

    id = create_threads();
    sleep(20);

    kill_threads(id);

    return 0;
}
#else
static pthread_t *id;

static int __init program_start(void)
{
  id = create_threads();

  return 0;
}

static void __exit program_end(void)
{
  kill_threads(id);
}

module_init(program_start);
module_exit(program_end);
#endif
