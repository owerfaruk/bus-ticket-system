// Deletes a trip by ID
// A trip cannot be deleted if tickets have already been sold
// Returns:
// 0  -> Success
// -1 -> Trip not found
// -2 -> File error
// -3 -> Tickets exist for this trip
int deleteTrip() {

    int tripID, thereIs = 0;

    FILE* dtrip = fopen("trips.dat", "rb");

    if (dtrip == NULL) {
        return -2;
    }

    printf("\nPlease enter the ID of trip you want to delete: ");
    scanf("%d", &tripID);
    clearBuffer();

    // Check if tickets are already sold for this trip (cannot delete if seats are sold)
    trip isTicket;
    while (fread(&isTicket, sizeof(trip), 1, dtrip)) {
        if ((isTicket.tripId == tripID) && (isTicket.selledSeat != 0)) {
            fclose(dtrip);
            return -3;
        } 
    }

    FILE* temp = fopen("temp.dat", "wb");
    
    // Check if file exists
    if (temp == NULL) {
        return -5;
    }

    trip delTrip;

    // Find trip in data and exclude it from the new file
    rewind(dtrip);
    while (fread(&delTrip, sizeof(trip), 1, dtrip)) {
        if (delTrip.tripId == tripID) {
            thereIs = 1;
        } else {
            fwrite(&delTrip, sizeof(trip), 1, temp);
        }
    }

    fclose(dtrip);
    fclose(temp);
    remove("trips.dat");
    rename("temp.dat", "trips.dat");

    // Return status
    if(thereIs == 1) {
        return 0;
    } else {
        return -1;
    }
}