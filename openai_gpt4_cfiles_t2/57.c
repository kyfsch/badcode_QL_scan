#include <stdio.h>
#include <stdint.h>

/* PCAP Global Header structure */
typedef struct pcap_hdr_s {
    uint32_t magic_number;   /* magic number */
    uint16_t version_major;  /* major version number */
    uint16_t version_minor;  /* minor version number */
    int32_t  thiszone;       /* GMT to local correction */
    uint32_t sigfigs;        /* accuracy of timestamps */
    uint32_t snaplen;        /* max length of captured packets, in octets */
    uint32_t network;        /* data link type */
} pcap_hdr_t;

/* Function to write the PCAP Global Header to a file */
int write_pcap_header(FILE *file) {
    if (!file) {
        return -1;
    }

    /* Standard PCAP Global Header values */
    pcap_hdr_t pcap_header;
    pcap_header.magic_number = 0xa1b2c3d4;
    pcap_header.version_major = 2; // usually 2
    pcap_header.version_minor = 4; // usually 4
    pcap_header.thiszone = 0; // GMT to local correction
    pcap_header.sigfigs = 0; // accuracy of timestamps
    pcap_header.snaplen = 65535; // max length of captured packets
    pcap_header.network = 1; // link-layer header type, Ethernet for example

    size_t written = fwrite(&pcap_header, sizeof(pcap_hdr_t), 1, file);
    if (written != 1) {
        return -2; // Error occurred while writing to file
    }

    return 0; // Successfully wrote the header
}

/* Example usage */
/*
int main() {
    FILE *pcap_file = fopen("example.pcap", "wb");
    if (pcap_file == NULL) {
        perror("Error opening file");
        return -1;
    }

    if (write_pcap_header(pcap_file) != 0) {
        perror("Error writing PCAP header");
        fclose(pcap_file);
        return -1;
    }

    // Writing packets would come here...

    fclose(pcap_file);
    return 0;
}
*/


Uncomment the main function and other associated code if you want to create a test program to write out a PCAP file with just a header. This function `write_pcap_header` assumes that you are handling file opening and error checking externally. It takes a `FILE` pointer to an already open file in binary write mode and writes the hard-coded PCAP header to it. Then the function returns an integer indicating success or failure of the operation.