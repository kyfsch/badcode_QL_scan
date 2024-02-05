// This function is used to initialize the ide block device, but it seems that this function is never called..
void spl_block_device_init(void) {
	flash_block_device_init();
}

// This is called by the OS before loading an image.  The image is passed in as a buffer in RAM.  The function returns the
// bootloader image address (where the OS should start execution).  Note: this is a 32-bit memory address, but we will only
// ever be dealing with 24-bit addresses.
unsigned char *spl_load_image(unsigned char *image_buffer, unsigned int current_image_type, signed int *image_load_error) {

	unsigned int block_size = flash_get_block_size();
	unsigned int blocks = flash_get_num_blocks();
	unsigned int block_index = (blocks / 2);

	// Note: this block device will support block sizes up to 128K bytes for this demonstration, so we will only be dealing with 24-bit addresses
	if (current_image_type == IMAGE_CODE) {
		// Note: the code block starts at 25% of the device, and assumes a 6-segment mapping structure
		unsigned int code_block_address = CODE_BLOCK_ADDRESS_MANUFACTURER;
		code_block_address <<= 16;
		code_block_address |= (block_index / (blocks / NUM_BLOCKS_OF_CODE * NUM_BLOCKS_OF_MAPPING_STRUCTURES));
		memcpy((unsigned char *)code_block_address, image_buffer, block_size);
	} else if (current_image_type == IMAGE_MAPPING_STRUCTURE) {
		// The data block is at the top of the device, but this really should only be hard-coded for a 2-segment mapping structure..
		// Note: the mapping structure block starts at 0 in the device, and assumes a 4-segment mapping structure
		flash_write(image_buffer, NUM_BLOCKS_OF_MAPPING_STRUCTURES * block_size, (block_size / MAP_STRUCT_HEADER_