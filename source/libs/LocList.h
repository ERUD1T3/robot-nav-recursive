//Copyright to Josias Moukpe, 2019

#ifndef LOCLIST_H
#define LOCLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 64

typedef unsigned int uint;

typedef struct
{
    /* data */
    char loc_name[MAX_STR_SIZE];
    uint loc_X; //x coordinate of a location 
    uint loc_Y; //y coordinate of a location

} location;

typedef struct locnode {
    /*
    * LocNode for single linked list structure
    */
    location* data; //data contained in node
    struct locnode* next; //pointer to next node

} LocNode;

typedef struct {
    /*
    * Single Linked List struct
    */ 
   int size; //overall size of Single Linked List
   LocNode* head; //pointer to first element in the list

} LocList;


//Methods to operate on list
LocList* initLocList(void); //initialize data member of the list
void destroy(LocList* List); //destroy a list and free all pointers
LocNode* traverse(LocList* List, const uint index);  //return the pointer to the node previous to the node at index 
void insert(LocList* List,const int index,location* data); //insert a node with payload data at position index
location* suppress(LocList* List,const int index);  //deletes a node at position index
void pushfront(LocList* List,location* data); //insert node at the front of the list
void pushback(LocList* List,location* data); //insert node at the end of the list
location* popfront(LocList* List);  //delete node at the back of the list
location* popback(LocList* List);  //delete node at the front of the list
void printlist(LocList* List); //print all elements in the list
location* getAt(LocList* List, const int index); //get the data at index 
void copy(LocList* dest, LocList* src); //retunns copy of the List
void reset(LocList* List); //clears a list of its element
LocList* reverseList(LocList* List); //reverse a list

LocList* reverseList(LocList* List) {
    LocList* reversed = initLocList();
    for(uint i = 0; i < List->size; ++i)
    pushfront(reversed, getAt(List, i));
    //free(List);
    return reversed;
}


location* getAt(LocList* List, const int index) {
    /*
    * Obtain the data contained in node at index 
    */
    return (traverse(List, index)->data);
}

void copy(LocList* dest, LocList* src) {
    //LocList* list_copy = initLocList();
    //list_copy->size = 0;
    for(uint i = 0; i < src->size; ++i) {
        pushback(dest, getAt(src, i));
    }
    //return list_copy;
}

LocList* initLocList(void) {
    /*
    *   initialize size to 0 and head to NULL
    */
   LocList* List = (LocList*)malloc(sizeof(LocList));
   List->size = 0;
   List->head = NULL;
   return List;
}

void destroy(LocList* List) {
    /*
    * Deallocate all the allocated memory
    */
    while(List->size != 0) popback(List);
    free(List);
}


void reset(LocList* List) {
    /*
    * Clear the list of all its elements
    */
    if(List == NULL) return;
    while(List->size != 0) popback(List);
}

void printlist(LocList* List) {
    /*
    * print all elements in the list
    */
   if(List == NULL || List->size == 0 ) {
       printf("empty list\n");
       return;
   }
   printf("[");
   LocNode* tmp = List->head;

   if(List->size != 0) {
       while(tmp != NULL) {
           printf(" %s,", tmp->data->loc_name);
           tmp = tmp->next;
       }
   }
   printf(" ]\n");
}

LocNode* traverse(LocList* List, const uint index) {
    /*
    * give an index N, traverse() traverse the list until N and return pointer to N-1
    * O(n)
    */
   
    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n"); 
        return NULL;
    }

    //case 2: index is not present
    if(index < 0 || index >= List->size) {
        printf("Invalid index!\n");
        return NULL;
    }

    //case 3: index present
    LocNode* tmp = List->head; 
    for(unsigned int i = 0; i < index; ++i) {//traversing till index - 1 
        //printf("tmp value: %d for i = %d\n ", tmp->data, i);    
        tmp = tmp->next; //moving to the next node
    }
    //printf("about to return\n");
    return tmp;
}

void insert(LocList* List, int index, location* data) {
    /*
    * insert a node with data at index
    * O(n)
    */

    LocNode* new_node = (LocNode*)malloc(sizeof(LocNode));
    new_node->data = data;

    
    if(List->size == 0) { //case 1: empty list
        List->head = new_node;
        new_node->next = NULL;
    } 
    else if(index == 0) { //case 2: front insertion
        new_node->next = List->head;
        List->head = new_node;
    } 
    else { //case 3: Non empty list with insert at middle
        LocNode* prev = traverse(List, index);
        new_node->next = prev->next;
        prev->next = new_node;
    }

    ++List->size;
}


void pushfront(LocList* List,location* data) {
    /*
    * insert node at the front of the list
    */
   insert(List, 0, data);
} 

void pushback(LocList* List, location* data) {
    /*
    * insert node at the end of the list
    */
   if(List->size == 0) {
        LocNode* new_node = (LocNode*)malloc(sizeof(LocNode));
        new_node->data = data;
        new_node->next = NULL;
        List->head = new_node;
        ++List->size;
   }
   else if(List->size == 1) { //edge case for single node list
        LocNode* new_node = (LocNode*)malloc(sizeof(LocNode));
        new_node->data = data;
        new_node->next = List->head->next;
        List->head->next = new_node;
        ++List->size;

    } else {
        insert(List, List->size - 1, data);
    }
}  


location* suppress(LocList* List,const int index) {
    /*
    * suppress() deletes node at index
    * O(n)
    */ 

    //case 1: empty list
    if(List->size == 0) {
        printf("empty list!\n");
        return NULL;
    }

    //case 2: invalid index
    if(index < 0 || index >= List->size) {
        printf("invalid index");
        return NULL;
    }

    LocNode* to_del;
    
    if(index == 0) { //case 3: deleting head
       to_del = List->head;
       List->head = (List->head)->next;

    } else {  //case 4: deleting any node that is not head
        LocNode* prev = traverse(List, index - 1);
        to_del = prev->next;
        prev->next = to_del->next;

    }

    location* tmp = to_del->data;
    free(to_del);
    --List->size;
    return tmp;
}

location* popfront(LocList* List) {
    /*
    * delete node at the back of the list
    */
    return suppress(List,0);
}  

location* popback(LocList* List) {
    /*
    * delete node at the front of the list
    */
    return suppress(List, List->size - 1);
}  
#endif //LOCLIST_H