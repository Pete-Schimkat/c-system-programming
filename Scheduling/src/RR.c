#include "../lib/RR.h"

static queue_object* RR_queue;
static int time_interval = 0;
static int same_process_time=0;
static process* currently_running = NULL; 

process* RR_tick (process* running_process){
    if (running_process==NULL || running_process->time_left==0){
        running_process=queue_poll(RR_queue);
        if(running_process==NULL){
            return NULL;
        }
        currently_running=running_process;
        same_process_time=1;
        running_process->time_left--;
        return running_process;
    }
    if (running_process!=NULL){
        running_process->time_left--;
        if(same_process_time==time_interval){
            queue_add(running_process, RR_queue);
            currently_running = queue_poll(RR_queue);
            same_process_time = 1;
            return currently_running;
        } else {
            same_process_time++;
            return running_process;
        }
    }
    
    return running_process;
}

int RR_startup(int quantum){
    RR_queue=new_queue();
    if (RR_queue==NULL){
        return 1;
    }
    time_interval = quantum;
    return 0;
}


process* RR_new_arrival(process* arriving_process, process* running_process){
    if(arriving_process!=NULL){
        queue_add(arriving_process, RR_queue);
    }
    return running_process;
}


void RR_finish(){
    free_queue(RR_queue);
}
