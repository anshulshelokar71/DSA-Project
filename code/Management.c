#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEACHERS 100
#define MAX_STUDENTS 100
#define MAX_ATTENDANCE 100
#define MAX_PERFORMANCE 100

char admin_username[] = "admin";
char admin_password[] = "dmin@U$T";

char teacher_username[MAX_TEACHERS][50];
char teacher_password[MAX_TEACHERS][50];
int num_teachers = 0;

char student_username[MAX_STUDENTS][50];
char student_password[MAX_STUDENTS][50];
int num_students = 0;

char attendence_date[MAX_ATTENDANCE][20];
char attend_student[MAX_ATTENDANCE][50];
int num_attendance = 0;

char performance[MAX_PERFORMANCE][50];
char per_student[MAX_PERFORMANCE][50];
int num_performance = 0;

void createAccount(char type);
void delAccount(char type);
void seePerformance(char type);
void changePassword();

void teacher_givePerformance(char *username);
void teacher_seeAttendance();
void teacher_seePerformance(char *username);

void student_giveAttendance(char *username);
void student_seePerformance(char *username);

int main() {
    char username[50];
    char password[50];
    int choice;

    do {
        printf("Enter the type of account you want to log in:\n");
        printf("1. Admin\n2. Teacher\n3. Student\n4. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
                    // Admin logged in
                    int option;
                    do {
                        printf("1. Change password\n");
                        printf("2. Create teacher account\n");
                        printf("3. Create student account\n");
                        printf("4. Delete teacher account\n");
                        printf("5. Delete student account\n");
                        printf("6. See teacher performance\n");
                        printf("7. See student performance\n");
                        printf("8. Logout\n");
                        scanf("%d", &option);
                        switch (option) {
                            case 1:
                                // Change admin password
                                changePassword();
                                break;
                            case 2:
                                // Create teacher account
                                createAccount('t');
                                break;
                            case 3:
                                // Create student account
                                createAccount('s');
                                break;
                            case 4:
                                // Delete teacher account
                                delAccount('t');
                                break;
                            case 5:
                                // Delete student account
                                delAccount('s');
                                break;
                            case 6:
                                // See teacher performance
                                seePerformance('t');
                                break;
                            case 7:
                                // See student performance
                                seePerformance('s');
                                break;
                        }
                    } while (option != 8);
                } else {
                    printf("Wrong username or password.\n");
                }
                break;
            case 2:
                // Teacher login
                printf("Enter teacher username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                // Implement teacher functionalities
                teacher_givePerformance(username);
                break;
            case 3:
                // Student login
                printf("Enter student username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                // Implement student functionalities
                student_giveAttendance(username);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}

void createAccount(char type) {
    char name[50], pass[50];
    printf("Enter %s name: ", (type == 't') ? "teacher" : "student");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", pass);
    if (type == 't') {
        strcpy(teacher_username[num_teachers], name);
        strcpy(teacher_password[num_teachers], pass);
        num_teachers++;
    } else {
        strcpy(student_username[num_students], name);
        strcpy(student_password[num_students], pass);
        num_students++;
    }
    printf("%s account created successfully.\n", (type == 't') ? "Teacher" : "Student");
}

void delAccount(char type) {
    char name[50], pass[50];
    printf("Enter %s name: ", (type == 't') ? "teacher" : "student");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", pass);
    int i;
    if (type == 't') {
        for (i = 0; i < num_teachers; i++) {
            if (strcmp(teacher_username[i], name) == 0 && strcmp(teacher_password[i], pass) == 0) {
                for (int j = i; j < num_teachers - 1; j++) {
                    strcpy(teacher_username[j], teacher_username[j + 1]);
                    strcpy(teacher_password[j], teacher_password[j + 1]);
                }
                num_teachers--;
                printf("Teacher account deleted successfully.\n");
                return;
            }
        }
    } else {
        for (i = 0; i < num_students; i++) {
            if (strcmp(student_username[i], name) == 0 && strcmp(student_password[i], pass) == 0) {
                for (int j = i; j < num_students - 1; j++) {
                    strcpy(student_username[j], student_username[j + 1]);
                    strcpy(student_password[j], student_password[j + 1]);
                }
                num_students--;
                printf("Student account deleted successfully.\n");
                return;
            }
        }
    }
    printf("Account not found or incorrect password.\n");
}

void seePerformance(char type) {
    int i;
    if (type == 't') {
        printf("Teacher\t-> Performance\n");
        for (i = 0; i < num_teachers; i++) {
            printf("%s\t-> <Performance Details>\n", teacher_username[i]);
        }
    } else {
        printf("Student\t-> Performance\n");
        for (i = 0; i < num_students; i++) {
            printf("%s\t-> <Performance Details>\n", student_username[i]);
        }
    }
}

void changePassword() {
    printf("Enter new username: ");
    scanf("%s", admin_username);
    printf("Enter new password: ");
    scanf("%s", admin_password);
    printf("Password changed successfully.\n");
}

void teacher_givePerformance(char *username) {
    char student[50], performance[50];
    printf("Enter student name: ");
    scanf("%s", student);
    printf("Enter performance: ");
    scanf("%s", performance);
    // Save performance data
}

void teacher_seeAttendance() {
    // Implement attendance viewing logic for teacher
}

void teacher_seePerformance(char *username) {
    // Implement performance viewing logic for teacher
}

void student_giveAttendance(char *username) {
    char date[20];
    printf("Enter date and month: ");
    scanf("%s", date);
    // Save attendance data
}

void student_seePerformance(char *username) {
    // Implement performance viewing logic for student
}
