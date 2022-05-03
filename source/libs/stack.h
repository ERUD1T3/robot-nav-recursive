//Copyright to Josias Moukpe, 2019

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_SIZE 64

typedef struct node {
    /*
    * Node for single linked Stack structure
    */
    char data[MAX_STR_SIZE]; //data contained in node
    //char* data;
    struct node* next; //pointer to next node

} Node;

typedef struct {
    /*
    * Single Linked Stack struct
    */ 
   int size; //overall size of Single Linked Stack
   Node* head; //pointer to first element in the Stack

} Stack;


//Methods to operate on Stack
Stack* initStack(void); //initialize data member of the Stack
void printStack(Stack* stack); //print all elements in the Stack
char* front(Stack* stack);
void push(Stack* stack, char* data); //stack push operation
char* pop(Stack* stack); //stack pop operation




/***********************************
 * IMPLEMENTATION
 ***********************************/ 

char* pop(Stack* stack) {
    /*
    * Pop the head of the stack 
    * Return the data in the popped node
    */
    char tmp[MAX_STR_SIZE];

    Node* to_del = stack->head;
    strcpy(tmp, to_del->data);
    stack->head = to_del->next;
    free(to_del);
    --stack->size;
    return tmp;
}

void push(Stack* stack, char* data) {
    /*
    * Push a new node with data at the top of the stack
    */
   Node* new_node = (Node*)malloc(sizeof(Node));
   strcpy(new_node->data, data);
   new_node->next = stack->head;
   stack->head = new_node;
   ++stack->size;
}

char* front(Stack* stack) {
    /*
    * Get the data at the head of the Stack
    */ 
    return stack->head->data;
}

/*
char* getAt(Stack* Stack, const int index) {
    return (traverse(Stack, index)->data);
}
*/

Stack* initStack(void) {
    /*
    *   initialize size to 0 and head to NULL
    */
   Stack* stack = (Stack*)malloc(sizeof(Stack));
   stack->size = 0;
   stack->head = NULL;
   return stack;
}

void destroy(Stack* stack) {
    /*
    * Destroy a stack
    */
   while(stack->size != 0) pop(stack);
   free(stack);
}

void printStack(Stack* stack) {
    /*
    * print all elements in the Stack
    */
   if(stack == NULL || stack->size == 0 ) {
       printf("empty Stack\n");
       return;
   }
   printf("[");
   Node* tmp = stack->head;

   if(stack->size != 0) {
       while(tmp != NULL) {
           printf(" %s,", tmp->data);
           tmp = tmp->next;
       }
   }
   printf(" ]\n");
}



#endif