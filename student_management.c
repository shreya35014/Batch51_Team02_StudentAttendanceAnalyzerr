
#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10

struct Student {
    int roll;
    char name[50];
};

// Shared student data
struct Student students[MAX_STUDENTS];
int studentCount = 0;

void studentManagement() {

    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT =====\n");
        printf("1. Add Students\n");
        printf("2. Search Student\n");
        printf("0. Back to Main Menu\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {

            int n;

            printf("How many students to add? ");
            scanf("%d", &n);

            if(n <= 0 || n > MAX_STUDENTS - studentCount) {
                printf("Invalid number of students!\n");
                continue;
            }

            for(int i = 0; i < n; i++) {

                int roll, duplicate = 0;

                printf("\nEnter Roll Number: ");
                scanf("%d", &roll);

                for(int j = 0; j < studentCount; j++) {
                    if(students[j].roll == roll) {
                        duplicate = 1;
                        break;
                    }
                }

                if(duplicate) {
                    printf("Roll number already exists!\n");
                    i--;
                    continue;
                }

                students[studentCount].roll = roll;

                printf("Enter Student Name: ");
                scanf(" %49[^\n]", students[studentCount].name);

                studentCount++;

                printf("Student added successfully!\n");
            }
        }

        else if(choice == 2) {

            int roll, found = 0;

            printf("Enter Roll Number: ");
            scanf("%d", &roll);

            for(int i = 0; i < studentCount; i++) {

                if(students[i].roll == roll) {

                    printf("\nStudent Found!\n");
                    printf("Name: %s\n", students[i].name);
                    printf("Roll Number: %d\n", students[i].roll);

                    found = 1;
                    break;
                }
            }

            if(!found)
                printf("Student not found!\n");
        }

        else if(choice == 0) {
            printf("Returning to Main Menu...\n");
        }

        else {
            printf("Invalid choice!\n");
        }

    } while(choice != 0);
}
