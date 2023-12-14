//Project Title : Hotel Reservation System
//User sign-up and login
//Real-time room status
//Booking, changes, or cancellations
//Booking history
//Team Name : System React
//Team Leader : Mir Rabbi (C233273)
//Team Member’s : Tanjim Mahmud (C233259)
//Joytu Das Nobo (C233262)
//Md Shoibul Islam (C233274)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 10
#define MAX_USERS 10
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    int roomNumber;
    char status[20];  // "Available", "Booked", etc.
} Room;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int bookedRoom;
} User;

Room rooms[MAX_ROOMS];
User users[MAX_USERS];
User currentUser;

// Function prototypes
void displayMenu();
void userSignUp();
void userLogin();
void bookRoom();
void viewBookingHistory();
void cancelBooking();

int main() {
    // Initialize rooms
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        strcpy(rooms[i].status, "Available");
    }

    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                userSignUp();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                bookRoom();
                break;
            case 4:
                viewBookingHistory();
                break;
            case 5:
                cancelBooking();
                break;
            case 6:
                printf("Exiting the program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() {
    printf("\n=== Hotel Reservation System ===\n");
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Book a Room\n");
    printf("4. View Booking History\n");
    printf("5. Cancel Booking\n");
    printf("6. Exit\n");

    printf("\nReal-time Room Status:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %d: %s\n", rooms[i].roomNumber, rooms[i].status);
    }
}

void userSignUp() {
    if (currentUser.username[0] != '\0') {
        printf("You are already logged in. Logout to create a new account.\n");
        return;
    }

    printf("Enter your username: ");
    scanf("%s", currentUser.username);

    // Check if the username already exists
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, currentUser.username) == 0) {
            printf("Username already exists. Please choose a different username.\n");
            return;
        }
    }

    printf("Enter your password: ");
    scanf("%s", currentUser.password);

    printf("Account created successfully!\n");
}

void userLogin() {
    if (currentUser.username[0] != '\0') {
        printf("You are already logged in. Logout to log in with a different account.\n");
        return;
    }

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            currentUser = users[i];
            printf("Login successful!\n");
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
}

void bookRoom() {
    if (currentUser.username[0] == '\0') {
        printf("You need to log in first to book a room.\n");
        return;
    }

    if (currentUser.bookedRoom != 0) {
        printf("You already have a booked room (%d). Cancel the existing booking to book a new room.\n", currentUser.bookedRoom);
        return;
    }

    printf("Available rooms:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (strcmp(rooms[i].status, "Available") == 0) {
            printf("Room %d\n", rooms[i].roomNumber);
        }
    }

    int roomNumber;
    printf("Enter the room number you want to book: ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
        printf("Invalid room number. Please try again.\n");
        return;
    }

    if (strcmp(rooms[roomNumber - 1].status, "Available") == 0) {
        strcpy(rooms[roomNumber - 1].status, "Booked");
        currentUser.bookedRoom = roomNumber;
        printf("Room %d booked successfully!\n", roomNumber);
    } else {
        printf("Room %d is not available. Please choose another room.\n", roomNumber);
    }
}

void viewBookingHistory() {
    if (currentUser.username[0] == '\0') {
        printf("You need to log in first to view booking history.\n");
        return;
    }

    if (currentUser.bookedRoom != 0) {
        printf("You have booked Room %d.\n", currentUser.bookedRoom);
    } else {
        printf("You don't have any booked rooms.\n");
    }
}

void cancelBooking() {
    if (currentUser.username[0] == '\0') {
        printf("You need to log in first to cancel a booking.\n");
        return;
    }

    if (currentUser.bookedRoom != 0) {
        int roomNumber = currentUser.bookedRoom;
        strcpy(rooms[roomNumber - 1].status, "Available");
        printf("Booking for Room %d canceled successfully!\n", roomNumber);
        currentUser.bookedRoom = 0;
    } else {
        printf("You don't have any booked rooms to cancel.\n");
    }
}
