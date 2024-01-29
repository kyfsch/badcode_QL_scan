#include <stdio.h>
#include <stdlib.h>

// Function to return statistics string
char* getStatistics(int value1, int value2, int value3) {
    // Create a buffer of size 100 to hold the statistics string
    char* statistics = (char*)malloc(100 * sizeof(char));
    
    // Format the statistics string
    snprintf(statistics, 100, "Statistics: value1 = %d, value2 = %d, value3 = %d", value1, value2, value3);
    
    // Return the statistics string
    return statistics;
}

int main() {
    // Example usage
    int a = 10, b = 20, c = 30;
    char* result = getStatistics(a, b, c);
    
    // Print the statistics string
    printf("%s\n", result);
    
    // Free the allocated memory
    free(result);
    
    return 0;
}


In this example, the `getStatistics` function takes three integer values as arguments (`value1`, `value2`, `value3`), and returns a dynamically allocated string holding the statistics.