
#include <stdio.h>

#define MAX_STUDENTS 10
#define SUBJECTS 3
#define MAX_CLASSES 50
#define LIMIT 75.0

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

void attendanceReport() {

    if(studentCount == 0) {
        printf("\nNo students registered!\n");
        return;
    }

    int choice;

    do {
        printf("\n===== ATTENDANCE REPORT =====\n");
        printf("1. Complete Student Report\n");
        printf("2. Students Below 75%%\n");
        printf("3. Class Attendance Summary\n");
        printf("0. Back to Main Menu\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1) {

            for(int i = 0; i < studentCount; i++) {

                int totalPresent = 0;
                int totalClasses = 0;

                printf("\n-----------------------------\n");
                printf("Roll Number: %d\n", students[i].roll);
                printf("Name: %s\n", students[i].name);

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

                    totalPresent += present;
                    totalClasses += classCount[j];
                }

                float overall = 0;

                if(totalClasses > 0) {
                    overall =
                    (totalPresent * 100.0) / totalClasses;
                }

                printf("\nOverall Attendance: %.2f%%\n", overall);

                if(totalClasses == 0) {
                    printf("Status: NO ATTENDANCE RECORDED\n");
                }

                else if(overall < LIMIT) {
                    printf("\n*** LOW ATTENDANCE WARNING! ***\n");
                    printf("Attendance is below 75%%.\n");
                    printf("Immediate improvement required!\n");
                }

                else {
                    printf("Status: GOOD\n");
                }
            }
        }

        else if(choice == 2) {

            int found = 0;

            printf("\n===== STUDENTS BELOW 75%% =====\n");

            for(int i = 0; i < studentCount; i++) {

                int present = 0;
                int total = 0;

                for(int j = 0; j < SUBJECTS; j++) {
                    for(int k = 0; k < classCount[j]; k++) {

                        if(attendance[i][j][k] == 1)
                            present++;

                        total++;
                    }
                }

                if(total == 0)
                    continue;

                float percentage =
                (present * 100.0) / total;

                if(percentage < LIMIT) {

                    printf("\nWARNING: %s\n", students[i].name);
                    printf("Roll Number: %d\n", students[i].roll);
                    printf("Attendance: %.2f%%\n", percentage);

                    found = 1;
                }
            }

            if(!found) {
                printf("No students below 75%%!\n");
            }
        }

        else if(choice == 3) {

            printf("\n===== CLASS SUMMARY =====\n");

            for(int j = 0; j < SUBJECTS; j++) {

                int present = 0;
                int absent = 0;

                for(int i = 0; i < studentCount; i++) {
                    for(int k = 0; k < classCount[j]; k++) {

                        if(attendance[i][j][k] == 1)
                            present++;
                        else
                            absent++;
                    }
                }

                printf("\nSubject: %s\n", subject[j]);
                printf("Present: %d\n", present);
                printf("Absent: %d\n", absent);
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
