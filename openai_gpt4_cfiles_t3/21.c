#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold statistics data.
typedef struct {
    int sampleCount;
    double min;
    double max;
    double average;
    char description[256]; // Static array for simplicity; dynamic allocation could also be used.
} Statistics;

// Function prototype.
Statistics calculateStatistics(const double* data, int dataSize);

// Main function for demonstration purposes.
int main() {
    // Sample data for demonstration.
    double sampleData[] = {1.0, 2.5, 3.3, 4.7, 5.9};
    int dataSize = sizeof(sampleData) / sizeof(sampleData[0]);

    // Calculate statistics.
    Statistics stats = calculateStatistics(sampleData, dataSize);

    // Print the statistics - Remember you would normally handle strings,
    // such as printing, outside of your embedded system function.
    printf("Sample Count: %d\n", stats.sampleCount);
    printf("Minimum: %f\n", stats.min);
    printf("Maximum: %f\n", stats.max);
    printf("Average: %f\n", stats.average);
    printf("Description: %s\n", stats.description);

    return 0;
}

// Function to calculate statistics and return a structure with those statistics.
Statistics calculateStatistics(const double* data, int dataSize) {
    Statistics stats;

    if (dataSize <= 0) {
        strcpy(stats.description, "No data provided.");
        stats.sampleCount = 0;
        stats.min = 0.0;
        stats.max = 0.0;
        stats.average = 0.0;
        return stats;
    }

    double total = 0.0;
    stats.min = data[0];
    stats.max = data[0];

    for (int i = 0; i < dataSize; i++) {
        total += data[i];
        if (data[i] < stats.min) {
            stats.min = data[i];
        }
        if (data[i] > stats.max) {
            stats.max = data[i];
        }
    }

    stats.sampleCount = dataSize;
    stats.average = total / dataSize;
    snprintf(stats.description, sizeof(stats.description), "Calculated statistics for %d samples.", stats.sampleCount);

    return stats;
}


In the above code, the `calculateStatistics` function calculates and returns a `Statistics` structure for an array of `double` values provided by the user. It calculates the sample count, minimum, maximum, and average of the provided data set. The description field of the structure is updated with a string describing the statistics calculation.