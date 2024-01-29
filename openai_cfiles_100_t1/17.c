#include <stdio.h>

// Structure to hold NAPI statistics
typedef struct {
    int packetsReceived;
    int packetsDropped;
    int bytesReceived;
    int bytesDropped;
} NapiStats;

// Function to report NAPI stats in file format
void reportNapiStats(NapiStats stats, const char* filename) {
    // Open the file in write mode
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file for writing.");
        return;
    }

    // Write the NAPI stats to the file
    fprintf(file, "Packets Received: %d\n", stats.packetsReceived);
    fprintf(file, "Packets Dropped: %d\n", stats.packetsDropped);
    fprintf(file, "Bytes Received: %d\n", stats.bytesReceived);
    fprintf(file, "Bytes Dropped: %d\n", stats.bytesDropped);

    // Close the file
    fclose(file);
}
