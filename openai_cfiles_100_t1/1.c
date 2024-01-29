#include <string.h>

int matchMappingName(const char* mappingName, const char* platformMappingName)
{
    if (strcmp(mappingName, platformMappingName) == 0)
    {
        return 1; // Names match
    }

    return 0; // Names don't match
}


This function takes two arguments: `mappingName` and `platformMappingName`, which are both strings representing the names to be matched. It uses the `strcmp` function from the `string.h` library to compare the two names. If the names are the same, the function returns `1` to indicate a match. Otherwise, it returns `0` to indicate that the names don't match.

You can call this function with your mapping names and the platform's mapping names to check for a match. For example:

c
const char* mappingName = "Mapping 1";
const char* platformMappingName = "Mapping 2";

if (matchMappingName(mappingName, platformMappingName))
{
    // Names match
    // Perform your desired actions here
}
else
{
    // Names don't match
    // Handle the mismatch here
}
