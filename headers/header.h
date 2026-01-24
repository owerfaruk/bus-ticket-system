typedef struct {
    int tripId;                 
    char pointTo[50];           
    char pointFrom[50];          
    char date[20];               
    char time[10];               
    char plate[15];            
    char driverName[50];        
    int seatTotal;             
    int selledSeat;            
    char ticketPrice[10];      
} trip;

typedef struct {
    int tripId;               
    int ticketId;                
    char name[50];             
    int seatNum;                 
} ticket;

void menu();
int createTrip();
int updateTrip();
int deleteTrip();
int inquiryTrip();
int listAllTrips();
int sellTicket();
int deleteTicket();