int write_dataflash(unsigned long addr_dest, unsigned int addr_src,
                    unsigned int size)
{
	unsigned int AddrToWrite = addr_dest;
	AT91PS_DataFlash pFlash = &DataFlashInst;

	pFlash = AT91F_DataflashSelect(pFlash, &AddrToWrite);
	if (AddrToWrite == -1)
		return -1;

	return AT91F_DataFlashWrite(pFlash, (unsigned char *) addr_src, AddrToWrite, size);
}
