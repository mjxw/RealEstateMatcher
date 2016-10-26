

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "house.h"

// Creates a house object dynamically
HouseType generateHouse() {
    HouseType hPtr = malloc(sizeof(struct house_type));
    return hPtr;
}

// Sets a house's MLS
void setHouseMLS(HouseType house, long int mls) {
    house -> mls = mls;
}

// Sets a house's address
void setHouseAddress(HouseType house, char address[]) {
    strcpy(house -> address, address);
}

// Sets a house's city
void setHouseCity(HouseType house, char city[]) {
    strcpy(house -> city, city);
}

// Sets a house's zip
void setHouseZip(HouseType house, char zip[]) {
    strcpy(house -> zip, zip);
}

// Sets a house's bed
void setHouseBed(HouseType house, long int bed) {
    house -> bed = bed;
}

// Sets a house's bath
void setHouseBath(HouseType house, long int bath) {
    house -> bath = bath;
}

// Sets a house's sq footage
void setHouseSqFt(HouseType house, long int sqft) {
    house -> sqft = sqft;
}

// Sets a house's price
void setHousePrice(HouseType house, long int price) {
    house -> price = price; 
}

// Print method for a house for testing
void printHouse(HouseType house) {
    printf("MLS: %li \n", house -> mls);
    printf("address: %s \n", house -> address);
    printf("city: %s \n", house -> city);
    printf("zip: %s \n", house -> zip);
    printf("bed: %li \n", house -> bed);
    printf("bath: %li \n", house -> bath);
    printf("sq ft: %li \n", house -> sqft);
    printf("price: %li \n", house -> price);
    printf("\n");
}

