#include <stdbool.h>
#include <string.h>

// Function to check if two mapping names match
bool isMappingMatch(const char* platformMapping, const char* providedMapping) {
  // Check if the length of the strings are equal
  if (strlen(platformMapping) != strlen(providedMapping)) {
    return false;
  }
  
  // Iterate over the characters in the strings
  for (int i = 0; i < strlen(platformMapping); i++) {
    // Check if the characters at the current index match
    if (platformMapping[i] != providedMapping[i]) {
      return false;
    }
  }
  
  // Return true if all characters match
  return true;
}


You can use this function to compare mapping names provided by a platform with a given mapping name. The function takes two `const char*` parameters, `platformMapping` and `providedMapping`, representing the platform-provided mapping name and the given mapping name to compare, respectively. It returns `true` if the mapping names match and `false` otherwise.