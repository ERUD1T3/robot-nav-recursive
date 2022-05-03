//Copyright to Josias Moukpe, 2019

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_SIZE 64

typedef struct node {
    /*
    * Node for single linked Queue structure
    */
    char data[MAX_STR_SIZE]; //data contained in node
    //char* data;
    struct node* next; //pointer to next node

} Node;

typedef struct {
    /*
    * Single Linked Queue struct
    */ 
   int size; //overall size of Single Linked Queue
   Node* head; //pointer to first element in the Queue
   Node* tail; //pointer to the last element in the Queue

} Queue;


//Methods to operate on Queue
Queue* initQueue(void); //initialize data member of the Queue
void printQueue(Queue* queue); //print all elements in the Queue
char* front(Queue* queue);
void enqueue(Queue* queue, char* data); //queue enqueue operation
char* dequeue(Queue* queue); //queue dequeue operation




/***********************************
 * IMPLEMENTATION
 ***********************************/ 

char* dequeue(Queue* queue) {
    /*
    * Pop the head of the queue 
    * Return the data in the dequeueped node
    */
    char tmp[MAX_STR_SIZE];

    Node* to_del = queue->head;
    strcpy(tmp,to_del->data);
    queue->head = to_del->next;
    free(to_del);
    --queue->size;
    return tmp;
}

void enqueue(Queue* queue, char* data) {
    /*
    * Push a new node with data at the top of the queue
    */
   Node* new_node = (Node*)malloc(sizeof(Node));
   strcpy(new_node->data, data);
   new_node->next = NULL;
   if(queue->size == 0) {
    queue->tail = new_node;
    queue->head = new_node;
   } 
   else { 
    queue->tail->next = new_node;
    queue->tail = new_node;
   }
   ++queue->size;
}

char* front(Queue* queue) {
    /*
    * Get the data at the head of the Queue
    */ 
    return queue->head->data;
}

/*
char* getAt(Queue* Queue, const int index) {
    return (traverse(Queue, index)->data);
}
*/

Queue* initQueue(void) {
    /*
    *   initialize size to 0 and head to NULL
    */
   Queue* queue = (Queue*)malloc(sizeof(Queue));
   queue->size = 0;
   queue->head = NULL;
   queue->tail = NULL;
   return queue;
}

void destroy(Queue* queue) {
    /*
    * Destroy a queue
    */
   while(queue->size != 0) dequeue(queue);
   free(queue);
}

void printQueue(Queue* queue) {
    /*
    * print all elements in the Queue
    */
   if(queue == NULL || queue->size == 0 ) {
       printf("empty Queue\n");
       return;
   }
   printf("[");
   Node* tmp = queue->head;

   if(queue->size != 0) {
       while(tmp != NULL) {
           printf(" %s,", tmp->data);
           tmp = tmp->next;
       }
   }
   printf(" ]\n");
}



#endif