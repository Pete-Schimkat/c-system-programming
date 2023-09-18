#include "../lib/LCFS.h"

static queue_object* LCFS_queue;
static void* queue_poll_newest(queue_object* queue){
    if(queue->next==NULL){
        return NULL;
    }
    queue_object* first_element = queue->next;
    void* value = first_element->object; 

    queue->next=first_element->next;
    free(first_element); 
    return value;  


}

int LCFS_startup(){
    LCFS_queue=new_queue();
    if (LCFS_queue==NULL){
        return 1;
    }
    return 0;
}

process* LCFS_tick (process* running_process){
    if (running_process==NULL || running_process->time_left==0){
        running_process=queue_poll_newest(LCFS_queue);
    }
    if (running_process!=NULL){
        running_process->time_left--;
    }

    return running_process;
}


process* LCFS_new_arrival(process* arriving_process, process* running_process){
    if(arriving_process!=NULL){
        queue_add(arriving_process, LCFS_queue);
    }
    return running_process;
}

void LCFS_finish(){
    free_queue(LCFS_queue);
}
