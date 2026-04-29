#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 100

struct Request {
    int id;
    int priority;
    char equip[50];
    char issue[100];
    struct Request *next;
};

struct Request *head = NULL;

struct Request *comFront = NULL;
struct Request *comRear = NULL;

char history[MAX_HISTORY][100];
int historyCount = 0;

void clearBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void logHistory(char *action, struct Request *r) {
    if (historyCount < MAX_HISTORY) {
        sprintf(history[historyCount],
            "[%s] ID:%d | %s | Priority:%d",
            action,
             r->id,
             r->equip,
             r->priority);
        historyCount++;
    }
}

void addRequest() {
    struct Request *newRequest = (struct Request*)malloc(sizeof(struct Request));
    int ch;
    
    while (1) {
        printf("Enter ID: ");
        scanf("%d", &newRequest->id);

        struct Request *check = head;
        int duplicate = 0;
        while (check != NULL) {
            if (check->id == newRequest->id) {
                duplicate = 1;
                break;
            }
            check = check->next;
        }

        if (!duplicate) break;
        printf("ID already exists! Try again.\n");
    }

     clearBuffer();

    printf("Enter Equipment Name: ");
    fgets(newRequest->equip, sizeof(newRequest->equip), stdin);
    if (newRequest->equip[strlen(newRequest->equip) - 1] == '\n')
        newRequest->equip[strlen(newRequest->equip) - 1] = '\0';
    printf("Enter Issue Description: ");
    fgets(newRequest->issue, sizeof(newRequest->issue), stdin);
    if (newRequest->issue[strlen(newRequest->issue) - 1] == '\n')
        newRequest->issue[strlen(newRequest->issue) - 1] = '\0';

         while (1) {
        printf("Enter Priority Level (1-High, 2-Medium, 3-Low): ");
        scanf("%d", &newRequest->priority);
        if (newRequest->priority >= 1 && newRequest->priority <= 3) break;
        printf("Invalid priority! Try again.\n");
    }

    newRequest->next = NULL;

    if (head == NULL) {
        head = newRequest;
    } else {
        struct Request *temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newRequest;
    }

    logHistory("ADDED", newRequest);
    printf("\nRequest added successfully!\n");
}


void viewRequests() {
    struct Request *temp = head;
    if (temp == NULL) {
        printf("No requests to display.\n");
        return;
    }
    printf("------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-20s | %-30s |\n", "ID", "Priority", "Equipment", "Description");
    printf("------------------------------------------------------------------------------\n");
      while (temp != NULL) {
        char *p;
        if (temp->priority == 1) p = "High";
        else if (temp->priority == 2) p = "Medium";
        else p = "Low";

        printf("| %-5d | %-10s | %-20s | %-30s |\n",
               temp->id, p, temp->equip, temp->issue);

        printf("------------------------------------------------------------------------------\n");
        temp = temp->next;
    }
}

void updateRequest() {
    int id, ch;
   printf("Enter ID to update: ");
    scanf("%d", &id);

    struct Request *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            clearBuffer();
            
            printf("Enter new Equipment Name: ");
            fgets(temp->equip, sizeof(temp->equip), stdin);
            if (temp->equip[strlen(temp->equip) - 1] == '\n')
                temp->equip[strlen(temp->equip) - 1] = '\0';
            printf("Enter new Issue Description: ");
            fgets(temp->issue, sizeof(temp->issue), stdin);
            if (temp->issue[strlen(temp->issue) - 1] == '\n')
                temp->issue[strlen(temp->issue) - 1] = '\0';
            while (1) {
                printf("Enter new Priority (1-High, 2-Medium, 3-Low): ");
                scanf("%d", &temp->priority);
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



void searchRequest() {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    struct Request *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
             printf("------------------------------------------------------------------------------\n");
            printf("| %-5s | %-10s | %-20s | %-30s |\n", "ID", "Priority", "Equipment", "Description");
             printf("------------------------------------------------------------------------------\n");
            printf("| %-5d | %-10d | %-20s | %-30s |\n", temp->id, temp->priority, temp->equip, temp->issue);
             printf("------------------------------------------------------------------------------\n");
            return;
        }
        temp = temp->next;
    }
    printf("\nRequest with ID %d not found.\n", id);
}

void processRequest() {
    if (head == NULL) {
        printf("\nNo requests to process.\n");
        return;
    }

    struct Request *temp = head;
    struct Request *prev = NULL;

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


void deleteRequest() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

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

void viewCompleted() {
    struct Request *temp = comFront;
    if (temp == NULL) {
        printf("No completed requests.\n");
        return;
    }

    printf("\n==============================================================================\n");
    printf("                             COMPLETED REQUESTS                                 \n");
    printf("================================================================================\n");
    while (temp != NULL) {
        printf("ID: %d | %s | Priority: %d\n",
               temp->id, temp->equip, temp->priority);
               printf("==============================================================================\n");    
        temp = temp->next;
    }
}

void viewHistory() {
    if (historyCount == 0) {
        printf("\nNo history available.\n");
        return;
    }

    printf("\n==============================================================================\n");
    printf("                               VIEW HISTORY                                     \n");
    printf("================================================================================\n");

    for (int i = 0; i < historyCount; i++) {
        printf("%s\n", history[i]);
        printf("============================================================================\n");
    }
}


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
        scanf("%d", &choice);

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