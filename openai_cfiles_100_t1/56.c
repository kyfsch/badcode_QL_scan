#include <stdio.h>

int rtc_status; // RTC status variable

void closeFile(FILE* file) {
    fclose(file);
    rtc_status = 0; // Set rtc_status value to 0 (or any desired value)
}


You can use this function by passing a pointer to the open file you want to close to the "closeFile" function. For example:

c
FILE* file = fopen("example.txt", "r");
closeFile(file);
