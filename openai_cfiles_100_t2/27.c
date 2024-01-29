#include <stdio.h>
#include <stdbool.h>

void updateBSSConfig(FILE *file, int index, bool onlyFiles) {
    // Move file pointer to the desired index
    fseek(file, (index - 1) * sizeof(BSSConfig), SEEK_SET);

    // Read the existing BSSConfig from the file
    BSSConfig currentConfig;
    fread(&currentConfig, sizeof(BSSConfig), 1, file);

    // Update the BSSConfig
    currentConfig.onlyFiles = onlyFiles;

    // Move file pointer back to the desired index
    fseek(file, (index - 1) * sizeof(BSSConfig), SEEK_SET);

    // Write the updated BSSConfig back to the file
    fwrite(&currentConfig, sizeof(BSSConfig), 1, file);
}


In this function, `file` is a pointer to the file object where the BSS configuration is stored. `index` represents the index of the BSS configuration to be updated. `onlyFiles` is a Boolean value indicating whether only files or the full configuration should be updated.