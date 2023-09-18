#include "../lib/SRTNP.h"

static queue_object* SRTNP_queue;
void queue_sort_SRTNP(queue_object* queue); 
void queue_insert_after_SRTNP(queue_object* queue, process* to_insert);

process* SRTNP_tick (process* running_process){
    if(running_process==NULL || running_process->time_left==0){
        queue_sort_SRTNP(SRTNP_queue);
        running_process = queue_poll(SRTNP_queue); 
        if(running_process==NULL){
            return NULL; 
        }
    } else {//
        queue_sort_SRTNP(SRTNP_queue);
            process* compare_process = queue_peek(SRTNP_queue); 
            if(compare_process != NULL){
                if(compare_process->time_left < running_process->time_left){ //running process wird verdrängt
                    queue_add(running_process, SRTNP_queue);
                    running_process = queue_poll(SRTNP_queue);
                }
            //}
        }
        //running_process->time_left--;
    }
    running_process->time_left--;  //

    return running_process;
}

int SRTNP_startup(){
    SRTNP_queue = new_queue(); 
    if(SRTNP_queue==NULL){
        return 1;
    }
    return 0;
}

process* SRTNP_new_arrival(process* arriving_process, process* running_process){
    if(arriving_process!= NULL && running_process != NULL){
        //checken, ob wir verdrängen müssen
        if(arriving_process->time_left<running_process->time_left){
            queue_add(running_process, SRTNP_queue); 
            return arriving_process;
        } else {
            queue_add(arriving_process, SRTNP_queue); 
        }
    } else if(arriving_process!=NULL){
        queue_add(arriving_process, SRTNP_queue); 
    }
    return running_process;
}

void SRTNP_finish(){
    free_queue(SRTNP_queue); 
}

void queue_sort_SRTNP(queue_object* queue) {
    if(queue==NULL || queue->next == NULL) {
        return; 
    }
    queue_object* sorted_queue = new_queue(); 
    if(sorted_queue == NULL) {
        return; 
    }
    process* temp_sort_element; 
    while(queue->next!=NULL){
        temp_sort_element= queue_poll(queue); 
        if(queue_peek(sorted_queue)==NULL){
            queue_add(temp_sort_element, sorted_queue); 
        } else {
            queue_object* current = sorted_queue; 
            queue_object* nxt = current->next; 
            process* nxt_process = nxt->object; 
            int flag = 0; 

            while(nxt!=NULL&&flag==0){
                //if(!(nxt_process->time_left>temp_sort_element->time_left)){
                if(temp_sort_element->time_left<nxt_process->time_left){
                    flag=1;
                }
                current=nxt;
                nxt=current->next;
            }
            queue_insert_after_SRTNP(current, temp_sort_element);
        }
    }
    while(sorted_queue->next!=NULL){
        queue_add(queue_poll(sorted_queue), queue);
    }
    free_queue(sorted_queue); 
}

void queue_insert_after_SRTNP(queue_object* queue, process* to_insert){
    queue_object* inserter = malloc(sizeof(queue_object)); 
    inserter->object = to_insert; 

    inserter->next=queue->next;
    queue->next=inserter; 
}
