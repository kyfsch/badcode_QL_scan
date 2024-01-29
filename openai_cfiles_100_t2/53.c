#include <stdint.h>

typedef struct {
    uint32_t page_size;
    uint32_t block_size;
    uint32_t spare_size;
    uint32_t num_pages;
    uint32_t num_blocks;
    uint32_t num_planes;
} NAND_Info;

void parseNANDInfo(uint8_t* nand_data, NAND_Info* info) {
    info->page_size = (nand_data[0] << 8) | nand_data[1];
    info->block_size = (nand_data[2] << 8) | nand_data[3];
    info->spare_size = (nand_data[4] << 8) | nand_data[5];
    info->num_pages = (nand_data[6] << 24) | (nand_data[7] << 16) | (nand_data[8] << 8) | nand_data[9];
    info->num_blocks = (nand_data[10] << 24) | (nand_data[11] << 16) | (nand_data[12] << 8) | nand_data[13];
    info->num_planes = (nand_data[14] << 8) | nand_data[15];
}


This function takes an `nand_data` array, which contains the information extracted from a NAND, and a pointer to a `NAND_Info` structure. It then parses the information from the `nand_data` array and stores it in the `info` structure.