// Cancels a sold ticket
// Removes the ticket record, updates trip seat count,
// and deletes the corresponding receipt file
// Returns:
// 0  -> Success
// -1 -> Ticket not found
// -2 -> No ticket data exists
int deleteTicket() {
    int tripID, ticketID, thereIs = 0;

    FILE* dticket = fopen("tickets.dat", "rb");

    if (dticket == NULL) {
        return -2;
    }

    printf("\nPlease enter the ID of trip and ticket you want to cancel\n");
    printf("Trip ID: ");
    scanf("%d", &tripID);
    clearBuffer();
    printf("Ticket ID: ");
    scanf("%d", &ticketID);
    clearBuffer();

    FILE* temp = fopen("temp.dat", "wb");
    // Check if file exists
    if (temp == NULL) {
        return -5;
    }
    
    ticket delTicket;

    // Find the ticket by ID and Trip ID, copy others to temp
    while (fread(&delTicket, sizeof(ticket), 1, dticket)) {
        if ((delTicket.tripId == tripID) && (delTicket.ticketId == ticketID)) {
            thereIs = 1;
        } else {
            fwrite(&delTicket, sizeof(ticket), 1, temp);
        }
    }

    fclose(dticket);
    fclose(temp);
    
    remove("tickets.dat");
    rename("temp.dat", "tickets.dat");

    if(thereIs == 1) {

        // Remove the invoice file
        char receipt[50];
        sprintf(receipt, "bill_%d_%d.txt", tripID, ticketID);
        remove(receipt);

        // Decrease sold seat count after successful ticket cancellation
        FILE* utrip = fopen("trips.dat", "rb");
        FILE* tempTrip = fopen("temp_trips.dat", "wb");

        if (utrip == NULL || tempTrip == NULL) {
            return -5;
        }

        trip updateTrip;

        while (fread(&updateTrip, sizeof(trip), 1, utrip)) {
            if (updateTrip.tripId == tripID) {
                updateTrip.selledSeat--;
            }
            fwrite(&updateTrip, sizeof(trip), 1, tempTrip);
        }
        
        fclose(utrip);
        fclose(tempTrip);

        remove("trips.dat");
        rename("temp_trips.dat", "trips.dat");

        return 0;
    } else {
        return -1;
    }
}