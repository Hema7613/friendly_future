#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 20
#define MAX_RESERVATIONS 50

typedef struct {
    int tableNumber;
    int capacity;
    int isAvailable;
} Table;

typedef struct {
    char customerName[50];
    char contactNumber[15];
    int numberOfGuests;
    int tableNumber;
    char reservationTime[20];
    int checkedIn;
} Reservation;

void initializeTables(Table tables[], int size) {
    int capacities[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,6, 6, 6, 6, 6, 8, 8, 8, 8, 8};
    for (int i = 0; i < size; i++) {
        tables[i].tableNumber = i + 1;
        tables[i].capacity = capacities[i];
        tables[i].isAvailable = 1; // All tables are initially available
    }
}
void displayAvailableTables(Table tables[], int size) {
    printf("Available Tables:\n");
    for (int i = 0; i < size; i++) {
        if (tables[i].isAvailable) {
            printf("Table Number: %d, Capacity: %d\n", tables[i].tableNumber, tables[i].capacity);
        }
    }
}
int bookTable(Table tables[], int size, Reservation *reservation) {
    for (int i = 0; i < size; i++) {
        if (tables[i].isAvailable && tables[i].capacity >= reservation->numberOfGuests) {
            tables[i].isAvailable = 0;
            reservation->tableNumber = tables[i].tableNumber;
            return 1; // Booking successful
        }
    }
    return 0; // Booking failed
}
void onlineBooking(Table tables[], int size, Reservation reservations[], int *reservationCount) {
    if (*reservationCount >= MAX_RESERVATIONS) {
        printf("No more reservations can be made.\n");
        return;
    }

    Reservation newReservation;
    printf("Enter customer name: ");
    scanf(" %[^\n]", newReservation.customerName);
    printf("Enter contact number: ");
    scanf(" %[^\n]", newReservation.contactNumber);
    printf("Enter number of guests: ");
    scanf("%d", &newReservation.numberOfGuests);
    printf("Enter reservation time: ");
    scanf(" %[^\n]", newReservation.reservationTime);
    newReservation.checkedIn = 0;

    if (bookTable(tables, size, &newReservation)) {
        reservations[*reservationCount] = newReservation;
        (*reservationCount)++;
        printf("Table booked successfully!\n");
    } else {
        printf("No available table for the specified number of guests.\n");
    }
}
void checkIn(Reservation reservations[], int size) {
    char customerName[50];
    printf("Enter customer name for check-in: ");
    scanf(" %[^\n]", customerName);

    for (int i = 0; i < size; i++) {
        if (strcmp(reservations[i].customerName, customerName) == 0 && reservations[i].checkedIn == 0) {
            reservations[i].checkedIn = 1;
            printf("Check-in successful for %s.\n", customerName);
            return;
        }
    }
    printf("Reservation not found or already checked in.\n");
}

void checkOut(Table tables[], int size, Reservation reservations[], int *reservationCount) {
    char customerName[50];
    printf("Enter customer name for check-out: ");
    scanf(" %[^\n]", customerName);

    for (int i = 0; i < *reservationCount; i++) {
        if (strcmp(reservations[i].customerName, customerName) == 0 && reservations[i].checkedIn == 1) {
            int tableNumber = reservations[i].tableNumber;
            for (int j = 0; j < size; j++) {
                if (tables[j].tableNumber == tableNumber) {
                    tables[j].isAvailable = 1;
                    break;
                }
            }
            for (int k = i; k < *reservationCount - 1; k++) {
                reservations[k] = reservations[k + 1];
            }
            (*reservationCount)--;
            printf("Check-out successful. Table %d is now available.\n", tableNumber);
            return;
        }
    }
    printf("Reservation not found or not checked in.\n");
}
void displayReservations(Reservation reservations[], int size) {
    printf("Reservations:\n");
    for (int i = 0; i < size; i++) {
        if (reservations[i].tableNumber != 0) {
            printf("Customer: %s, Contact: %s, Guests: %d, Table: %d, Time: %s, Checked In: %s\n",
                   reservations[i].customerName, reservations[i].contactNumber,
                   reservations[i].numberOfGuests, reservations[i].tableNumber,
                   reservations[i].reservationTime, reservations[i].checkedIn ? "Yes" : "No");
        }
    }
}
void displayCheckIns(Reservation reservations[], int size) {
    printf("Checked-In Reservations:\n");
    for (int i = 0; i < size; i++) {
        if (reservations[i].checkedIn) {
            printf("Customer: %s, Contact: %s, Guests: %d, Table: %d, Time: %s\n",
                   reservations[i].customerName, reservations[i].contactNumber,
                   reservations[i].numberOfGuests, reservations[i].tableNumber,
                   reservations[i].reservationTime);
        }
    }
}
int main() {
    Table tables[MAX_TABLES];
    Reservation reservations[MAX_RESERVATIONS];
    int reservationCount = 0;

    initializeTables(tables, MAX_TABLES);

    while (1) {
        int choice;
        printf("\n1. Display Available Tables\n2. Online Booking\n3. Check-In\n4. Check-Out\n5. Display Reservations\n6. Display Check-Ins\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableTables(tables, MAX_TABLES);
                break;
            case 2:
                onlineBooking(tables, MAX_TABLES, reservations, &reservationCount);
                break;
            case 3:
                checkIn(reservations, reservationCount);
                break;
            case 4:
                checkOut(tables, MAX_TABLES, reservations, &reservationCount);
                break;
            case 5:
                displayReservations(reservations, reservationCount);
                break;
            case 6:
                displayCheckIns(reservations, reservationCount);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}

