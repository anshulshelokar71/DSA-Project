# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "Vector.c"
# include "Map_String.c"
#include <mysql/mysql.h>

char username[10] = "Tejas";
char password[10] = "Sanika";

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "DSA"

#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET   "\x1B[0m"

Vector teacher_username;
Vector teacher_password;
Vector student_username;
Vector student_password;
Vector attendence_date;
Vector attend_student;
Vector performance;
Vector per_student;
Map *individual;


MYSQL *db_connect() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

void db_disconnect(MYSQL *conn) {
    mysql_close(conn);
}

void changepassword() {

    printf("Enter username : ");
    scanf("%s", username);
    printf("Enter password : ");
    scanf("%s", password);
    
}


void teacheraccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    Vector_push_back(&teacher_username, n);
    Vector_push_back(&teacher_password, pass);
}


void deleteteacheraccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    if(Vector_search(&teacher_username, n) && Vector_search(&teacher_password, pass)) {
        Vector_erase_value(&teacher_username, n);
        Vector_erase_value(&teacher_password, pass);
    }
}




void teacher_list() {
    for(int i = 0; i < Vector_size(&teacher_username); i++) {
        printf("%d.  %s    %s\n", i+1, teacher_username.data[i], teacher_password.data[i]);
    }
} 



void studentaccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    Vector_push_back(&student_username, n);
    Vector_push_back(&student_password, pass);
}


void deletestudentaccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    if(Vector_search(&student_username, n) && Vector_search(&student_password, pass)) {
        Vector_erase_value(&student_username, n);
        Vector_erase_value(&student_password, pass);
    }
}


void student_list() {
    for(int i = 0; i < Vector_size(&student_username); i++) {
        printf("%d.  %s    %s\n", i+1, student_username.data[i], student_password.data[i]);
    }
} 






void teacher_givePerformance() {
    printf("Enter student name : ");
    char s[30];
    scanf("%s", s);

    if(Vector_search(&student_username, s)) {
        printf("Enter performance : ");
        char s2[30];
        scanf("%s", s2);
        Vector_push_back(&performance, s2);
        Vector_push_back(&per_student, s);
        map_insert(individual, s, s2);
    } else {
        printf("Student name not valid.:\n");
        printf("Press 1 to try again 0 to continue\n");
        int num;
        scanf("%d", &num);
        if(num==1)
            teacher_givePerformance();  
    }
}


void teacher_seeAttendence() {
    printf("Student Name -> ");
    printf("present date :\n");
    for(int i = 0; i < Vector_size(&attendence_date); i++) {
        printf("%s  ", attend_student.data[i]);
        printf("%s\n", attendence_date.data[i]);
    }
}


void teacher_seePerformance() {
    printf("1. individual performance \n");
    printf("2. collectively performance \n");
    int num;
    scanf("%d", &num);
    
    if(num==1) {
        printf("Enter student name : ");
        char s[30];
        scanf("%s", s);
        printf("Performance is : ");
        printf("%s\n", map_get(individual, s));

    } else if(num==2) {
        printf("Sudent -> Performance\n");
        for(int i = 0; i < Vector_size(&performance); i++) {
            printf("%s %s\n", per_student.data[i], performance.data[i]);
        }
    }
}










void student_giveAttendence(char* s1) {
    printf("Enter date and month : \n");
    char s[50];
    scanf("%s", s);
    Vector_push_back(&attendence_date, s);
    Vector_push_back(&attend_student, s1); 
}















void admin_createAccount() {

    printf("Enter your choice :\n");
    printf("1. create teacher account :\n");
    printf("2. create student account :\n");
    int num;
    scanf("%d", &num);
    if(num==1)
        teacheraccount();
    else if(num==2)
        studentaccount();

    printf("press 1 to create another account and 0 to continue \n");

    int v;
    scanf("%d", &v);
    if(v==1)
        admin_createAccount();
}


void admin_deleteAccount() {

    printf("1. delete teacher account :\n");
    printf("2. delete student account :\n");
    int num;
    scanf("%d", &num);
    if(num==1)
        deleteteacheraccount();
    else if(num==2)
        deletestudentaccount();

}


void admin_seePerformance() {
    printf("1. individual performance \n");
    printf("2. collectively performance \n");

    int num;
    scanf("%d", &num);
    
    if(num==1) {
        printf("Enter student name : ");
        char s[30];
        scanf("%s", s);
        printf("Performance is : ");
        printf("%s\n", map_get(individual, s));

    } else if(num==2) {
        printf("Sudent -> Performance\n");
        for(int i = 0; i < Vector_size(&performance); i++) {
            printf("%s %s\n", per_student.data[i], performance.data[i]);
        }
    }
}


void insertTeacherData(MYSQL *conn) {
    for (int i = 0; i < Vector_size(&teacher_username); i++) {
        char *username = teacher_username.data[i];
        char *password = teacher_password.data[i];

        char query[100];
        sprintf(query, "INSERT INTO teachers (username, password) VALUES ('%s', '%s')", username, password);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }
    }
}

void insertStudentData(MYSQL *conn) {
    for (int i = 0; i < Vector_size(&student_username); i++) {
        char *username = student_username.data[i];
        char *password = student_password.data[i];

        char query[100];
        sprintf(query, "INSERT INTO students (username, password) VALUES ('%s', '%s')", username, password);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }
    }
}

// void insertAttendanceData(MYSQL *conn) {
//     for (int i = 0; i < Vector_size(&attendence_date); i++) {
//         char *student = attend_student.data[i];
//         char *date = attendence_date.data[i];

//         char query[100];
//         sprintf(query, "INSERT INTO attendance (student, date) VALUES ('%s', '%s')", student, date);

//         if (mysql_query(conn, query)) {
//             fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
//             mysql_close(conn);
//             exit(1);
//         }
//     }
// }

// void insertPerformanceData(MYSQL *conn) {
//     char *performance[100];
//     for (int i = 0; i < Vector_size(&performance); i++) {
//         char *student = per_student.data[i];
//         performance[i] = Vector_get(&performance, i);

//         char query[100];
//         sprintf(query, "INSERT INTO performance (student, performance) VALUES ('%s', '%s')", student, performance);

//         if (mysql_query(conn, query)) {
//             fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
//             mysql_close(conn);
//             exit(1);
//         }
//     }
// }





void saveDataToCSV(const char *filename1, const char *filename2, const char *filename3, const char *filename4) {
    FILE *file1 = fopen(filename1, "w");
    if (file1 == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        exit(EXIT_FAILURE);
    }

    // Write teacher accounts
    fprintf(file1, "Teacher passwords\n");
    for (int i = 0; i < Vector_size(&teacher_username); i++) {
        fprintf(file1, "%s,%s\n", teacher_username.data[i], teacher_password.data[i]);
    }

    fclose(file1);




    // Write student accounts
    FILE *file2 = fopen(filename2, "w");
    if (file2 == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file2, "Student passwords\n");
    for (int i = 0; i < Vector_size(&student_username); i++) {
        fprintf(file2, "%s,%s\n", student_username.data[i], student_password.data[i]);
    }

    fclose(file2);





    // Write attendance data
    FILE *file3 = fopen(filename3, "w");
    if (file3 == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file3, "Student Date\n");
    for (int i = 0; i < Vector_size(&attendence_date); i++) {
        fprintf(file3, "%s,%s\n", attend_student.data[i], attendence_date.data[i]);
    }
    fclose(file3);



    // Write performance data
    FILE *file4 = fopen(filename4, "w");
    if (file4 == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file4, "Student Perfromance\n");
    for (int i = 0; i < Vector_size(&performance); i++) {
        fprintf(file4, "%s,%s\n", per_student.data[i], performance.data[i]);
    }

    fclose(file4);
}








void saveDataToDatabase(MYSQL *conn) {
    insertTeacherData(conn);
    insertStudentData(conn);
    // insertAttendanceData(conn);
    // insertPerformanceData(conn);
}




int main() {
    
     MYSQL *conn = db_connect();
    Init_vector(&teacher_username);
    Init_vector(&teacher_password);
    Init_vector(&student_username);
    Init_vector(&student_password);
    Init_vector(&attendence_date);
    Init_vector(&attend_student);
    Init_vector(&performance);
    Init_vector(&per_student);
    Init_map(&individual);

    int choice;
    char user[30], pass[20];

    do {
        printf("Enter the type of account you want to log in:\n");
        printf("1. Admin\n2. Teacher\n3. Student\n4. Exit\n");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf(RED "Enter username: " RESET);
                scanf("%s", user);
                printf("Enter password: ");
                scanf("%s", pass);
                if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
                    int option;
                    do {
                        printf("1. Change password\n");
                        printf("2. Create teacher account\n");
                        printf("3. Create student account\n");
                        printf("4. Delete teacher account\n");
                        printf("5. Delete student account\n");
                        printf("6. See teacher performance\n");
                        printf("7. See student performance\n");
                        printf("8. Display all teachers\n");
                        printf("9. Display all Student\n");
                        printf("10. Logout\n");
                        scanf("%d", &option);
                        switch (option) {
                            case 1:
                                // Change admin password
                                changepassword();
                                break;
                            case 2:
                                // Create teacher account
                                teacheraccount();
                                break;
                            case 3:
                                // Create student account
                                studentaccount();
                                break;
                            case 4:
                                // Delete teacher account
                                deleteteacheraccount();
                                break;
                            case 5:
                                // Delete student account
                                deletestudentaccount();
                                break;
                            case 6:
                                // See teacher performance
                                admin_seePerformance();
                                break;
                            case 7:
                                // See student performance
                                teacher_seePerformance();
                                break;
                            case 8:
                                teacher_list();
                                break;
                            case 9:
                                student_list();
                                break;
                        }
                    } while (option != 10);
                } else {
                    printf("Wrong username or password.\n");
                }
                break;

            case 2:
                printf("Enter username: ");
                scanf("%s", user);
                printf("Enter password: ");
                scanf("%s", pass);
                if(Vector_search(&teacher_username, user) && Vector_search(&teacher_password, pass)) {
                    int num;
                    do{
                        printf("Welcome to Acoount\n");
                        printf("1. See Attendance\n");
                        printf("2. Give Performance\n");
                        printf("3. See Performance\n");
                        printf("4. Log Out\n");

                        scanf("%d", &num);
                        switch(num) {
                            case 1:
                                teacher_seeAttendence();
                                break;
                            case 2:
                                teacher_givePerformance();
                                break;
                            case 3:
                                teacher_seePerformance();
                                break;
                        }

                    } while(num != 4);
                } else {
                    printf("You are not a valid user !\n");
                }

                break;

            case 3:
                // Student login
                printf("Enter username: ");
                scanf("%s", user);
                printf("Enter password: ");
                scanf("%s", pass);
                
                if(Vector_search(&student_username, user) && Vector_search(&student_password, pass)) {
                    int num;
                    do{
                        printf("Welcome to Acoount\n");
                        printf("1. Give Attendance\n");
                        printf("2. See your previous performance\n");
                        printf("3. Log Out\n");

                        scanf("%d", &num);

                        switch(num) {
                            case 1:
                                student_giveAttendence(user);
                                break;
                            case 2:
                                printf("Your previous performance is : %s\n", map_get(individual, user));
                                break;
                        }

                    } while(num != 3);
                } else {
                    printf("You are not a valid user\n");
                }
                break;

            case 4:
             saveDataToDatabase(conn);
                saveDataToCSV("Teacher_data.csv", "Studemt_data.csv", "Attendance.csv", "Performance.csv");
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");

        }

    } while(choice != 4);
db_disconnect(conn);

    return 0;
}