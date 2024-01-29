#include <stdio.h>

void report_napi_stats(const char *filename, int rx_packets, int tx_packets, int rx_bytes, int tx_bytes) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return;
    }

    fprintf(file, "NAPI STATS REPORT:\n");
    fprintf(file, "-----------------\n");
    fprintf(file, "Rx Packets: %d\n", rx_packets);
    fprintf(file, "Tx Packets: %d\n", tx_packets);
    fprintf(file, "Rx Bytes: %d\n", rx_bytes);
    fprintf(file, "Tx Bytes: %d\n", tx_bytes);

    fclose(file);
}
