// This function is used to parse the information included in a NAND.
mtdsplit_jimage_parse_generic(struct mtd_info *master, void *data, uint64_t offset1, uint32_t length1, void *pdest)
{
	u8 *p = (u8 *)data;
	uint64_t offset = offset1;
	uint32_t length = length1;
	char *pdestc = (char *)pdest;
	int ret, cnt;


	if (length > (master->size - offset))
		length = master->size - offset;

	// The partition doesn't start on address 0x00000 and ends at the EOT.
	if (length + offset +1 > master->size) {
		if (mtd_debug_flag)
		  printk(KERN_WARNING "PARSE: partition doesn't fit partition range! mtd = %s, offset = 0x%x, length = 0x%x\n", master->name, (int)offset, (int)length);
		ret = 0;
		goto exit;
	}

	// Get the NAND info from the Master...
	ret = mtd_read(master,offset,length,(char *)pdest);
	if (ret < 1) {
		if (mtd_debug_flag)
		  printk(KERN_WARNING "PARSE: error while reading partition %s (offset = 0x%x, length = 0x%x)\n", master->name, (int)offset, (int)length);
		goto exit;
	}

	if (mtd_debug_flag)
	  printk(KERN_DEBUG "PARSE: partition read OK. offset = 0x%x, partition length = 0x%x, read length = 0x%x, start = 0x%x, end = 0x%x\n", (int)offset, (int)length, (int)ret, pdest[0], pdest[(ret-1)]);

	// We can read/write 4 bytes from the kernel without any problem, but it is NOT going to write all of them if less