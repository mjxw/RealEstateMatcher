// Matthew Wu
// HW 4 
// TCSS 333

#ifndef house_h
#define house_h


#include <stdio.h>

// Struct for house
struct house_type {
    long int mls;
    char address[30];
    char city[30];
    char zip[30];
    long int bed;
    long int bath;
    long int sqft;
    long int price;
};

typedef struct house_type *HouseType;

HouseType generateHouse();
void setHouseMLS(HouseType house, long int mls);
void setHouseAddress(HouseType house, char address[]);
void setHouseCity(HouseType house, char city[]);
void setHouseZip(HouseType house, char zip[]);
void setHouseBed(HouseType house, long int bed);
void setHouseBath(HouseType house, long int bath);
void setHouseSqFt(HouseType house, long int sqft);
void setHousePrice(HouseType house, long int price);
void printHouse(HouseType house);

#endif /* house_h */
