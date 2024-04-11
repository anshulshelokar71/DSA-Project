# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "Vector.h"


Vector teacher_username;
Vector teacher_password;
Vector student_username;
Vector student_password;
Vector attendence_date;
Vector attend_student;
Vector performance;
Vector per_student;




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
        createAccount();
}


void admin_deleteAccount() {

    printf("1. delete teacher account :\n");
    printf("2. delete student account :\n");
    int num;
    scanf("%d", &num);
    if(num==1)
        del_teacheraccount();
    else if(num==2)
        del_studentaccount();

}


void admin_seePerformance() {
    printf("1.individual performance \n");
    printf("2.collectively performance \n");

    int num;
    scanf("%d", &num);
    
    if(num==1) {
        printf("Enter student name : ");
        char s[30];
        scanf("%s", s);
        printf("Performance is : ");
        // printf("%s", ) print performance from map

    } else if(num==2) {
        printf("Sudent -> Performance\n");
        //print performances from for loop
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
        // add individual to map...remaining
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
    // for(int i = 0; i < Vector_size(&attendence_date); i++) {
    //     printf("%s  ", attend_student->data[i]);
    //     printf("%s\n", attendence_date->data[i]);
    // }
}


void teacher_seePerformance() {
    printf("1.individual performance \n");
    printf("2.collectively performance \n");
    int num;
    scanf("%d", &num);
    
    if(num==1) {
        printf("Enter student name : ");
        char s[30];
        scanf("%s", s);
        printf("Performance is : ");
        // printf("%s", ) print performance from map

    } else if(num==2) {
        printf("Sudent -> Performance\n");
        //print performances from for loop
    }
}










void student_giveAttendence(char* s1) {
    printf("Enter date and month : \n");
    char s[50];
    scanf("%s", s);
    Vector_push_back(&attendence_date, s);
    Vector_push_back(&attend_student, s1); 
}









char username[20], password[20];
void changepassword() {

    printf("Enter username : ");
    scanf("%s", &username);
    printf("Enter password : ");
    scanf("%s", &password);
    
}


void teacheraccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", &n);
    printf("Enter password : ");
    scanf("%s", &pass);
    Vector_push_back(&teacher_username, n);
    Vector_push_back(&teacher_password, pass);
}


void deleteteacheraccount() {

}


void teacher_list() {
    for(int i = 0; i < Vector_size(&teacher_username); i++) {
        printf("%d.  %s    %s\n", i+1, teacher_username.data[i], teacher_password.data[i]);
    }
} 



void studentaccount() {
    char n[20], pass[20];
    printf("Enter name : ");
    scanf("%s", &n);
    printf("Enter password : ");
    scanf("%s", &pass);
    Vector_push_back(&student_username, n);
    Vector_push_back(&student_password, pass);
}


void deletestudentaccount() {

}


void student_list() {
    for(int i = 0; i < Vector_size(&student_username); i++) {
        printf("%d.  %s    %s\n", i+1, student_username.data[i], student_password.data[i]);
    }
} 












int main() {
    strcpy(username, "Tejas");
    strcpy(password, "IqUnix");

    Init_vector(&teacher_username);
    Init_vector(&teacher_password);
    Init_vector(&student_username);
    Init_vector(&student_password);
    Init_vector(&attendence_date);
    Init_vector(&attend_student);
    Init_vector(&performance);
    Init_vector(&per_student);

    int choice;
    char user[30], pass[20];

    do {
        printf("Enter the type of account you want to log in:\n");
        printf("1. Admin\n2. Teacher\n3. Student\n4. Exit\n");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf("Enter username: ");
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
                        printf("8. Logout\n");
                        scanf("%d", &option);
                        switch (option) {
                            case 1:
                                // Change admin password
                                changepassword();
                                break;
                            case 2:
                                // Create teacher account
                                teacheraccount('t');
                                break;
                            case 3:
                                // Create student account
                                studentaccount('s');
                                break;
                            case 4:
                                // Delete teacher account
                                deleteteacheraccount('t');
                                break;
                            case 5:
                                // Delete student account
                                deletestudentaccount('s');
                                break;
                            case 6:
                                // See teacher performance
                                admin_seePerformance('t');
                                break;
                            case 7:
                                // See student performance
                                teacher_seePerformance('s');
                                break;
                        }
                    } while (option != 8);
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
                        
                    } while(num != 4);
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
                        
                    } while(num != 4);
                }
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");

        }

    } while(choice<4 && choice>0);


    return 0;
}