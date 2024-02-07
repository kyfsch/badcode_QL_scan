#include <stdio.h>  // Required for FILE and fclose function

// Assume that rtc_status is a global variable or defined elsewhere in the program
// Possible values for rtc_status should be defined as constants or an enum
#define RTC_SUCCESS 0
#define RTC_FAILURE 1

int rtc_status; // Globally defined status variable

void close_file(FILE **file_ptr) {
    if (file_ptr != NULL && *file_ptr != NULL) {
        if (fclose(*file_ptr) == 0) {
            rtc_status = RTC_SUCCESS;
        } else {
            rtc_status = RTC_FAILURE;
        }
        *file_ptr = NULL;  // Set the pointer to NULL to avoid dangling pointer
    } else {
        rtc_status = RTC_FAILURE;
    }
}
