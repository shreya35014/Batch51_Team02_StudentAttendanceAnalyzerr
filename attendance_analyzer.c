#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define SUBJECTS 3
#define MAX_CLASSES 50
#define LIMIT 75.0

// Student structure
struct Student {
    int roll;
    char name[50];
};

// Global variables
struct Student students[MAX_STUDENTS];

char subject[SUBJECTS][30] = {
    "Mathematics",
    "Programming",
    "Physics"
};

int attendance[MAX_STUDENTS][SUBJECTS][MAX_CLASSES];

int classCount[SUBJECTS] = {0};

int studentCount = 0;


// FUNCTION 1: STUDENT MANAGEMENT

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


// FUNCTION 2: ATTENDANCE MANAGEMENT

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


// FUNCTION 3: ATTENDANCE REPORT

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

                printf("\nOverall Attendance: %.2f%%\n",
                       overall);

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

                    printf("\nWARNING: %s\n",
                           students[i].name);

                    printf("Roll Number: %d\n",
                           students[i].roll);

                    printf("Attendance: %.2f%%\n",
                           percentage);

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


// MAIN FUNCTION

int main() {

    int choice;

    do {

        printf("\n================================\n");
        printf("       ATTENDEASE 2.0\n");
        printf(" STUDENT ATTENDANCE ANALYZER\n");
        printf("================================\n");

        printf("1. Student Management\n");
        printf("2. Attendance Management\n");
        printf("3. Attendance Report\n");
        printf("4. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                studentManagement();
                break;

            case 2:
                attendanceManagement();
                break;

            case 3:
                attendanceReport();
                break;

            case 4:
                printf("\nThank you for using AttendEase!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 4);

    return 0;
}
