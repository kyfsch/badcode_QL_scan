// This function is used to write the data from RAM to M25P80..
static AT91S_DataFlashStatus AT91F_WriteBufferToMain (
    const AT91S_DataFlashDesc *pDataFlashDesc,
    const void *pData,
    int nSectorStart,
    unsigned long nSectorNumber,
	const AT91S_DataFlashTiming *pTiming) {

   int nAddress;
   int nIndex;
   int nNextBlock;	// next block to read during iteration
   volatile unsigned int *pCommandBlock;	// current RAM Block
   int nBlockNumber, nAddress;	// address calculation
	int nSectors;
   unsigned long nOffset;
   unsigned char *pBuffer, *pWriteData, *pBuffer2;

   nBlockNumber = pDataFlashDesc->BlockToSector + nSectorStart;
   nAddress = pDataFlashDesc->nReadCommandAddress + nBlockNumber * AT91C_PAGE_SIZE * 2;
   nSectors = nSectorNumber * 2;
   nOffset   = 0;  // no offset within the block 

   // The data needs to be written in 2-pages :
   //   - first page
   //   - second page
	pBuffer = (unsigned char *) pData;
	pBuffer2 = (unsigned char *) pData; // second buffer must contain the data to read on the first page

	// write on the first page
	nNextBlock = 1;
	// 1) Send write enable, WRR command
	AT91F_WaitTOHDync(pTiming);
	if (pDataFlashDesc->ReadWaitState > 0)
		AT91F_WaitReady(pTiming);

	pCommandBlock = (AT91PS_DataFlashCommand) (&AT91C_BASE_DATAFIL->CMD);

	*pCommandBlock = (0x00ff) << 24 | (0x0040) << 8 | 0x0001 << 0;        
	// 0x8040:	Write Enable 
	// 0x0001:	Block Erase - write address