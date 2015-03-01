#include <time.h>
#ifndef __KERNEL__
#include <stdio.h>
#include <stdint.h>
#else
#include <linux/types.h>
#define printf printk
#define fflush(a)
#endif

#include "task_bodies.h"

void task1(void)
{
  int i,j;
 
  for (i=0; i<3; i++) {
    for (j=0; j<1000; j++) ;
    printf("1");
    fflush(stdout);
  }
}

void task2(void)
{
  int i,j;

  for (i=0; i<5; i++) {
    for (j=0; j<10000; j++) ;
    printf("2");
    fflush(stdout);
  }
}

void task3(void)
{
  static uint64_t previous;
  uint64_t t;
  struct timespec ts;

  if (previous == 0) {
    clock_gettime(CLOCK_REALTIME, &ts);
    previous = ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000L;
  }

  clock_gettime(CLOCK_REALTIME, &ts);
  t = ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000L;
  printf("\tT: %Lu\n", t - previous);
  previous = t;
}

