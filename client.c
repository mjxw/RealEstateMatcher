// Matthew Wu
// HW 4 
// TCSS 333

#include "client.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Create a client object by allocating memory dynamically 
ClientType generateClient() {
    ClientType cPtr = malloc(sizeof(struct client_type));
    return cPtr;
}

// Sets the client's ID 
void setClientID(char id[], ClientType client) {
    strncpy(client -> id, id, strlen(id) -2);
}

// Sets the client's name 
void setClientName(char name[], ClientType client) {
    long int length = strlen(name) - 2;
    
    strncpy(client -> address.name, name, length);
}

// Sets the client's address
void setClientAddress(char address[], ClientType client) {
    long int length = strlen(address) - 2;
    
    strncpy(client -> address.address, address, length);

}

// Sets the client's location
void setClientLocation(char location[], ClientType client) {
    long int length = strlen(location) - 2;
    
    strncpy(client -> address.location, location, length);
}

// Sets the client's phone
void setClientPhone(char phone[], ClientType client) {
    long int length = 12; // get the proper amount of numbers for phone number (last entry) doesnt have /r/n?
    
    strncpy(client -> address.phone, phone, length);
}

// Gets a client's ID 
char *getClientID(ClientType client) {
    return client -> id;
        
}

// Sets the client's min bed
void setClientMinBed(char *minBed, ClientType client) {
    long int bed;
    bed = atoi(minBed);
    client -> preference.minBed = bed;
}

// Sets the client's min bath
void setClientMinBath(char *minBath, ClientType client) {
    long int bath;
    bath = atoi(minBath);
    client -> preference.minBath = bath;
}

// Sets the client's min footage requirement 
void setClientMinFootage(char *minFootage, ClientType client) {
    long int footage;
    footage = atoi(minFootage);
    client -> preference.minFootage = footage;
}

// Sets a clients max price threshold
void setClientMaxPrice(char *maxPrice, ClientType client) {
    long int price;
    price = atoi(maxPrice);
    client -> preference.maxPrice = price;
}

// Print method for a client for testing
void printClient(ClientType client) {
    printf("ID: %s \n", client -> id);
    printf("name: %s \n", client -> address.name);
    printf("address: %s \n", client -> address.address);
    printf("location: %s \n", client -> address.location);
    printf("phone: %s \n", client -> address.phone);
    printf("min bed: %li \n", client -> preference.minBed);
    printf("min bath: %li \n", client -> preference.minBath);
    printf("min sq footage: %li \n", client -> preference.minFootage);
    printf("max price: %li \n" , client -> preference.maxPrice);
    printf("\n");
}
