// Lists all available trips in a formatted table
// Returns:
// 0  -> Success
// -2 -> No trip data exists
int listAllTrips() {

    FILE* latrips = fopen("trips.dat", "rb");

    if (latrips == NULL) {
        return -2;
    }

    trip allTrips;

    int i = 1;

    printf("\n\n");
    printf("|    #    %-10s %-20s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n\n", "ID", "Exit Location", "Destination", "Date", "Time", "Plate", "Driver", "Ticket Price", "Empty/Total Seats");

    while (fread(&allTrips, sizeof(trip), 1, latrips)) {

        printf("|    %d.   %-10d %-20s %-15s %-15s %-15s %-15s %-15s %-15s %d/%d\n", 
        i, allTrips.tripId, allTrips.pointFrom, allTrips.pointTo, allTrips.date, allTrips.time, allTrips.plate, 
		allTrips.driverName, allTrips.ticketPrice, (allTrips.seatTotal - allTrips.selledSeat), allTrips.seatTotal);
    
        i++;
    }

    fclose(latrips);

    return 0;
}