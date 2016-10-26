

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <math.h>

#include "client.h"
#include "list.h"
#include "house.h"

// Prototypes
int compare(int *a, int*b);
void nullBuffer(char *arr);
void addPreferences(FILE *pfPtr, ClientType client);
void addClientInfo(FILE *cfPtr, ListType clientList);
void addHouseInfo(ListType houseList);
void clientsView(ListType clientList, ListType houseList);
void houseView(ListType clientList, ListType houseList);
int match(ClientType client, HouseType house);

// Creates lists for clients and houses. Calls methods to create client and house objects
// as well as populate them with the correct information. Writes to two files for clients and
// houses.
int main(void) {
    FILE *cfPtr; // clients.txt file pointer
    ListType clientList;
    ListType houseList;
	int i;
	
	// Create 2 lists
    clientList = create(sizeof(struct client_type), NULL);
    houseList = create(sizeof(struct house_type), NULL);
	
	// Call methods for filling client and house objects with info
    addClientInfo(cfPtr, clientList);
    addHouseInfo(houseList);
    
	// These methods write to external file the relevant info 
    clientsView(clientList, houseList);
    houseView(clientList, houseList);

	// free up memory
	destroy(clientList);
	destroy(houseList);
    return 0;
}

// Creates a client object and reads a text file to get relevent information of client.
void addClientInfo(FILE *cfPtr, ListType clientList) {
    FILE *pfPtr; // preferences.txt pointer
    int line = 1;
    int cycle;
    char inputLines[200];
    char id[7];
    char name[60];
    char address[60];
    char location[60];
    char phone[15];
    
	// Create client 
    ClientType client = generateClient();
    
    if ((cfPtr = fopen("clients.txt", "r")) == NULL) {
        puts("File could not be opened");
    } else {
        while (fgets(inputLines, 100, cfPtr) != NULL) {
            if (line == 1) {
                strcpy(id, inputLines);
                setClientID(id, client);
            } else if (line == 2) {
                strcpy(name, inputLines);
                setClientName(name, client);
            } else if (line == 3) {
                strcpy(address, inputLines);
                setClientAddress(address, client);
            } else if (line == 4) {
                strcpy(location, inputLines);
                setClientLocation(location, client);
            } else {
                strcpy(phone, inputLines);
                setClientPhone(phone, client);
				
				// Call method to read preference file and collect relevent preference info                 
				addPreferences(pfPtr, client);
                
				// Add client to list
				push(clientList, client);
				client = generateClient(); // reset
                line = 0;
                cycle++;
            }
            line++;
        }
    }
	free(client);
    fclose(cfPtr);
}

// This method reads the preferences text file and collects client preference info
void addPreferences(FILE *pfPtr, ClientType client) {
    char inputLines[200];
    char modifiedInput[200];
    int found = 0; // 0 for not found, 1 for found
    char preferences[50];
    long int strlength;
    const char s[2] = " ";
    char *minBed;
    char *minBath;
    char *minFootage;
    char *maxPrice;
    
	// clear strings to avoid garbage characters
    nullBuffer(inputLines);
    nullBuffer(modifiedInput);
    nullBuffer(preferences);
    
    if ((pfPtr = fopen("preferences.txt", "r")) == NULL) {
        puts("File could not be opened");
    } else {
        while (fgets(inputLines, 100, pfPtr) != NULL) {
            strlength = strlen(inputLines)-2;
            nullBuffer(modifiedInput);
            strncpy(modifiedInput, inputLines, strlength);
            if (strcmp(getClientID(client), modifiedInput) == 0) {
                found = 1;
                continue;
            } if (found == 1) {
                strcpy(preferences, inputLines);
                
                // store tokens appropriately
                minBed = strtok(inputLines, s);
                minBath = strtok(NULL, s);
                minFootage = strtok(NULL, s);
                maxPrice = strtok(NULL, s);
                
                // execute setter methods
                setClientMinBed(minBed, client);
                setClientMinBath(minBath, client);
                setClientMinFootage(minFootage, client);
                setClientMaxPrice(maxPrice, client);
                
                // reset found
                found = 0;
            }
        }
    }
    fclose(pfPtr);
}

// This method reads the houses file and creates a house object with the relevant info
void addHouseInfo(ListType houseList) {
    FILE *hPtr; // houses.csv file pointer
    char address[60];
    char city[60];
    char zip[30];
    long int mls;
    long int bed;
    long int bath;
    long int sqft;
    long int price;
    char inputLines[200];
   
	// Create house
    HouseType house = generateHouse();
    
    if ((hPtr = fopen("houses.csv", "r")) == NULL) {
        puts("File could not be opened");
    } else {
        fgets(inputLines, sizeof(inputLines), hPtr); // skip first line
        while (fgets(inputLines, sizeof(inputLines), hPtr) != NULL)  {
            sscanf(inputLines, "%ld,%[^,],%[^,],%[^,],%ld,%ld,%ld,%ld", &mls, address, city, zip,
                &bed, &bath, &sqft, &price);
            setHouseMLS(house, mls);
            setHouseAddress(house, address);
            setHouseCity(house, city);
            setHouseZip(house, zip);
            setHouseBed(house, bed);
            setHouseBath(house, bath);
            setHouseSqFt(house, sqft);
            setHousePrice(house, price);
            
			// Add to list
            push(houseList, house);
            house = generateHouse(); // reset
            continue;
        }
    }
    free(house);
    fclose(hPtr);
}

// Write to clientsView file the matches for client and house
void clientsView(ListType clientList, ListType houseList) {
    FILE *clientsView = fopen("clientsView.csv", "w");
    int hits = 0; // requirements met
    int singleClient = 0;   
    int clientIndex, houseIndex;    
    fprintf(clientsView, "%s\n", "Client ID,Name,Phone Number,,,MLS,Street Address,City,Zip,Bedroom,Bathroom,Sq Footage,Price");
    
    for (clientIndex = 0; clientIndex < size_is(clientList); clientIndex++) {
        ClientType client = getClient(clientList, clientIndex);
        
        for (houseIndex = 0; houseIndex < size_is(houseList); houseIndex++) {
            HouseType house = getHouse(houseList, houseIndex);
            
            if (match(client, house) == 0) {
                char clientID[7];
                char clientName[60];
                char clientPhone[15];
                long int houseMLS, houseBeds, houseBaths, houseSqFt, housePrice;
                char houseAddress[60];
                char houseCity[60];
                char houseZip[30];
                
				// Set variables
                strcpy(clientID, client -> id);
                strcpy(clientName, client -> address.name);
                strcpy(clientPhone, client -> address.phone);
                houseMLS = house -> mls;
                strcpy(houseAddress, house -> address);
                strcpy(houseCity, house -> city);
                strcpy(houseZip, house -> zip);
                houseBeds = house -> bed;
                houseBaths = house -> bath;
                houseSqFt = house -> sqft;
                housePrice = house -> price;
                
                if (singleClient == 0) {
                    fprintf(clientsView, "%s", clientID);
                    fprintf(clientsView, "%s", ",");
                    fprintf(clientsView, "%s", clientName);
                    fprintf(clientsView, "%s", ",");
                    fprintf(clientsView, "%s", clientPhone);
                } else {
                    fprintf(clientsView, "%s", ",,");
                }
                fprintf(clientsView, "%s", ",,,");
                fprintf(clientsView, "%li", houseMLS);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%s", houseAddress);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%s", houseCity);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%s", houseZip);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%li", houseBeds);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%li", houseBaths);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%li", houseSqFt);
                fprintf(clientsView, "%s", ",");
                fprintf(clientsView, "%li", housePrice);
                fprintf(clientsView, "%c", '\n');
                hits++;
                singleClient = -1;
            }
        }
        singleClient = 0;
    }
    if (hits == 0) {
        fprintf(clientsView, "%s", "No matches found.");
    }
    fclose(clientsView);
}

// This method writes to the houseView file the matches for houses and clients
void houseView(ListType clientList, ListType houseList) {
    FILE *houseView = fopen("houseView.csv", "w");
    int singleHouse = 0;
    int houseIndex, clientIndex;
    fprintf(houseView, "%s\n", "MLS,Street Address,City,Zip,Bedroom,Bathroom,Sq Footage,Price,,Client ID,Name,Phone Number, price difference");
    
    for (houseIndex = 0; houseIndex < size_is(houseList); houseIndex++) {
        HouseType house = getHouse(houseList, houseIndex);
        char houseAddress[60];
        char houseCity[60];
        char houseZip[30];
        long int houseMLS, houseBed, houseBath, houseSqFt, housePrice;
        strcpy(houseAddress, house -> address);
        strcpy(houseCity, house -> city);
        strcpy(houseZip, house -> zip);
        houseMLS = house -> mls;
        houseBed = house -> bed;
        houseBath = house -> bath;
        houseSqFt = house -> sqft;
        housePrice = house -> price;
        
        for (clientIndex = 0; clientIndex < size_is(clientList); clientIndex++) {
            ClientType client = getClient(clientList, clientIndex);
            char clientID[7];
            char clientName[60];
            char clientPhone[15];
    		long int clientMaxPrice = client -> preference.maxPrice;
            strcpy(clientID, client -> id);
            strcpy(clientName, client -> address.name);
            strcpy(clientPhone, client -> address.phone);
          
            if (match(client, house) == 0) {
				long int difference = abs(housePrice - clientMaxPrice);
                if (singleHouse == 0) {
                    fprintf(houseView, "%li", houseMLS);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%s", houseAddress);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%s", houseCity);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%s", houseZip);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%li", houseBed);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%li",houseBath);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%li", houseSqFt);
                    fprintf(houseView, "%s", ",");
                    fprintf(houseView, "%li", housePrice);
                } else {
                    fprintf(houseView, "%s", ",,,,,,,");
                }
                fprintf(houseView, "%s", ",,");
                fprintf(houseView, "%s", clientID);
                fprintf(houseView, "%s", ",");
                fprintf(houseView, "%s", clientName);
                fprintf(houseView, "%s", ",");
                fprintf(houseView, "%s", clientPhone);
				fprintf(houseView, "%s", ",");
				fprintf(houseView, "%li", difference);
                fprintf(houseView, "%s", "\n");
                singleHouse = -1;
            }
        }
        singleHouse = 0;
    }
    fclose(houseView);
}

// This method creates indicator for client threshold matches
int match(ClientType client, HouseType house) {
    int match = 0;
    char clientID[7];
    strcpy(clientID, client -> id);
    long int clientMinBed = client -> preference.minBed;
    long int clientMinBath = client -> preference.minBath;
    long int clientMinFootage = client -> preference.minFootage;
    long int clientMaxPrice = client -> preference.maxPrice;
    long int houseBed = house -> bed;
    long int houseBath = house -> bath;
    long int houseSqFt = house -> sqft;
    long int housePrice = house -> price;
    
    if (houseBed < clientMinBed) {
        match = -1;
    }
    if (houseBath < clientMinBath) {
        match = -1;
    }
    if (houseSqFt < clientMinFootage) {
        match = -1;
    }
    if (housePrice > clientMaxPrice) {
        match = -1;
    }
    return match;
}

// This method is for clearing strings to avoid garbage characters
void nullBuffer(char *arr) {
    int index;
    
    for (index = 0; index < 200; index++) { // set every index to null to avoid garbage values
        arr[index] = '\0';
    }
}

int compare(int *a, int *b) {
    short int toReturn = 0;
    if (*a < *b)
        toReturn = -1;
    else if (*a > *b)
        toReturn = 1;
    return toReturn;
}
