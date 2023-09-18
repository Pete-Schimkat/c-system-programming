#include "../lib/PRIOP.h"
#include <stdio.h>

static queue_object* PRIOP_queue;
void queue_sort_PRIOP(queue_object* queue);
void* queue_peek_highest(queue_object* queue); 
void queue_insert_after(queue_object* queue, process* to_insert);

process* PRIOP_tick (process* running_process){
    if (running_process==NULL || running_process->time_left==0){
        queue_sort_PRIOP(PRIOP_queue);
        running_process=queue_poll(PRIOP_queue);
        if(running_process==NULL){
            return NULL;
        }
    }
    if (running_process!=NULL){
        running_process->time_left--;
    }

    return running_process;
}

int PRIOP_startup(){
    PRIOP_queue = new_queue();
    if(PRIOP_queue==NULL){
        return 1;
    }
    return 0;
}

process* PRIOP_new_arrival(process* arriving_process, process* running_process){
    if(arriving_process!=NULL && running_process!=NULL){
        if(arriving_process->priority>running_process->priority){
            queue_add(running_process,PRIOP_queue);
            return arriving_process;
        } else {
            queue_add(arriving_process, PRIOP_queue);
        }
    } else if(arriving_process!=NULL){
        queue_add(arriving_process,PRIOP_queue);
    }
    return running_process;
}

void PRIOP_finish(){
    free_queue(PRIOP_queue);
}

void queue_sort_PRIOP(queue_object* queue){
    if(queue == NULL || queue->next==NULL){
        return;
    }
    queue_object* sorted_queue = new_queue();
    if(sorted_queue ==NULL){
        return;
    }
    process* temp_sort_element;
    while(queue->next != NULL){
        temp_sort_element = queue_poll(queue);
        if(queue_peek(sorted_queue) == NULL){
            queue_add(temp_sort_element, sorted_queue);
        } else {
            queue_object* current = sorted_queue;
            queue_object* nxt = current->next;
            process* nxt_process = nxt->object; 
            int flag = 0; 

            while(nxt!=NULL && flag == 0){
                if(temp_sort_element->priority>=nxt_process->priority){
                        flag = 1; 
                    }
                current=nxt; 
                nxt = current->next;
                }
            queue_insert_after(current, temp_sort_element);
        }
    }
    while(sorted_queue->next!=NULL){
        queue_add(queue_poll(sorted_queue), queue); 
    }
    free(sorted_queue);
    //free(temp_sort_element);
}

void* queue_peek_highest(queue_object* queue){
    if(queue == NULL){
        return NULL;
    }
    if(queue->next ==NULL){
        return NULL;
    }
    return queue->next; 
}

void queue_insert_after(queue_object* queue, process* to_insert){
    queue_object* inserter = malloc(sizeof(queue_object)); 
    inserter->object = to_insert; 

    inserter->next=queue->next;
    queue->next=inserter; 
}
