#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/header.h"

// Clears remaining characters in the input buffer
// Prevents unwanted input issues caused by leftover newline characters
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Headers of functions
#include "headers/menu.h"
#include "headers/createTrip.h"
#include "headers/updateTrip.h"
#include "headers/deleteTrip.h"
#include "headers/inquiryTrip.h"
#include "headers/listAllTrips.h"
#include "headers/sellTicket.h"
#include "headers/deleteTicket.h"

int main() {

    int choice = 0, res = 0;

    menu();

    do {
        printf(">>> Enter a number from the menu to make a transaction: ");
        scanf("%d", &choice);

        // Menu selection logic
        switch(choice) {
            case 0:
                printf("\n--  You have exited the program.");
                return 0;
                break;
            case 8:
                menu();
                break;                
            case 1:
                res = createTrip();
                if(res == 0) printf("\n--  The trip was successfully added.\n\n");
                else if(res == -2) printf("\n--  File could not be opened.\n\n");
                else printf("\n--  A problem occurred while adding the trip.\n\n");
                break;
            case 2:
                res = updateTrip();
                if(res == 0) printf("\n--  The trip was successfully updated.\n\n");
                else if(res == -1) printf("\n--  The trip could not be found.\n\n");
                else if(res == -2) printf("\n--  There is no trip yet.\n\n");
                else printf("\n--  A problem occurred while updating the trip.\n\n");
                break;
            case 3:
                res = deleteTrip();
                if(res == 0) printf("\n--  The trip was successfully deleted.\n\n");
                else if(res == -1) printf("\n--  The trip could not be found.\n\n");
                else if(res == -2) printf("\n--  There is no trip yet.\n\n");
                else if(res == -3) printf("\n--  There are tickets sold for this trip. Please cancel the tickets first.\n\n");
                else printf("\n--  A problem occurred while deleting the trip.\n\n");
                break;
            case 4:
                res = inquiryTrip();
                if(res == 0) break;
                else if(res == -1) printf("\n--  The trip could not be found.\n\n");
                else if(res == -2) printf("\n--  There is no trip yet.\n\n");
                else printf("\n--  A problem occurred while searching for the trip.\n\n");
                break;
            case 5:
                res = listAllTrips();
                if(res == 0) printf("\n--  All trips were successfully listed.\n\n");
                else if(res == -2) printf("\n--  There is no trip yet.\n\n");
                else printf("\n--  A problem occurred while listing trips.\n\n");
                break;
            case 6:
                res = sellTicket();
                if(res == 0) printf("\n--  Ticket sold and receipt was created.\n\n");
                else if(res == -1) printf("\n--  The trip could not be found.\n\n");
                else if(res == -2) printf("\n--  There is no trip yet.\n\n");
                else if(res == -3) printf("\n--  This trip is full.\n\n");
                else printf("\n--  A problem occurred while selling the ticket.\n\n");
                break;
            case 7:
                res = deleteTicket();
                if(res == 0) printf("\n--  The ticket was successfully deleted.\n\n");
                else if(res == -1) printf("\n--  The ticket could not be found.\n\n");
                else if(res == -2) printf("\n--  No tickets have been sold so far.\n\n");
                else printf("\n--  A problem occurred while deleting the ticket.\n\n");
                break;                                                                   
            default: 
                printf("\n=>  Please type a number between 0 and 8.\n\n"); 
				clearBuffer();
        }
    } while(choice != 0);

    return 0;
}