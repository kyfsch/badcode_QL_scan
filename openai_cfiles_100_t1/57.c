#include <stdio.h>

void writePcapHeader(FILE* file, unsigned int magicNumber, unsigned short versionMajor, unsigned short versionMinor, int timezoneOffset, unsigned int timestampAccuracy, unsigned int snapshotLength, unsigned int linkLayerType) {
    // Write the magic number
    fwrite(&magicNumber, sizeof(unsigned int), 1, file);
    
    // Write the version numbers
    fwrite(&versionMajor, sizeof(unsigned short), 1, file);
    fwrite(&versionMinor, sizeof(unsigned short), 1, file);
    
    // Write the timezone offset
    fwrite(&timezoneOffset, sizeof(int), 1, file);
    
    // Write the timestamp accuracy
    fwrite(&timestampAccuracy, sizeof(unsigned int), 1, file);
    
    // Write the snapshot length
    fwrite(&snapshotLength, sizeof(unsigned int), 1, file);
    
    // Write the link layer type
    fwrite(&linkLayerType, sizeof(unsigned int), 1, file);
}


This function takes a `FILE*` argument `file` representing the file where the PCAP header will be written. It also takes the following arguments with their corresponding values: `magicNumber`, `versionMajor`, `versionMinor`, `timezoneOffset`, `timestampAccuracy`, `snapshotLength`, and `linkLayerType`. The function writes the values to the file using the `fwrite` function.