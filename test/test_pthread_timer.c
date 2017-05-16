#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "funclog.h"
#include "pthread_timer.h"

void timeout_call_back1()
{
    printf("=== your time is up 1===\n");
    // doing some other stuff
}

void timeout_call_back2()
{
    printf("=== your time is up 2===\n");
    // doing some other stuff
}

void timeout_call_back3()
{
    printf("=== your time is up 3===\n");
    // doing some other stuff
}



int main(int argc, char const *argv[])
{
	LOOP loop;
	PTimer_node A ={
		.timer_id = 8,
		.timer_type = ALARM_ONCE,
		.timer_length = 5,
		.cb= &timeout_call_back1
	};

	PTimer_node B ={
		.timer_id = 7878,
		.timer_type = ALARM_ONCE,
		.timer_length = 3,
		.cb= timeout_call_back2
	};

	PTimer_node C ={
		.timer_id = 9487,
		.timer_type = PERIODIC,
		.timer_length = 1,
		.cb= timeout_call_back3
	};

	PTimer_Loop(&loop, NEW_A_LOOP);
	
	PTimer_Regist_Timer(&loop, &A);
	PTimer_Start_Timer(&loop, &A);

	PTimer_Regist_Timer(&loop, &B);
	PTimer_Start_Timer(&loop, &B);

	PTimer_Regist_Timer(&loop, &C);
	PTimer_Start_Timer(&loop, &C);

	PTimer_Loop(&loop, RUN);
	PTimer_Print_Timer(&loop);

	
	return 0;
}