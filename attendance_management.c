
#include <stdio.h>

#define MAX_STUDENTS 10
#define SUBJECTS 3
#define MAX_CLASSES 50

struct Student {
    int roll;
    char name[50];
};

// Shared data
extern struct Student students[MAX_STUDENTS];
extern int studentCount;

extern char subject[SUBJECTS][30];

extern int attendance[MAX_STUDENTS][SUBJECTS][MAX_CLASSES];
extern int classCount[SUBJECTS];

void attendanceManagement() {

    if(studentCount == 0) {
        printf("\nPlease add students first!\n");
        return;
    }

    int choice;

    do {
        printf("\n===== ATTENDANCE MANAGEMENT =====\n");
        printf("1. Mark Attendance\n");
        printf("2. View Attendance Percentage\n");
        printf("0. Back to Main Menu\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {

            for(int s = 0; s < SUBJECTS; s++) {

                int n;

                printf("\nSubject: %s\n", subject[s]);

                printf("Enter number of NEW classes: ");
                scanf("%d", &n);

                if(n <= 0 || n > MAX_CLASSES - classCount[s]) {
                    printf("Invalid number of classes!\n");
                    break;
                }

                for(int c = classCount[s];
                    c < classCount[s] + n; c++) {

                    printf("\nClass %d\n", c + 1);

                    for(int i = 0; i < studentCount; i++) {

                        int status;

                        printf("%s (1=Present, 0=Absent): ",
                               students[i].name);

                        scanf("%d", &status);

                        while(status != 0 && status != 1) {
                            printf("Enter 1 or 0: ");
                            scanf("%d", &status);
                        }

                        attendance[i][s][c] = status;
                    }
                }

                classCount[s] += n;
            }

            printf("\nAttendance updated successfully!\n");
        }

        else if(choice == 2) {

            for(int i = 0; i < studentCount; i++) {

                printf("\n%s (Roll: %d)\n",
                       students[i].name, students[i].roll);

                for(int j = 0; j < SUBJECTS; j++) {

                    int present = 0;

                    for(int k = 0; k < classCount[j]; k++) {
                        if(attendance[i][j][k] == 1)
                            present++;
                    }

                    float percentage = 0;

                    if(classCount[j] > 0) {
                        percentage =
                        (present * 100.0) / classCount[j];
                    }

                    printf("%s: %.2f%%\n",
                           subject[j], percentage);
                }
            }
        }

        else if(choice == 0) {
            printf("Returning to Main Menu...\n");
        }

        else {
            printf("Invalid choice!\n");
        }

    } while(choice != 0);
}
