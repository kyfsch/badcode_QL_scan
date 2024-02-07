#include <stdio.h>
#include <stdlib.h>

/* Define a structure for NAPI statistics */
typedef struct {
    unsigned int packets; /* Number of packets */
    unsigned int drops;   /* Number of dropped packets */
    unsigned int errors;  /* Number of errors */
    // You can add more fields here based on the stats you need to report
} NapiStats;

/* Function to report NAPI stats to a file */
void report_napi_stats(const char *filename, const NapiStats *stats) {
    FILE *file = fopen(filename, "w"); // Open the file for writing
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the NAPI stats to the file
    fprintf(file, "Packets: %u\n", stats->packets);
    fprintf(file, "Drops: %u\n", stats->drops);
    fprintf(file, "Errors: %u\n", stats->errors);
    // Add more fprintf calls for additional stats fields if necessary

    fclose(file); // Close the file
}

/* Example usage */
int main() {
    NapiStats my_stats = {
        .packets = 1000,
        .drops = 10,
        .errors = 5
        // Initialize more fields if there are additional stats
    };

    report_napi_stats("napi_stats.txt", &my_stats);

    return 0;
}
