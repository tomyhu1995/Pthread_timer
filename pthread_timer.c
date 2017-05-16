#include "pthread_timer.h"


PTimer_Status_Code PTimer_Regist_Timer(LOOP *head, PTimer_node *new_timer){
    log_debug("create new timer");
    log_debug("timer_id = %d", new_timer->timer_id);
    ListAdd(head, new_timer);
    return PT_SUCCESS;
}

static void* start_timer(void *args){
    /* function pointer */
    void (*finish_function)();

    PTimer_node timer = *((PTimer_node *)args);
    printf("thread ID : %ld, go to sleep for %d\n", pthread_self(), timer.timer_length);

    finish_function = timer.cb;

    if(timer.timer_type == ALARM_ONCE){
        sleep(timer.timer_length);
        /* call the cb to inform the user time is out */
        (*finish_function)();
        pthread_exit(NULL);
    }else if(timer.timer_type == PERIODIC){
        while(1){
            sleep(timer.timer_length);
            /* call the cb to inform the user time is out */
            (*finish_function)();
        }
    }
}

PTimer_Status_Code PTimer_Start_Timer(LOOP *head, PTimer_node *wanted_timer){
    pthread_t thread;

    PTimer_node *resualt_timer = (PTimer_node*)ListSearch(head, wanted_timer, sizeof(PTimer_node));
    if(resualt_timer != NULL){
        if(resualt_timer->cb != NULL){
           if(pthread_create(&thread, NULL, start_timer, (void *) resualt_timer)){
                log_debug("=== Failed to create thread");
                return PT_FAIL_START;
            }else{
                log_debug("=== Create thread");
                wanted_timer->thread = thread;
                return PT_SUCCESS;
            } 
        }else{
            log_debug("call back function is null");
            return PT_FAIL_START;
        }
    }else{
        log_debug("Fail to search wanted_timer");
        return PT_FAIL_START;
    }
}

PTimer_Status_Code PTimer_Stop_timer(LOOP *head, PTimer_node *wanted_timer){

    PTimer_node *resualt_timer = (PTimer_node*)ListSearch(head, wanted_timer, sizeof(PTimer_node));
    if(resualt_timer != NULL){
        if(pthread_cancel(wanted_timer->thread) == 0){
            log_debug("Stop timer id %d success", wanted_timer->timer_id);
            return PT_SUCCESS;
        }else{
            log_debug("Fail to stop timer id %d", wanted_timer->timer_id);
            return PT_FAIL_STOP;
        }
    }else{
        log_debug("Fail to search wanted_timer");
        return PT_FAIL_STOP;
    }

}

PTimer_Status_Code PTimer_Unregist_timer(LOOP *head, PTimer_node *wanted_timer){

}

void Timer_printer(PTimer_node *p){
    if(p->timer_type == ALARM_ONCE){
        log_debug("Timer id :%d, length = %ld, timer type = ALARM_ONCE", p->timer_id, p->timer_length);
    }else if(p->timer_type == PERIODIC){
        log_debug("Timer id :%d, length = %ld, timer type = PERIODIC", p->timer_id, p->timer_length);
    }
    
}

PTimer_Status_Code PTimer_Print_Timer(LOOP *loop){
    log_debug("Enter %s", __FUNC__);
    ListNode *p = NULL;
    for (p = loop->head; p != NULL; p=p->next){
        Timer_printer((PTimer_node *)p->obj);
    }
    return PT_SUCCESS;
}

PTimer_Status_Code PTimer_Loop(LOOP *head, PTIMER_LOOP_CMD cmd){
    ListNode *p = NULL;
    pthread_t thread;
    
    switch(cmd){
        case RUN:
            pthread_create(&thread, NULL, main_loop, NULL);
            for (p = head->head; p != NULL; p=p->next){
                PTimer_node *tmp = (PTimer_node*)(p->obj);
                if(pthread_join(tmp->thread, NULL) != 0){
                    log_debug("Fail to pthread_join");
                    return PT_FAIL_RUN;
                }
            }
            pthread_join(thread, NULL);
            break;
        case NEW_A_LOOP:
            log_debug("New a loop");
            ListNew(head);
            break;
    }

    return PT_SUCCESS;
}

static void main_loop(){
    log_debug("-----------------------Hi I am your real main loop--------------------\n");
    long long int i = 0;

    while(1){
        i++;
        //printf("%d\n", i);
        if(i == 30000000000){
            log_debug("I am steal here ~~");   
        }
    }
}

