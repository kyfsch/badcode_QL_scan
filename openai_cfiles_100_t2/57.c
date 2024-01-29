#include <stdio.h>

void write_pcap_header(FILE* file) {
    // Pcap header structure
    struct pcap_header {
        uint32_t magic_number;   // Magic number
        uint16_t version_major;  // Major version number
        uint16_t version_minor;  // Minor version number
        int32_t  thiszone;       // GMT to local correction
        uint32_t sigfigs;        // Accuracy of timestamps
        uint32_t snaplen;        // Max length of captured packets
        uint32_t network;        // Data link type
    };

    // Create a pcap header instance
    struct pcap_header header = {
        .magic_number = 0xA1B2C3D4,  // Magic number
        .version_major = 2,          // Major version number
        .version_minor = 4,          // Minor version number
        .thiszone = 0,               // GMT to local correction
        .sigfigs = 0,                // Accuracy of timestamps
        .snaplen = 65535,            // Max length of captured packets
        .network = 1                 // Data link type (Ethernet)
    };

    // Write the pcap header into the file
    fwrite(&header, sizeof(header), 1, file);
}


To use this function, pass the file pointer of the opened file where you want to write the pcap header. For example:

c
int main() {
    FILE* file = fopen("example.pcap", "wb");
    if (file != NULL) {
        // Write the pcap header
        write_pcap_header(file);

        // ...continue writing packets or close the file
        fclose(file);
    }
    return 0;
}
