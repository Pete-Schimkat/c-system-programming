#include "../lib/MLF.h"
#include <stdio.h>

static queue_object** MLF_queues;
static queue_object* first_RR_queue; 
static queue_object* second_RR_queue; 
static queue_object* third_RR_queue; 
static queue_object* last_FCFS_queue; 
static int first_quantum = 1;
static int second_quantum = 3; 
static int third_quantum = 9;
static int curr_quantum = 1; 
int is_empty(queue_object* queue);
//LCFS_quantum = process->time_left;
//You can add more global variables here

process* MLF_tick (process* running_process){
    //Aktueller Prozess ist  durch, neuer gebraucht
    if(running_process==NULL ||running_process->time_left==0) {
        if(is_empty(first_RR_queue) == 0){
            curr_quantum = first_quantum;
            running_process=queue_poll(first_RR_queue); 
        } else if(is_empty(second_RR_queue) == 0){
            curr_quantum = second_quantum; 
            running_process=queue_poll(second_RR_queue); 
        } else if(is_empty(third_RR_queue) == 0){
            curr_quantum = third_quantum; 
            running_process=queue_poll(third_RR_queue);
        } else if(is_empty(last_FCFS_queue) == 0) {
            running_process = queue_poll(last_FCFS_queue); 
            if(running_process==NULL){
                    return NULL; 
            }
            curr_quantum = running_process->time_left;
        }   
        if(running_process==NULL){
            return NULL; 
        }
        //Aktueller Prozess ist noch nicht durch, Zeitscheibe könnte aufgebraucht sein
    } else if(running_process!=NULL && running_process->time_left!=0){
        if(curr_quantum==0) { //Zeitscheibe aufgebraucht
            if(is_empty(first_RR_queue) == 0){
                curr_quantum = first_quantum;
                queue_add(running_process,second_RR_queue);
                running_process=queue_poll(first_RR_queue); 
            } else if(is_empty(second_RR_queue) == 0){
                curr_quantum = second_quantum; 
                queue_add(running_process,third_RR_queue);
                running_process=queue_poll(second_RR_queue); 
            } else if(is_empty(third_RR_queue) == 0){
                curr_quantum = third_quantum; 
                queue_add(running_process,last_FCFS_queue);
                running_process=queue_poll(third_RR_queue);
            } else if (is_empty(last_FCFS_queue) == 0){
                running_process = queue_poll(last_FCFS_queue); 
                if(running_process==NULL){
                    return NULL; 
                }
                curr_quantum = running_process->time_left;
            }   
            if(running_process==NULL){
                return NULL; 
            }
        }
    }
    curr_quantum--;
    if (running_process!=NULL){
        running_process->time_left--;
    }
    return running_process;
}

/**
 *  Is called once at the beginning. 
 * @result 0 if everything was fine. Any other number if there was an error.
 */
int MLF_startup(){
    first_RR_queue = new_queue(); 
    second_RR_queue = new_queue();
    third_RR_queue = new_queue();
    last_FCFS_queue = new_queue(); 
    if(first_RR_queue == NULL || second_RR_queue == NULL || third_RR_queue == NULL ||last_FCFS_queue == NULL){
        return 1;
    }
    return 0;
}

process* MLF_new_arrival(process* arriving_process, process* running_process){
    if(arriving_process != NULL) {
        queue_add(arriving_process, first_RR_queue); 
    }
    return running_process;
}

/**
 * is called once after the all processes were handled. */
void MLF_finish(){
    free_queue(first_RR_queue);
    free_queue(second_RR_queue);
    free_queue(third_RR_queue);
    free_queue(last_FCFS_queue);
}

//1 wenn queue empty, 0 wenn nicht empty, -1 wenn queue nicht existiert
int is_empty(queue_object* queue){
    if(queue==NULL) {
        return -1;
    }
    if(queue->next ==NULL){
        return 1;
    }
    return 0; 
}

