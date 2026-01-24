// Sells a ticket for a selected trip
// Ensures seat availability and prevents duplicate seat sales
// Updates trip data and generates a receipt file
// Returns:
// 0  -> Success
// -1 -> Trip not found
// -2 -> No trip data exists
// -3 -> Trip is full
int sellTicket() {
    
    FILE* trips = fopen("trips.dat", "rb");

    if (trips == NULL) {
        return -2;
    }

    int tripID, thereIs = 0;

    printf("\nPlease enter the ID of trip you want to sell ticket: ");
    scanf("%d", &tripID);
    clearBuffer();

    trip isTrip;
    ticket newTicket;
	
    // Find trip and check for seat availability
    while (fread(&isTrip, sizeof(trip), 1, trips)) {
        if (isTrip.tripId == tripID) {
            if (isTrip.selledSeat >= isTrip.seatTotal) {
                fclose(trips);
                return -3; // Trip is full
            }
            thereIs = 1;
            break;
        }
    }

    if(thereIs == 0) {
        fclose(trips);
        return -1;
    }

    // Process ticket sale
    printf("\n---------------------------------\n");
    printf("|         SELL A TICKET         |\n\n");
    printf("|  Trip ID - %d\n|  Destination - %s to %s\n|  Time - %s\n|  Ticket Price - %s\n\n", isTrip.tripId, isTrip.pointFrom, isTrip.pointTo, isTrip.time, isTrip.ticketPrice);

    printf("|  Please enter your name: ");
    fgets(newTicket.name, sizeof(newTicket.name), stdin);
    newTicket.name[strcspn(newTicket.name, "\n")] = 0;

    int isTaken;
    
    do {
        isTaken = 0;
		
        // Seat number input validation
        printf("|  Please enter seat number you want to buy: ");
        while (scanf("%d", &newTicket.seatNum) != 1) {
            printf("\n=>  Invalid format! Enter numbers only.\n\n");
            printf("|  Please enter seat number you want to buy: ");
            clearBuffer();
        }
        clearBuffer();
        
        // Seat range check
        if (newTicket.seatNum > isTrip.seatTotal || newTicket.seatNum < 1) {
            printf("\n=>  Invalid seat number! This bus has a capacity of %d seats.\n\n", isTrip.seatTotal);
            isTaken = 1;
            continue;
        }   
		
        // Check if selected seat is already sold for this trip
        FILE* checkTicketFile = fopen("tickets.dat", "rb");
        
        if (checkTicketFile != NULL) {
            ticket checkTicket;
            while (fread(&checkTicket, sizeof(ticket), 1, checkTicketFile)) {
                if (checkTicket.tripId == tripID && checkTicket.seatNum == newTicket.seatNum) {
                    printf("\n=>  Seat %d is already taken!\n\n", newTicket.seatNum);
                    isTaken = 1;
                    break;
                }
            }
            fclose(checkTicketFile);
        }
        
    } while (isTaken == 1);
    
    // Update the number of sold seats in the trips database
    // Update sold seat count using temporary file to ensure data integrity
    FILE* temp = fopen("temp.dat", "wb");
    // Check if file exists
    if (temp == NULL) {
        return -5;
    }
    rewind(trips); 

    trip tempTrip; 
    while (fread(&tempTrip, sizeof(trip), 1, trips)) {
        if (tempTrip.tripId == tripID) {
            tempTrip.selledSeat++;
            isTrip.selledSeat = tempTrip.selledSeat; 
        }
        fwrite(&tempTrip, sizeof(trip), 1, temp);
    }
    
    fclose(trips);
    fclose(temp);

    remove("trips.dat");
    rename("temp.dat", "trips.dat");

    // Save the ticket to tickets database
    FILE* sticket = fopen("tickets.dat", "ab"); 
    if (sticket != NULL) {
        newTicket.tripId = tripID;
        newTicket.ticketId = (tripID * 10000) + newTicket.seatNum;
        
        fwrite(&newTicket, sizeof(ticket), 1, sticket); 
        fclose(sticket);
    }

    // Generate a text-based receipt for the sold ticket
    char bill[50];
    sprintf(bill, "bill_%d_%d.txt", newTicket.tripId, newTicket.ticketId);
    
    FILE* fp = fopen(bill, "w");
    if (fp != NULL) {
        fprintf(fp, "---------------------------------\n");
        fprintf(fp, "|         BILL FOR TRIP         |\n\n");
        fprintf(fp, "|  Dear %s, you have successfully purchased your ticket.\n\n", newTicket.name);
        fprintf(fp, "|           TRIP INFOS          |\n\n");
        fprintf(fp, "|  Destination: %s -> %s\n", isTrip.pointFrom, isTrip.pointTo);
        fprintf(fp, "|  Date - Time: %s - %s\n", isTrip.date, isTrip.time);
        fprintf(fp, "|  Ticket Price: %s\n", isTrip.ticketPrice);
        fprintf(fp, "|  Trip ID: %d\n", isTrip.tripId);
        fprintf(fp, "|  Ticket ID: %d\n", newTicket.ticketId);
        fprintf(fp, "|  Seat Number: %d\n\n", newTicket.seatNum);
        fprintf(fp, "|    Have a pleasant journey!   |");
        fclose(fp);
    }
    return 0;
}