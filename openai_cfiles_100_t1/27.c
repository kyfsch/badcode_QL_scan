#include <stdio.h>

void updateBSSConfig(FILE* file, int index, int isFullConfig) {
    // move file pointer to the desired BSS configuration index
    fseek(file, index * sizeof(BSSConfig), SEEK_SET);
    
    // read the current BSS configuration from file
    BSSConfig config;
    fread(&config, sizeof(BSSConfig), 1, file);
    
    // update the BSS configuration
    if (isFullConfig) {
        // modify the full configuration
        // ...
    } else {
        // modify only the files configuration
        // ...
    }
    
    // move file pointer back to the desired position
    fseek(file, index * sizeof(BSSConfig), SEEK_SET);
    
    // write the updated BSS configuration back to file
    fwrite(&config, sizeof(BSSConfig), 1, file);
    
    // flush the changes to disk
    fflush(file);
}


This function assumes that you have a `BSSConfig` struct defined, representing the BSS configuration. You will need to define the structure based on your specific needs.

The `file` parameter is a pointer to the file object that contains the BSS configurations. The `index` parameter is the index of the desired BSS configuration to update. The `isFullConfig` parameter is a Boolean value indicating whether only the files configuration or the full configuration should be modified.

The function first moves the file pointer to the desired BSS configuration index using `fseek()`. It then reads the current BSS configuration from the file using `fread()`.

After that, you can modify the BSS configuration based on the `isFullConfig` flag. If `isFullConfig` is true, you can modify the full configuration. Otherwise, you can modify only the files configuration.

Once the modification is done, the file pointer is moved back to the desired position using `fseek()` again. The updated BSS configuration is then written back to the file using `fwrite()`, and the changes are flushed to disk using `fflush()`.