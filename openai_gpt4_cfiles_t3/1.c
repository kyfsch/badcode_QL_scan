#include <stdio.h>
#include <string.h>

#define MAX_MAPPINGS 128 // Maximum number of mappings; adjust as necessary
#define NAME_MAX_LENGTH 50 // Maximum length of each mapping name
#define NOT_FOUND -1 // Error code when mapping name is not found

typedef struct {
    char name[NAME_MAX_LENGTH];
    int id;
} Mapping;

int match_mapping_name(const char *name, const Mapping *mapping_list, int list_size) {
    for (int i = 0; i < list_size; ++i) {
        if (strcmp(mapping_list[i].name, name) == 0) {
            return mapping_list[i].id; // Return the matched ID
        }
    }
    return NOT_FOUND; // Return error code when not found
}

// Example usage
int main() {
    Mapping mapping_list[MAX_MAPPINGS] = {
        {"NAME_1", 1},
        {"NAME_2", 2},
        // ... Add more mappings as needed
    };

    int number_of_mappings = 2; // Assume we have 2 mappings for this example; set this to actual count

    const char *name_to_match = "NAME_1";
    int matched_id = match_mapping_name(name_to_match, mapping_list, number_of_mappings);

    if (matched_id != NOT_FOUND) {
        printf("Matched ID: %d\n", matched_id);
    } else {
        printf("Mapping not found for name: %s\n", name_to_match);
    }

    return 0;
}
