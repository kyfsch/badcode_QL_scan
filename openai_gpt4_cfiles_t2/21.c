#include <stdio.h>
#include <string.h>

// Define the maximum number of statistics strings and their maximum sizes
#define MAX_STATS 10
#define MAX_STAT_STR_LENGTH 100

// Define a structure to hold statistics data
typedef struct {
    char stats_strings[MAX_STATS][MAX_STAT_STR_LENGTH];
    int count;
} Statistics;

// Function to fill the statistics strings
void get_statistics_strings(Statistics *statistics) {
    if (statistics == NULL) {
        return; // Safety check
    }

    // Example usage: fill in the statistics strings and count
    statistics->count = 3; // Assume we have 3 statistics strings for example
    strncpy(statistics->stats_strings[0], "First statistic: 123", MAX_STAT_STR_LENGTH);
    strncpy(statistics->stats_strings[1], "Second statistic: 456", MAX_STAT_STR_LENGTH);
    strncpy(statistics->stats_strings[2], "Third statistic: 789", MAX_STAT_STR_LENGTH);
}

// Main function for demonstration purposes
int main() {
    // Create an instance of Statistics to hold our data
    Statistics stats;
    get_statistics_strings(&stats);

    // Print out the statistics strings
    for (int i = 0; i < stats.count; ++i) {
        printf("%s\n", stats.stats_strings[i]);
    }