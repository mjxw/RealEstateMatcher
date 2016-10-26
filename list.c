

#include "client.h"
#include "house.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Struct for list
struct list_type {
    void *data;
    int size;
    int capacity;
    int elementSize;
    int (*comparePtr) (void *d1, void *d2);
};

// returns the pointer to the list; NULL if list not created
ListType create (int elSize, int (*comp) (void *item1, void * item2)) {
   
    // allocate memory for a structure variable containing all list components
    ListType listPtr = malloc(sizeof(struct list_type));
    
    //if allocation was succesfull
    if (listPtr != NULL) {
        listPtr -> size = 0;
        listPtr -> capacity = 10;
        listPtr -> elementSize = elSize;
        listPtr -> comparePtr = comp;
        
        // allocate memory for the acual array
        listPtr -> data = malloc(10*(listPtr -> elementSize));
        
        // if arrray not created, deallocate the list too
        if (listPtr -> data == NULL) {
            free(listPtr);
            listPtr = NULL;
        }
    }
    return listPtr;
}

void destroy(ListType listPtr) {
    free(listPtr -> data);
    free(listPtr);
    listPtr = NULL;
}

void printl(ListType listPtr, void (*printItem) (void *d)) {
    int i;
    for (i = 0; i < listPtr -> size; i++) {
        
        // since we cannot use data[i], we need to calculate the address
        // of the element to be sent to the client's print function
        // since data is of type void, the formula is:
        // the beginning address of the array + (offset x element size)
        printItem(listPtr -> data + i * (listPtr -> elementSize) );
        printf(" ");
    }
    printf("\n");
}

// Size of list
int size_is(ListType listPtr) {
    return listPtr -> size;
}

// Method for if the list is empty
int is_empty(ListType listPtr) {
    return listPtr -> size == 0;
}

// Method for making the list empty
void make_empty(ListType listPtr) {
    // if list is larger than 200 elements, create a smaller one
    if (listPtr -> capacity > 200) {
        listPtr -> data = realloc(listPtr -> data, listPtr -> elementSize);
    }
    listPtr -> size = 0;
    listPtr -> capacity = 100;
}

//adds a component to the array, if enough memory available
void push(ListType listPtr, void *item) {
    if (listPtr -> size >= listPtr -> capacity) {
        void *temp = realloc(listPtr -> data, listPtr -> elementSize * (listPtr -> capacity + 100));
        if (temp != NULL) {
            listPtr -> capacity += 100;
            listPtr -> data = temp;
            
            // copy the element, since we cannot use data[i], we need to copy the data using memcpy
            memcpy(listPtr -> data + (listPtr -> size) * (listPtr -> elementSize), item, listPtr -> elementSize);
            listPtr -> size++;
        }
    } else {
        memcpy(listPtr -> data + (listPtr -> size) * (listPtr ->elementSize), item, listPtr -> elementSize);
        listPtr -> size++;
    }
}

// Method for checking if list is full
int is_full(ListType listPtr) {
    if (listPtr -> size < listPtr -> capacity) {
        return 0;
    } else {
        void * temp = malloc(listPtr -> elementSize * (listPtr -> capacity + 100));
        if (temp != NULL) {
            free(temp);
            return 0;
        }
        return 1;
    }
}

// Returns a client, from a list, by index
ClientType getClient(ListType listptr, int index) {
    ClientType client = (ClientType) (listptr->data + index * (listptr->elementSize));
    return client;
}

// Returns a house, from a list, by index
HouseType getHouse(ListType listptr, int index) {
    HouseType house = (HouseType) (listptr->data + index * (listptr->elementSize));
    return house;
}













