#include <stdio.h>

/* Global variable to hold RTC status */
int rtc_status;

/* Function prototype */
void close_file(FILE *file);

/* Function to close a file and set rtc_status */
void close_file(FILE *file) {
    if (file != NULL) {
        /* fclose returns 0 on success and EOF on error */
        rtc_status = (fclose(file) == 0) ? 1 : 0;
    } else {
        /* Handle the case where file pointer is NULL */
        rtc_status = 0;
    }
}
