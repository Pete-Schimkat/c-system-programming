#include "../lib/queue.h"
#include <stdlib.h>
#include <stdio.h>

int queue_add(void* new_obejct, queue_object* queue){
    queue_object* new_queue_object = malloc(sizeof(queue_object));
    if(new_queue_object == NULL){
        return 1;
    }
    new_queue_object->object = new_obejct; 
    new_queue_object->next = queue->next;
    queue->next=new_queue_object;
    return 0;
}

void* queue_poll(queue_object* queue){
    if(queue->next==NULL){
        return NULL;
    }
    queue_object* prev_object = NULL;
    queue_object* temp_queue_object = queue;
    while(temp_queue_object->next != NULL) {
        prev_object = temp_queue_object;
        temp_queue_object = temp_queue_object->next;
    }
    void* value = temp_queue_object->object;
    prev_object->next = NULL;
    free(temp_queue_object);

    return value;
}

queue_object* new_queue(){
    queue_object* new_queue = malloc(sizeof(queue_object));
    if(new_queue == NULL){
        return NULL;
    }
    new_queue->object=NULL;
    new_queue->next=NULL;
    return new_queue;
}


void free_queue(queue_object* queue){
    while(queue->next!=NULL){
        queue_poll(queue);
    }
    free(queue->next);
    free(queue);
}

void* queue_peek(queue_object* queue){
    queue_object* temp_queue_object = queue;
    if(queue == NULL){
        return NULL;
    }
    if(queue->next ==NULL){
        return NULL;
    }
    while(temp_queue_object->next != NULL) {
        temp_queue_object = temp_queue_object->next;
    }
    void* value = temp_queue_object->object;
    return value;
}