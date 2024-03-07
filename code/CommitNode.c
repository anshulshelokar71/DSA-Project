// This file will be containg code for the commits made 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char* gen_random(const int len) {

    static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
    
    char* temp_string = (char*)malloc((len + 1) * sizeof(char)); 
    if (temp_string == NULL) {
        perror("Memory not allocation");
        exit(EXIT_FAILURE);
    }

    srand((unsigned int)(time(NULL) * getpid())); 

    for (int i = 0; i < len; ++i) {
        temp_string[i] = alphanum[rand() % (sizeof(alphanum) - 1)]; 
    }

    temp_string[len] = '\0';
    return temp_string;
}


char* get_time() {
    time_t rawtime;
    struct tm *timeinfo;
    char *dateTime = (char*)malloc(20 * sizeof(char));

    time(&rawtime);
    timeinfo = localtime(&rawtime); 

    sprintf(dateTime, "%d/%d/%d %d:%d\n",
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min);

    printf("%s ", dateTime);
    return dateTime;
}