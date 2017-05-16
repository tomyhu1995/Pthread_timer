#ifndef _PTHREAD_TIMER_H
#define _PTHREAD_TIMER_H

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "linked_list.h"
#include "funclog.h"

#define LOOP List

typedef enum {
	PT_SUCCESS = 1,
	PT_FAIL_REGIST = -1,
	PT_FAIL_START = -2,
	PT_FAIL_STOP = -3,
	PT_FAIL_UNREGIST = -4,
	PT_FAIL_RUN = -5
}PTimer_Status_Code;

typedef enum{
	ALARM_ONCE = 1,
	PERIODIC = 2
}PTIMER_TYPE;

typedef enum{
	RUN = 1,
	NEW_A_LOOP = 2
}PTIMER_LOOP_CMD;

typedef struct{
	int timer_id;
	PTIMER_TYPE timer_type;
	time_t timer_length;
	void *cb;
	pthread_t thread;
}PTimer_node;

extern int timer_id_count;

PTimer_Status_Code PTimer_Regist_Timer(LOOP *head, PTimer_node *new_timer);
PTimer_Status_Code PTimer_Start_Timer(LOOP *head, PTimer_node *wanted_timer);
PTimer_Status_Code PTimer_Stop_timer(LOOP *head, PTimer_node *wanted_timer);
PTimer_Status_Code PTimer_Unregist_timer(LOOP *head, PTimer_node *wanted_timer);
PTimer_Status_Code PTimer_Loop(LOOP *head, PTIMER_LOOP_CMD cmd);
PTimer_Status_Code PTimer_Print_Timer(LOOP *loop);
static void main_loop();

#endif