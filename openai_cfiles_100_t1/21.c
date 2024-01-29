#include <stdio.h>

char* getStatisticsString() {
    // Calculate statistics
    int totalCount = 100;
    int successCount = 80;
    int failureCount = 20;
    float successRate = ((float)successCount / totalCount) * 100;

    // Create the statistics string
    char* statisticsString = (char*)malloc(100);  // Assume a maximum of 100 characters
    sprintf(statisticsString, "Total: %d, Success: %d, Failure: %d, Success Rate: %.2f%%\n",
            totalCount, successCount, failureCount, successRate);

    return statisticsString;
}


In this function, we calculate the statistics (total count, success count, failure count, success rate) and then create a dynamic memory allocation for a string to hold the result. We use `sprintf` to format the statistics values into the string. Finally, we return the dynamically allocated string to the caller.