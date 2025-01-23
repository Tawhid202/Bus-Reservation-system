#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 10    ///Maximum number of buses
#define MAX_SEATS 10    /// Maximum number of seats per bus
#define BUS_FILE "buses.txt"  /// File to store bus information
#define CUSTOMER_FILE "customers.txt" /// File to store customer information

typedef struct {
    char busNumber[10];
    char driver[50];
    char startTime[10];   /// Format: HH:MM
    char reachTime[10];   /// Format: HH:MM
    char destination[50];
    char place[50];
    int seats[MAX_SEATS];
} Bus;

typedef struct {
    char name[100];
    char id[10];
    char phone[15];
    int age;
    char address[100];
} Customer;

Bus buses[MAX_BUSES];               /// Array to store bus data
Customer customers[MAX_BUSES];      /// Array to store customer data
int busCount = 0;                    /// Number of buses
int customerCount = 0;               ///Number of customers

void saveBusesToFile() {
    FILE* fp = fopen(BUS_FILE, "w");
    if (!fp) {
        printf("Error saving bus data!\n");
        return;
    }
    for (int i = 0; i < busCount; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s",
                buses[i].busNumber, buses[i].driver,
                buses[i].startTime, buses[i].reachTime,
                buses[i].destination, buses[i].place);
        for (int j = 0; j < MAX_SEATS; j++) {
            fprintf(fp, ",%d", buses[i].seats[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Bus data saved to file successfully.\n");
}

void loadBusesFromFile() {
    FILE* fp = fopen(BUS_FILE, "r");
    if (!fp) {
        printf("No saved bus data found, starting with empty data.\n");
        return;
    }
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
           buses[busCount].busNumber, buses[busCount].driver,
           buses[busCount].startTime, buses[busCount].reachTime,
           buses[busCount].destination, buses[busCount].place) != EOF) {

        for (int j = 0; j < MAX_SEATS; j++) {
            fscanf(fp, ",%d", &buses[busCount].seats[j]);
        }
        busCount++;
    }
    fclose(fp);
    printf("Bus data loaded from file successfully.\n");
}

void saveCustomersToFile() {
    FILE* fp = fopen(CUSTOMER_FILE, "w");
    if (!fp) {
        printf("Error saving customer data!\n");
        return;
    }
    for (int i = 0; i < customerCount; i++) {
        fprintf(fp, "%s,%s,%s,%d,%s\n",
                customers[i].name, customers[i].id, customers[i].phone, customers[i].age, customers[i].address);
    }
    fclose(fp);
    printf("Customer data saved to file successfully.\n");
}

void loadCustomersFromFile() {
    FILE* fp = fopen(CUSTOMER_FILE, "r");
    if (!fp) {
        printf("No saved customer data found, starting without customers.\n");
        return;
    }
    while (fscanf(fp, "%[^,],%[^,],%s\n",
           customers[customerCount].name,
           customers[customerCount].id,
           customers[customerCount].phone) != EOF) {
        customerCount++;
    }
    fclose(fp);
    printf("Customer data loaded from file successfully.\n");
}

void addBusInfo() {
    if (busCount >= MAX_BUSES) {
        printf("Cannot add more buses. Maximum limit reached.\n");
        return;
    }
    printf("Enter bus number: ");
    scanf("%s", buses[busCount].busNumber);
    printf("Enter driver's name: ");
    scanf("%s", buses[busCount].driver);
    printf("Enter starting time (HH:MM): ");
    scanf("%s", buses[busCount].startTime);
    printf("Enter reaching time (HH:MM): ");
    scanf("%s", buses[busCount].reachTime);
    printf("Enter destination: ");
    scanf("%s", buses[busCount].destination);
    printf("Enter place: ");
    scanf("%s", buses[busCount].place);

    // Initialize seats as available (0)
    for (int j = 0; j < MAX_SEATS; j++) {
        buses[busCount].seats[j] = 0; // Initialize seats as available
    }
    busCount++; // Increment the count of buses
    printf("Bus information added successfully!\n");
}

void viewBuses() {
    printf("Available Buses:\n");
    for (int i = 0; i < busCount; i++) {
        printf("Bus Number: %s, Driver: %s, Start Time: %s, Reach Time: %s, Destination: %s, Place: %s\n",
               buses[i].busNumber, buses[i].driver, buses[i].startTime, buses[i].reachTime,
               buses[i].destination, buses[i].place);
    }
}

void showBusStatus() {
    printf("Bus Booking Status:\n");
    for (int i = 0; i < busCount; i++) {
        printf("Bus Number: %s to %s: ", buses[i].busNumber, buses[i].destination);
        for (int j = 0; j < MAX_SEATS; j++) {
            printf("%s ", buses[i].seats[j] == 0 ? "Available" : "Booked");
        }
        printf("\n");
    }
}

void customerInfo() {
    if (customerCount >= MAX_BUSES) {
        printf("Cannot add more customers. Maximum limit reached.\n");
        return;
    }

    printf("Enter customer name: ");
    scanf("%s", customers[customerCount].name);
    printf("Enter customer ID: ");
    scanf("%s", customers[customerCount].id);
    printf("Enter customer phone number: ");
    scanf("%s", customers[customerCount].phone);
    printf("Enter customer age: ");
    scanf("%d", customers[customerCount].age);
    printf("Enter customer address: ");
    scanf("%s", customers[customerCount].address);


    customerCount++; // Increment count of customers
    printf("Customer information added successfully!\n");
}

void modifyBusInfo() {
    char busNumber[10];
    printf("Enter bus number to modify: ");
    scanf("%s", busNumber);

    for (int i = 0; i < busCount; i++) {
        if (strcmp(buses[i].busNumber, busNumber) == 0) {
            printf("Modifying details for bus %s:\n", busNumber);
            printf("Enter new driver's name (current: %s): ", buses[i].driver);
            scanf("%s", buses[i].driver);
            printf("Enter new starting time (current: %s): ", buses[i].startTime);
            scanf("%s", buses[i].startTime);
            printf("Enter new reaching time (current: %s): ", buses[i].reachTime);
            scanf("%s", buses[i].reachTime);
            printf("Enter new destination (current: %s): ", buses[i].destination);
            scanf("%s", buses[i].destination);
            printf("Enter new place (current: %s): ", buses[i].place);
            scanf("%s", buses[i].place);
            printf("Bus information updated successfully!\n");
            return;
        }
    }
    printf("Bus not found!\n");
}

void modifyCustomerInfo() {
    char customerId[10];
    printf("Enter customer ID to modify: ");
    scanf("%s", customerId);

    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].id, customerId) == 0) {
            printf("Modifying details for customer %s:\n", customerId);
            printf("Enter new name (current: %s): ", customers[i].name);
            scanf("%s", customers[i].name);
            printf("Enter new phone number (current: %s): ", customers[i].phone);
            scanf("%s", customers[i].phone);
            printf("Customer information updated successfully!\n");
            return;
        }
    }
    printf("Customer not found!\n");
}

void bookTicket() {
    char busNumber[10];
    int seatNumber;

    printf("Enter bus number to book: ");
    scanf("%s", busNumber);

    printf("Enter seat number (1-%d): ", MAX_SEATS);
    if (scanf("%d", &seatNumber) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return;
    }
    seatNumber--; // Adjust for array index

    for (int i = 0; i < busCount; i++) {
        if (strcmp(buses[i].busNumber, busNumber) == 0) {
            if (seatNumber >= 0 && seatNumber < MAX_SEATS) {
                if (buses[i].seats[seatNumber] == 0) {
                    buses[i].seats[seatNumber] = 1; // Mark seat as booked
                    printf("Ticket booked successfully for %s on bus %s!\n", customers[customerCount - 1].name, busNumber);
                    return;
                } else {
                    printf("Seat already booked!\n");
                    return;
                }
            } else {
                printf("Invalid seat number!\n");
                return;
            }
        }
    }
    printf("Bus not found!\n");
}

void cancelBooking() {
    char busNumber[10];
    int seatNumber;

    printf("Enter bus number to cancel ticket: ");
    scanf("%s", busNumber);

    printf("Enter seat number (1-%d): ", MAX_SEATS);
    if (scanf("%d", &seatNumber) != 1) {
        printf("Invalid input! Please enter a number.\n");
        return;
    }
    seatNumber--; // Adjust for array index

    for (int i = 0; i < busCount; i++) {
        if (strcmp(buses[i].busNumber, busNumber) == 0) {
            if (seatNumber >= 0 && seatNumber < MAX_SEATS) {
                if (buses[i].seats[seatNumber] == 1) {
                    buses[i].seats[seatNumber] = 0; // Mark seat as available
                    printf("Booking canceled successfully!\n");
                    return;
                } else {
                    printf("No booking found for this seat!\n");
                    return;
                }
            } else {
                printf("Invalid seat number!\n");
                return;
            }
        }
    }
    printf("Bus not found!\n");
}

int main() {
    int option;

    loadBusesFromFile();   // Load buses from file at the start
    loadCustomersFromFile(); // Load customers from file at the start

    // Main loop
    do {
        printf("\nBus Reservation System\n");
        printf("1. View Buses\n");
        printf("2. Add Bus Info\n");
        printf("3. Modify Bus Info\n");
        printf("4. Customer Info\n");
        printf("5. Modify Customer Info\n");
        printf("6. Book Ticket\n");
        printf("7. Cancel Booking\n");
        printf("8. Show Bus Status\n");
        printf("9. Save Data\n");
        printf("10. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (option) {
            case 1: viewBuses(); break;
            case 2: addBusInfo(); break;
            case 3: modifyBusInfo(); break; // Modify bus information
            case 4: customerInfo(); break;   // Adding customer information
            case 5: modifyCustomerInfo(); break; // Modify customer information
            case 6: bookTicket(); break;
            case 7: cancelBooking(); break;
            case 8: showBusStatus(); break;
            case 9:
                saveBusesToFile();
                saveCustomersToFile();
                break; // Save bus and customer data to files
            case 10: printf("Exiting...\n"); break;
            default: printf("Invalid option!\n"); break;
        }
    } while (option != 10);

    return 0;
}

