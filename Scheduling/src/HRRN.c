#include "../lib/HRRN.h"

static queue_object* HRRN_queue;
void queue_sort_HRRN(queue_object* queue);
void queue_insert_after_HRRN(queue_object* queue, HRRN_process* to_insert);
//You can add more global variables and structs here

process* HRRN_tick (process* running_process){
    if (running_process==NULL || running_process->time_left==0){
        HRRN_process* HRRN_running = queue_poll(HRRN_queue); 
        running_process = HRRN_running->this_process; 
        free(HRRN_running);

    }
    if (running_process!=NULL){
        running_process->time_left--;
    }
    queue_object* temp = HRRN_queue; 
    while(temp->next!=NULL) {
        if(temp->object!=NULL){
        HRRN_process* temp_HRRN = temp->object; 
        temp_HRRN->waiting_time++;
        }
    temp=temp->next;

    }
    return running_process;
}

int HRRN_startup(){
    HRRN_queue = new_queue();
    if(HRRN_queue==NULL){
        return 1;
    }
    return 0;
}

process* HRRN_new_arrival(process* arriving_process, process* running_process){
    if(arriving_process!=NULL){
        HRRN_process* hrrn_arriving = malloc(sizeof(HRRN_process));
        hrrn_arriving->this_process = arriving_process;
        hrrn_arriving->waiting_time = 0; 
        hrrn_arriving->rr = 1; 
        queue_add(hrrn_arriving, HRRN_queue); 
    }
    queue_sort_HRRN(HRRN_queue);
    return running_process; //nicht verdrängend
}

void HRRN_finish(){
    free_queue(HRRN_queue);
}

void queue_sort_HRRN(queue_object* queue){
    if(queue == NULL || queue->next==NULL){
        return;
    }
    queue_object* sorted_queue = new_queue();
    if(sorted_queue ==NULL){
        return;
    }
    HRRN_process* temp_sort_element;

    while(queue->next!=NULL) {
        int flag = 0; 
        float wait = 0;
        int serving = 0; 
        float serv = 0;
        float rr_value = 0; 

        temp_sort_element = queue_poll(queue); 
        wait = (float) temp_sort_element->waiting_time;
        process* temp_sort_process = temp_sort_element->this_process;
        serving = (int) temp_sort_process->time_left;
        serv = (float) serving;
        rr_value = (wait+serv)/serv; 
        temp_sort_element->rr=rr_value;



        if(queue_peek(sorted_queue) == NULL){
            queue_add(temp_sort_element, sorted_queue); 
        } else {
            queue_object* current = sorted_queue; 
            queue_object* nxt = current->next; 
            HRRN_process* nxt_HRRN_process = nxt->object;
            
            wait=(float) nxt_HRRN_process->waiting_time; 
            process* nxt_process = nxt_HRRN_process->this_process;
            serving = (int)nxt_process->time_left;
            serv =(float) serving;
            rr_value = (wait+serv)/serv; 

            nxt_HRRN_process->rr=rr_value; 
                while(nxt!=NULL && flag==0){
                    if(temp_sort_element ==NULL){
                        return;
                    }
                    if(temp_sort_element->rr>=nxt_HRRN_process->rr){
                        flag=1; 
                    }
                    current=nxt; 
                    nxt=current->next;
                }
            queue_insert_after_HRRN(current, temp_sort_element);
        }
    }
    while(sorted_queue->next!=NULL){
        queue_add(queue_poll(sorted_queue), queue); 
    }
    free(sorted_queue); 
}

void queue_insert_after_HRRN(queue_object* queue, HRRN_process* to_insert){
    queue_object* inserter = malloc(sizeof(queue_object)); 
    inserter->object = to_insert; 

    inserter->next=queue->next;
    queue->next=inserter; 
}