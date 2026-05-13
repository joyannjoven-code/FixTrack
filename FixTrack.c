#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 100

// Structure to represent a maintenance request
struct Request {
    int id;              // Unique identifier for the request
    int priority;        // Priority level: 1-High, 2-Medium, 3-Low
    char equip[50];      // Equipment name
    char issue[100];     // Description of the issue
    struct Request *next; // Pointer to the next request in the list
};

// Global pointers for the pending requests linked list
struct Request *head = NULL;

// Global pointers for the completed requests queue
struct Request *comFront = NULL;
struct Request *comRear = NULL;

// Array to store history of actions
char history[MAX_HISTORY][100];
int historyCount = 0;

// Function to clear the input buffer
void clearBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Function to log actions in the history array
void logHistory(char *action, struct Request *r) {
    if (historyCount < MAX_HISTORY) {
        snprintf(history[historyCount], 100,
            "[%s] ID:%d | %s | Priority:%d",
            action,
            r->id,
            r->equip,
            r->priority);
        historyCount++;
    }
}

// Function to add a new maintenance request
// Uses Linked List: Allocates new node and appends to the end of the pending requests list
void addRequest() {
    struct Request *newRequest = (struct Request*)malloc(sizeof(struct Request));

    if (newRequest == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    while (1) {
        printf("Enter ID: ");
        if (scanf("%d", &newRequest->id) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        struct Request *check = head;
        int duplicate = 0;
        // Check for duplicate ID in pending requests
        while (check != NULL) {
            if (check->id == newRequest->id) {
                duplicate = 1;
                break;
            }
            check = check->next;
        }
        // Check for duplicate ID in completed requests
        if (!duplicate) {
            check = comFront;
            while (check != NULL) {
                if (check->id == newRequest->id) {
                    duplicate = 1;
                    break;
                }
                check = check->next;
            }
        }

        if (!duplicate) break;
        printf("ID already exists! Try again.\n");
    }

    printf("Enter Equipment Name: ");
    if (fgets(newRequest->equip, sizeof(newRequest->equip), stdin) == NULL) {
        printf("Input error!\n");
        return;
    }
    newRequest->equip[strcspn(newRequest->equip, "\n")] = '\0';
    
   printf("Enter Issue Description: ");
   if (fgets(newRequest->issue, sizeof(newRequest->issue), stdin) == NULL) {
    printf("Input error!\n");
    return;
}

newRequest->issue[strcspn(newRequest->issue, "\n")] = '\0';

        while (1) {
        printf("Enter Priority Level (1-High, 2-Medium, 3-Low): ");
        if (scanf("%d", &newRequest->priority) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        if (newRequest->priority >= 1 && newRequest->priority <= 3) break;
        printf("Invalid priority! Try again.\n");
    }
    newRequest->next = NULL;

    if (head == NULL) {
        head = newRequest;
    } else {
        struct Request *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newRequest;
    }

    logHistory("ADDED", newRequest);
    printf("\nRequest added successfully!\n");
}


// Function to display all pending requests in a table format
// Uses Linked List: Traverses the list and prints each node's data in a formatted table
void viewRequests() {
    struct Request *temp = head;
    if (temp == NULL) {
        printf("No requests to display.\n");
        return;
    }
    printf("------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-20.20s | %-30.30s |\n", "ID", "Priority", "Equipment", "Description");
    printf("------------------------------------------------------------------------------\n");
      while (temp != NULL) {
        char *p;
        if (temp->priority == 1) {
            p = "High";
        }
        else if (temp->priority == 2) {
            p = "Medium";
        }
        else {
            p = "Low";
        }
        
        printf("| %-5d | %-10s | %-20.20s | %-30.30s |\n",
       temp->id, p, temp->equip, temp->issue);

        printf("------------------------------------------------------------------------------\n");
        temp = temp->next;
    }
}

// Function to update an existing request by ID
// Uses Linked List: Traverses the list to find the node with matching ID and updates its fields
void updateRequest() {
    int id;
    printf("Enter ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    struct Request *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            
            printf("Enter new Equipment Name: ");
            if (fgets(temp->equip, sizeof(temp->equip), stdin) == NULL) {
                printf("Input error!\n");
                return;
            }
            temp->equip[strcspn(temp->equip, "\n")] = '\0';
            
            printf("Enter new Issue Description: ");
            if (fgets(temp->issue, sizeof(temp->issue), stdin) == NULL) {
                printf("Input error!\n");
                return;
            }
            temp->issue[strcspn(temp->issue, "\n")] = '\0';

            while (1) {
                printf("Enter new Priority (1-High, 2-Medium, 3-Low): ");
                if (scanf("%d", &temp->priority) != 1) {
                    printf("Invalid input. Please enter a number.\n");
                    clearBuffer();
                    continue;
                }
                clearBuffer();
                if (temp->priority >= 1 && temp->priority <= 3) break;
                printf("Invalid priority!\n");
            }

            logHistory("UPDATED", temp);
            printf("\nRequest updated successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("\nRequest not found.\n");
}

// Function to search and display a request by ID
// Uses Linked List: Linear search through the list to find the node with matching ID
void searchRequest() {
    int id;
    printf("Enter ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    struct Request *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
             printf("------------------------------------------------------------------------------\n");
            printf("| %-5s | %-10s | %-20.20s | %-30.30s |\n", "ID", "Priority", "Equipment", "Description");
             printf("------------------------------------------------------------------------------\n");
            char *p;
            if (temp->priority == 1) {
                p = "High";
            }
            else if (temp->priority == 2) {
                p = "Medium";
            }
            else {
                p = "Low";
            }
            printf("| %-5d | %-10s | %-20.20s | %-30.30s |\n", temp->id, p, temp->equip, temp->issue);
            printf("------------------------------------------------------------------------------\n");
            return;
        }
        temp = temp->next;
    }
    printf("\nRequest with ID %d not found.\n", id);
}

// Function to process the highest priority request and move it to completed queue
// Uses Linked List and Queue: Linear search in linked list to find node with lowest priority number,
// removes it from list, and enqueues it to the completed requests queue
void processRequest() {
    if (head == NULL) {
        printf("\nNo requests to process.\n");
        return;
    }

    struct Request *temp = head;
    struct Request *prev = NULL;

    // Find the request with the highest priority (lowest number)
    struct Request *highest = head;
    struct Request *highestPrev = NULL;

    while (temp != NULL) {
        if (temp->priority < highest->priority) {
            highest = temp;
            highestPrev = prev;
        }
        prev = temp;
        temp = temp->next;
    }

    if (highestPrev == NULL)
        head = highest->next;
    else
        highestPrev->next = highest->next;

    highest->next = NULL;

    if (comRear == NULL) {
        comFront = comRear = highest;
    }
    else {
        comRear->next = highest;
        comRear = highest;
    }

    logHistory("PROCESSED", highest);
    printf("\nProcessed request ID %d (Highest Priority)\n", highest->id);
}

// Function to delete a request by ID
// Uses Linked List: Traverses the list to find and remove the node with matching ID
void deleteRequest() {
    int id;
    printf("Enter ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clearBuffer();
        return;
    }
    clearBuffer();
    struct Request *temp = head, *prev = NULL;
       while (temp != NULL) {
        if (temp->id == id) {
            
            logHistory("DELETED", temp);
            
            if (prev == NULL) {
            head = temp->next;
            }
            else {
            prev->next = temp->next;
            } free(temp);
            
            printf("\nDeleted successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("\nRequest not found.\n");
}

// Function to display all completed requests
// Uses Queue: Traverses the completed requests queue from front to rear
void viewCompleted() {
    struct Request *temp = comFront;
    if (temp == NULL) {
        printf("No completed requests.\n");
        return;
    }

    printf("\n==============================================================================\n");
    printf("                             COMPLETED REQUESTS                                 \n");
    printf("==============================================================================\n");
    printf("| %-5s | %-10s | %-20.20s | %-30.30s |\n", "ID", "Priority", "Equipment", "Description");
    printf("------------------------------------------------------------------------------\n");
    while (temp != NULL) {
        char *p;
        if (temp->priority == 1) {
            p = "High";
        }
        else if (temp->priority == 2) {
            p = "Medium";
        }
        else {
            p = "Low";
        }
        printf("| %-5d | %-10s | %-20.20s | %-30.30s |\n",
            temp->id, p, temp->equip, temp->issue);
        printf("------------------------------------------------------------------------------\n");
        temp = temp->next;
    }
}

// Function to display the history of actions
// Uses Array: Iterates through the history array to display logged actions
void viewHistory() {
    if (historyCount == 0) {
        printf("\nNo history available.\n");
        return;
    }

    printf("\n==============================================================================\n");
    printf("                               VIEW HISTORY                                     \n");
    printf("==============================================================================\n");

    for (int i = 0; i < historyCount; i++) {
        printf("%s\n", history[i]);
        printf("==============================================================================\n");
    }
}


// Main function: displays menu and handles user choices
int main() {
    int choice;

    do {
        printf("==============================================================================\n");
        printf("              FixTrack: Campus Equipment Maintenance System                   \n");
        printf("==============================================================================\n");
        printf("1. Add Request\n");
        printf("2. View Requests\n");
        printf("3. Update Request\n");
        printf("4. Search Request\n");
        printf("5. Process Request\n");
        printf("6. Delete Request\n");
        printf("7. View Completed\n");
        printf("8. View History\n");
        printf("9. Exit\n");
        printf("==============================================================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        switch(choice) {
            case 1: addRequest();
                break;
            case 2: viewRequests();
                break;
            case 3: updateRequest();
                break;
            case 4: searchRequest();
                break;
            case 5: processRequest();
                break;
            case 6: deleteRequest();
                break;
            case 7: viewCompleted();
                break;
            case 8: viewHistory();
                break;
            case 9:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 9);
    return 0;
}
