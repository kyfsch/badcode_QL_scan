#include <stdio.h>
#include <stdint.h>

/* PCAP Global Header Format */
typedef struct pcap_hdr_s {
    uint32_t magic_number;   /* magic number */
    uint16_t version_major;  /* major version number */
    uint16_t version_minor;  /* minor version number */
    int32_t  thiszone;       /* GMT to local correction */
    uint32_t sigfigs;        /* accuracy of timestamps */
    uint32_t snaplen;        /* max length of captured packets, in octets */
    uint32_t network;        /* data link type */
} pcap_hdr_t;

/* Function to write PCAP Global Header to a file */
void write_pcap_global_header(FILE *output_file) {
    pcap_hdr_t pcap_header;

    /* Initialize PCAP Global Header with typical values */
    pcap_header.magic_number = 0xa1b2c3d4; /* Standard PCAP magic number */
    pcap_header.version_major = 2;         /* Current major version */
    pcap_header.version_minor = 4;         /* Current minor version */
    pcap_header.thiszone = 0;              /* GMT to local correction */
    pcap_header.sigfigs = 0;               /* Accuracy of timestamps */
    pcap_header.snaplen = 65535;           /* Max length of captured packets */
    pcap_header.network = 1;               /* Ethernet data link type */

    /* Write PCAP Global Header to the output file */
    size_t bytes_written = fwrite(&pcap_header, sizeof(pcap_hdr_t), 1, output_file);

    /* Check if the write operation was successful */
    if (bytes_written != 1) {
        fprintf(stderr, "Error writing PCAP Global Header to file\n");
    }
}

/* Example usage */
int main() {
    FILE *pcap_file = fopen("example.pcap", "wb");
    if (pcap_file == NULL) {
        perror("Error opening file");
        return 1;
    }

    write_pcap_global_header(pcap_file);

    /* Further code to process and write packets to file would go here... */

    fclose(pcap_file);
    return 0;
}
