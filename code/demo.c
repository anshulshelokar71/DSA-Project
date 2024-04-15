# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "STL/Vector.h"
# include "STL/Map_String.h"
#include <mysql/mysql.h>
////////////////////////////////////////////////// ADMIN LOGIN /////////////////////////////////////////////////////////////
char username[10] = "Tejas";
char password[10] = "Sanika";
/////////////////////////////////////////////////// MYSQL INIT ////////////////////////////////////////////////////////////
#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "DSA"
////////////////////////////////////////////// COLOR PALETTE //////////////////////////////////////////////////////////////
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET   "\x1B[0m"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// DEFINING VECTORS AND MAP ////////////////////////////////////////////////
Vector teacher_username;
Vector teacher_password;
Vector student_username;
Vector student_password;
Vector attendence_date;
Vector attend_student;
Vector performance;
Vector per_student;
Map *individual;


void changepassword() {

    printf("Enter username : ");
    scanf("%s", username);
    printf("Enter password : ");
    scanf("%s", password);
    
}

////////////////////////////////////////////////////////STUDENT SIDE//////////////////////////////////////////////////////

void studentaccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    Vector_push_back(&student_username, n);
    Vector_push_back(&student_password, pass);
}




void student_seeAttendence(char *s) {
    printf(CYAN"present date :\n");
    for(int i = 0; i < Vector_size(&attendence_date); i++) {
        printf("%s  ", attend_student.data[i]);
        if(strcmp(attend_student.data[i], s) == 0)
            printf("%s\n", attendence_date.data[i]);
    }
    printf(""RESET);
}


///////////////////////////////////////////////////TEACHER SIDE////////////////////////////////////////////////////////////


void teacheraccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    Vector_push_back(&teacher_username, n);
    Vector_push_back(&teacher_password, pass);
}



void teacher_givePerformance() {
    printf("Enter student name : ");
    char s[30];
    scanf("%s", s);

    if(Vector_search(&student_username, s) != -1) {
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
    printf(CYAN"Student Name -> ");
    printf("present date :\n");
    for(int i = 0; i < Vector_size(&attendence_date); i++) {
        printf("%s  ", attend_student.data[i]);
        printf("%s\n", attendence_date.data[i]);
    }
    printf(""RESET);
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
        printf(CYAN"Performance is : ");
        printf("%s\n"RESET, map_get(individual, s));

    } else if(num==2) {
        printf(CYAN"Sudent -> Performance\n"RESET);
        for(int i = 0; i < Vector_size(&performance); i++) {
            printf(CYAN"%s %s\n"RESET, per_student.data[i], performance.data[i]);
        }
    }
}



void teacher_markAttendance() {
    char date[10];
    printf(CYAN"Enter Date : "RESET);
    scanf("%s", date);
    Vector_push_back(&attendence_date, date);
    int f = 1;
    while(f){
        printf(CYAN"Enter student name : "RESET);
        char s[30];
        scanf("%s", s);
        Vector_push_back(&attend_student, s);
        printf("press 1 to exit and 0 to continue\n");
        scanf("%d", &f);
    }
}



//////////////////////////////////////////////// ADMIN SIDE///////////////////////////////////////////////////////////////


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
        if(map_find(individual, s))
            printf("%s\n", map_get(individual, s));
        else 
            printf(RED "Performance not updated yet!!!\n" RESET);

    } else if(num==2) {
        printf("Sudent -> Performance\n");
        for(int i = 0; i < Vector_size(&performance); i++) {
            printf("%s %s\n", per_student.data[i], performance.data[i]);
        }
    }
}



void deleteteacheraccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    if(Vector_search(&teacher_username, n) != 1 && Vector_search(&teacher_username, n) == Vector_search(&teacher_password, pass)) {
        Vector_erase_value(&teacher_username, n);
        Vector_erase_value(&teacher_password, pass);
    }
}



void deletestudentaccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", n);
    printf("Enter password : ");
    scanf("%s", pass);
    if(Vector_search(&student_username, n) != -1 && Vector_search(&student_password, pass) == Vector_search(&student_username, n)) {
        Vector_erase_value(&student_username, n);
        Vector_erase_value(&student_password, pass);
    }
}



void teacher_list() {
    for(int i = 0; i < Vector_size(&teacher_username); i++) {
        printf(CYAN"%d.  %s    %s\n"RESET, i+1, teacher_username.data[i], teacher_password.data[i]);
    }
} 



void student_list() {
    for(int i = 0; i < Vector_size(&student_username); i++) {
        printf(CYAN"%d.  %s    %s\n"RESET, i+1, student_username.data[i], student_password.data[i]);
    }
} 




////////////////////////////////////////////////MYSQL SERVER FUNCTIONS/////////////////////////////////////////////////////

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

void insertAttendanceData(MYSQL *conn) {
    for (int i = 0; i < Vector_size(&attendence_date); i++) {
        char *student = attend_student.data[i];
        char *date = attendence_date.data[i];

        char query[100];
        sprintf(query, "INSERT INTO attendance (student, date) VALUES ('%s', '%s')", student, date);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }
    }
}

void insertPerformanceData(MYSQL *conn) {
    char *performance[100];
    for (int i = 0; i < Vector_size(&performance); i++) {
        char *student = per_student.data[i];
        performance[i] = Vector_get(&performance, i);

        char query[100];
        sprintf(query, "INSERT INTO performance (student, performance) VALUES ('%s', '%s')", student, performance);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }
    }
}



void saveDataToDatabase(MYSQL *conn) {
    insertTeacherData(conn);
    insertStudentData(conn);
    // insertAttendanceData(conn);
    // insertPerformanceData(conn);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////CSV FILES GENERATOR//////////////////////////////////////////////////



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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void UserGuideline()
{
    printf(GREEN "\n\t\t\t\t\t\t\t **** How it Works? ****\n\n" RESET);
    printf(MAGENTA "For Admin \n" RESET);
    printf(" -> You will only able to store the Student's Name, MIS.\n");
    printf(" -> Student Name can be maximum 20 characters long.\n");
    printf(" -> Student MIS is unique for every students.\n");
    printf(" -> You can see Performance and Attendance of each Student\n");
    printf(" -> You can create Teacher\'s account.\n");
    printf(" -> You can delete the created account\n");
    printf(MAGENTA "For Teachers \n" RESET);
    printf(" -> You can mark as well as see the attendance of Students\n");
    printf(" -> You can also give the performance record of Students\n");
    printf(MAGENTA "For Students \n" RESET);
    printf(" -> You can see your attendance\n");
    printf(" -> You caqn see your previous performance record \n");
}


/////////////////////////////////////////////////////////////MAIN FUNCTION/////////////////////////////////////////////////


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

    printf("\n\n\n\n=================================================");
    printf(YELLOW "WELCOME TO STUDENT MANAGEMENT SYSTEM" RESET);
    printf("=======================================================\n\n");

    UserGuideline();

    do {
        printf(MAGENTA"\n\n\n\n\nEnter the type of account you want to log in:\n"RESET);
        printf(CYAN"1. Admin\n2. Teacher\n3. Student \n4. Import data as CSV\n5. Exit\n"RESET);
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf(BLUE "Enter username: " RESET);
                scanf("%s", user);
                printf(BLUE"Enter password: "RESET);
                scanf("%s", pass);
                if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
                    printf(GREEN"\n\n\n\n\nWelcome Admin\n" RESET);
                    int option;
                    do {
                        printf(YELLOW"----------------------------------------\n");
                        printf("1. Change password\n");
                        printf("2. Create teacher account\n");
                        printf("3. Create student account\n");
                        printf("4. Delete teacher account\n");
                        printf("5. Delete student account\n");
                        printf("6. See student performance\n");
                        printf("7. Display all teachers\n");
                        printf("8. Display all Student\n");
                        printf("9. Logout\n");
                        printf("----------------------------------------\n"RESET);
                        scanf("%d", &option);
                        switch (option) {
                            case 1:
                                // Change admin password
                                changepassword();
                                break;
                            case 2:
                                // Create teacher account
                                teacheraccount();
                                printf(GREEN"Account created succesfully !\n"RESET);
                                break;
                            case 3:
                                // Create student account
                                studentaccount();
                                printf(GREEN"Account created succesfully !\n"RESET);
                                break;
                            case 4:
                                // Delete teacher account
                                deleteteacheraccount();
                                printf(GREEN"Account deleted succesfully !\n"RESET);
                                break;
                            case 5:
                                // Delete student account
                                deletestudentaccount();
                                printf(GREEN"Account deleted succesfully !\n"RESET);
                                break;
                            case 6:
                                // See teacher performance
                                admin_seePerformance();
                                break;
                            case 7:
                                teacher_list();
                                break;
                            case 8:
                                student_list();
                                break;
                        }
                    } while (option != 9);
                } else {
                    printf(RED"Wrong username or password.\n"RESET);
                }
                break;

            case 2:
                printf(BLUE"Enter username: "RESET);
                scanf("%s", user);
                printf(BLUE"Enter password: "RESET);
                scanf("%s", pass);
                if(Vector_search(&teacher_username, user) != -1 && Vector_search(&teacher_password, pass) == Vector_search(&teacher_username, user)) {
                    int num;
                        printf(GREEN"\n\n\nWelcome to Acoount\n"RESET);
                    do{
                        printf(YELLOW"----------------------------------------\n"RESET);
                        printf(YELLOW"1. See Attendance\n");
                        printf("2. Mark Attendance\n");
                        printf("3. Give Performance\n");
                        printf("4. See Performance\n");
                        printf("5. Log Out\n"RESET);

                        scanf("%d", &num);
                        switch(num) {
                            case 1:
                                teacher_seeAttendence();
                                break;
                            case 2:
                                teacher_markAttendance();
                                break;
                            case 3:
                                teacher_givePerformance();
                                break;
                            case 4:
                                teacher_seePerformance();
                                break;
                        }
                        printf(YELLOW"----------------------------------------\n\n\n"RESET);
                    } while(num != 5);
                } else {
                    printf(RED"You are not a valid user !\n"RESET);
                }

                break;

            case 3:
                // Student login
                printf(BLUE"Enter username: "RESET);
                scanf("%s", user);
                printf(BLUE"Enter password: "RESET);
                scanf("%s", pass);
                
                if(Vector_search(&student_username, user) != -1 && Vector_search(&student_password, pass) == Vector_search(&student_username, user)) {
                    int num;
                        printf(GREEN"\n\n\nWelcome to Acoount\n"RESET);
                    do{
                        printf(YELLOW"----------------------------------------\n"RESET);
                        printf(YELLOW"1. See Attendance\n");
                        printf("2. See your previous performance\n");
                        printf("3. Log Out\n"RESET);

                        scanf("%d", &num);

                        switch(num) {
                            case 1:
                                student_seeAttendence(user);
                                break;
                            case 2:
                                printf(CYAN"Your previous performance is : %s\n"RESET, map_get(individual, user));
                                break;
                        }
                        printf(YELLOW"----------------------------------------\n\n\n\n"RESET);
                    } while(num != 3);
                } else {
                    printf(RED"You are not a valid user\n"RESET);
                }
                break;

            case 4:
                saveDataToDatabase(conn);
                saveDataToCSV("Teacher_data.csv", "Studemt_data.csv", "Attendance.csv", "Performance.csv");
                break;

            case 5:
                printf(MAGENTA"Exiting...\n"RESET);
                db_disconnect(conn);
                break;
            default:
                printf(RED"Invalid choice.\n"RESET);

        }

    } while(choice != 5);

    return 0;
}