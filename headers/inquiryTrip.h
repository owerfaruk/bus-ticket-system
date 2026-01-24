// Searches and displays detailed information of a specific trip
// Returns:
// 0  -> Trip found
// -1 -> Trip not found
// -2 -> No trip data exists
int inquiryTrip() {

    int tripID, thereIs = 0;

    FILE* itrip = fopen("trips.dat", "rb");

    if (itrip == NULL) {
        return -2;
    }

    printf("\nPlease enter the ID of trip you want to find: ");
    scanf("%d", &tripID);
    clearBuffer();

    trip inquiryTrip;

    // Find and display the trip details
    while (fread(&inquiryTrip, sizeof(trip), 1, itrip)) {
        if (inquiryTrip.tripId == tripID) {

            thereIs = 1;

            printf("\n---------------------------------\n");
            printf("|        INQUIRY A TRIP         |\n\n");

            printf("|  ID: %d\n", inquiryTrip.tripId);
            printf("|  Destination: %s\n", inquiryTrip.pointTo);
            printf("|  Exit Location: %s\n", inquiryTrip.pointFrom);
            printf("|  Date and Time: %s - %s\n", inquiryTrip.date, inquiryTrip.time);
            printf("|  Plate: %s\n", inquiryTrip.plate);
            printf("|  Driver's name: %s\n", inquiryTrip.driverName);
            printf("|  Vehicle capacity (sold - total): %d - %d\n", inquiryTrip.selledSeat, inquiryTrip.seatTotal);
            printf("|  Ticket Price: %s\n\n", inquiryTrip.ticketPrice);

            break;
        }
    }

    fclose(itrip);
        
    if(thereIs == 1) {
        return 0;
    } else {
        return -1;
    }
}