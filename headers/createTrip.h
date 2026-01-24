// Checks whether a given Trip ID already exists in trips.dat
// Returns:
// 1 -> ID already exists
// 0 -> ID is unique or file does not exist
int Unique(int id) {
    FILE *file = fopen("trips.dat", "rb");
    if (file == NULL) return 0; // If file doesn't exist, ID is unique by default.

    trip temp;

    // Search for ID in the file
    while (fread(&temp, sizeof(trip), 1, file)) {
        if (temp.tripId == id) {
            fclose(file);
            return 1; // ID found
        }
    }
    fclose(file);
    return 0; // ID not found
}

// Creates a new trip and stores it in trips.dat
// Performs input validation and ID uniqueness check
// Returns:
// 0  -> Success
// -2 -> File open error
int createTrip() {
    trip newTrip;
    int inputId;

    printf("\n---------------------------------\n");
    printf("|         CREATE A TRIP         |\n\n");

    while (1) {
        printf("|  Please enter new Trip ID: ");
        
        // Validate input format (must be an integer)
        if (scanf("%d", &inputId) != 1) {
            printf("\n=>  Invalid format! Enter numbers only.\n\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        // Check ID uniqueness
        if (Unique(inputId)) {
            printf("\n=>  ID (%d) is already taken! Please enter a different ID.\n\n", inputId);
        } else {
            newTrip.tripId = inputId;
            break; 
        }
    }

    FILE *ntrip = fopen("trips.dat", "ab");
    
    // Check if file opened successfully
    if (ntrip == NULL) {
        return -2;
    }

    // Collect trip details
    printf("|  Please enter your destination: ");
    fgets(newTrip.pointTo, sizeof(newTrip.pointTo), stdin);    
    newTrip.pointTo[strcspn(newTrip.pointTo, "\n")] = 0; // Remove newline character left by fgets

    printf("|  Please enter your exit location: ");
    fgets(newTrip.pointFrom, sizeof(newTrip.pointFrom), stdin);
    newTrip.pointFrom[strcspn(newTrip.pointFrom, "\n")] = 0;

    printf("|  Please enter the date (DD.MM.YYYY): ");
    fgets(newTrip.date, sizeof(newTrip.date), stdin);
    newTrip.date[strcspn(newTrip.date, "\n")] = 0;
    
    printf("|  Please enter the time (HH.MM): ");
    fgets(newTrip.time, sizeof(newTrip.time), stdin);
    newTrip.time[strcspn(newTrip.time, "\n")] = 0;
    
    printf("|  Please enter bus plate: ");
    fgets(newTrip.plate, sizeof(newTrip.plate), stdin);
    newTrip.plate[strcspn(newTrip.plate, "\n")] = 0;
    
    printf("|  Please enter Driver's Name: ");
    fgets(newTrip.driverName, sizeof(newTrip.driverName), stdin);
    newTrip.driverName[strcspn(newTrip.driverName, "\n")] = 0;

    printf("|  Please enter how many seats (1-100): ");
    
    // Seat validation loop: Checks for number format and range (1-100)
    while (1) {
        if (scanf("%d", &newTrip.seatTotal) != 1) {
            printf("\n=>  Invalid format! Enter numbers only.\n\n");
            printf("|  Please enter how many seats (1-100): ");
            clearBuffer();
        } 
        else if (newTrip.seatTotal < 1 || newTrip.seatTotal > 100) {
            printf("\n=>  Invalid capacity! Please enter a value between 1 and 100.\n\n");
            printf("|  Please enter how many seats (1-100): ");
        } 
        else {
            clearBuffer();
            break;
        }
    }

    printf("|  Please enter Ticket Price for one seat: ");
    fgets(newTrip.ticketPrice, sizeof(newTrip.ticketPrice), stdin);
    newTrip.ticketPrice[strcspn(newTrip.ticketPrice, "\n")] = 0;

    // Initialize sold seat count to zero since this is a new trip
    newTrip.selledSeat = 0;

    // Save data to database
    fwrite(&newTrip, sizeof(trip), 1, ntrip);
    fclose(ntrip);

    return 0;
}