

#ifndef client_h
#define client_h

#include <stdio.h>

typedef struct client_type *ClientType;
typedef struct address_type *AddressType;
typedef struct preference_type *PreferenceType;

// Preference struct
struct preference_type {
    long int minBed;
    long int minBath;
    long int minFootage;
    long int maxPrice;
};

// Address struct
struct address_type {
    char name[60];
    char address[60];
    char location[60];
    char phone[15];
};

// Client struct- contains an address and a preference
struct client_type {
    char id[7];
    struct address_type address;
    struct preference_type preference;
};

ClientType generateClient();
void setClientID(char id[], ClientType client);
void setClientName(char name[], ClientType client);
void setClientAddress(char address[], ClientType client);
void setClientLocation(char location[], ClientType client);
void setClientPhone(char phone[], ClientType client);
void setClientMinBed(char *minBed, ClientType client);
void setClientMinBath(char *minBath, ClientType client);
void setClientMinFootage(char *minFootage, ClientType client);
void setClientMaxPrice(char *maxPrice, ClientType client);
char *getClientID(ClientType client);
void printClient(ClientType client);

#endif /* client_h */
