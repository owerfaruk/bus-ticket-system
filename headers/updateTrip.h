// Updates an existing trip by ID
// Uses a temporary file to safely overwrite data
// Returns:
// 0  -> Success
// -1 -> Trip not found
// -2 -> File error
int updateTrip() {
    int tripID, thereIs = 0, answer;

    FILE* utrip = fopen("trips.dat", "rb");
    
    // Check if file exists
    if (utrip == NULL) {
        return -2;
    }

    printf("\nPlease enter the ID of trip you want to update: ");
    scanf(" %d", &tripID);
    clearBuffer();

    FILE* temp = fopen("temp.dat", "wb");

    // Check if file exists
    if (temp == NULL) {
        return -5;
    }

    trip upTrip;

    // Find and update trip data in the database
    while (fread(&upTrip, sizeof(trip), 1, utrip)) {
        if (upTrip.tripId == tripID) {
            
            thereIs = 1;

            printf("\n---------------------------------\n");
            printf("|         UPDATE A TRIP         |\n\n");

            printf("|  Please enter your updated destination (Old: %s): ", upTrip.pointTo);
            fgets(upTrip.pointTo, sizeof(upTrip.pointTo), stdin);
            upTrip.pointTo[strcspn(upTrip.pointTo, "\n")] = 0;

            printf("|  Please enter your updated exit location (Old: %s): ", upTrip.pointFrom);
            fgets(upTrip.pointFrom, sizeof(upTrip.pointFrom), stdin);
            upTrip.pointFrom[strcspn(upTrip.pointFrom, "\n")] = 0;

            printf("|  Please enter your updated date (DD.MM.YYYY) (Old: %s): ", upTrip.date);
            fgets(upTrip.date, sizeof(upTrip.date), stdin);
            upTrip.date[strcspn(upTrip.date, "\n")] = 0;
        
            printf("|  Please enter your updated time (HH.MM) (Old: %s): ", upTrip.time);
            fgets(upTrip.time, sizeof(upTrip.time), stdin);
            upTrip.time[strcspn(upTrip.time, "\n")] = 0;
        
            printf("|  Please enter your updated bus plate (Old: %s): ", upTrip.plate);
            fgets(upTrip.plate, sizeof(upTrip.plate), stdin);
            upTrip.plate[strcspn(upTrip.plate, "\n")] = 0;
        
            printf("|  Please enter your updated Driver's name (Old: %s): ", upTrip.driverName);
            fgets(upTrip.driverName, sizeof(upTrip.driverName), stdin);
            upTrip.driverName[strcspn(upTrip.driverName, "\n")] = 0;

            printf("|  Please enter your updated Vehicle capacity (Old: %d - Sold: %d): ", upTrip.seatTotal, upTrip.selledSeat);
            
            // Seat update validation: Checks format, range, and sold seat conflict
            while (1) {
                if (scanf("%d", &answer) == 1) {
                    if (answer < 1 || answer > 100) {
                        printf("\n=>  Invalid capacity! Please enter a value between 1 and 100.\n\n");
                        printf("|  Please enter your updated Vehicle capacity: ");
                    } else if (answer < upTrip.selledSeat) {
                        printf("\n=>  Capacity (%d) cannot be lower than currently sold seats (%d)\n\n", answer, upTrip.selledSeat);
                        printf("|  Please enter your updated Vehicle capacity: ");
                    } else {
                        upTrip.seatTotal = answer;
                        break;
                    }
                } else {
                    printf("\n=> Invalid format! Enter numbers only.\n\n");
                    printf("|  Please enter your updated Vehicle capacity: ");
                    clearBuffer();
                }
            }
            clearBuffer();

            printf("|  Please enter your updated Ticket Price (Old: %s): ", upTrip.ticketPrice);
            fgets(upTrip.ticketPrice, sizeof(upTrip.ticketPrice), stdin);
            upTrip.ticketPrice[strcspn(upTrip.ticketPrice, "\n")] = 0;            

        }
        fwrite(&upTrip, sizeof(trip), 1, temp);
    }

    fclose(utrip);
    fclose(temp);

    // Finalize file operations (rename/remove) based on search result
    if (thereIs == 0) {
        remove("temp.dat"); 
        return -1; 
    } else {
        remove("trips.dat");
        rename("temp.dat", "trips.dat");
        return 0;
    }
}