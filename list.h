// Matthew Wu
// HW 4 
// TCSS 333

#ifndef list_h
#define list_h

#include "house.h"
#include "client.h"
#include <stdio.h>

typedef struct list_type *ListType;

ListType create(int elSize, int (*compare) (void *item1, void *item2));
void destroy(ListType listP);
void make_empty(ListType listP);
int is_empty(ListType listP);
int is_full(ListType listP);
int size_is(ListType listP);
void push(ListType listP, void *item);
void delete(ListType listP, void* item);
void printl(ListType listP, void (*printItem) (void *item));
ClientType getClient(ListType listptr, int index);
HouseType getHouse(ListType listptr, int index);


#endif /* list_h */
