// This function is used to write the data from RAM to M25P80..
static AT91S_DataFlashStatus AT91F_WriteBufferToMain (AT91PS_DataFlash pDev,
		AT91PS_DataFlashDataPtr pData,
		AT91S_DataFlashAddress Address,
		AT91S_DataFlashSize Size) {
	volatile u32 Reg ;
	AT91S_DataFlashStatus Status = ERROR;

	volatile u32 i = 0, j = 0, x;
	u32 SizeX, DataLen = 0;

	// Calculate x = size >>  8
	x = Size >> 8;

	// Write the data in x blocks of 256 bytes
	for (i = 0 ; i < x ; i++) {
		__dsrWaitReady (pDev);

		Reg = 0;

		// Write the address
		// Set the Block Address
		Reg |= AT91C_M25P_BLOCK_1;
		Reg |= ((Address & 0x00FF0000) >> 16);

		// Set the Page Address
		Reg |= AT91C_M25P_PAGE_PROGRAM;
		Reg |= ((Address & 0x0000FF00) >> 8);

		// Write the data in the buffer
		while (DataLen < 256) {
			// Write the data
			memcpy (&pDev->pDataFlashData[DataLen], &pData[DataLen],
				sizeof (u16));

			pDev->pDataFlashData[DataLen] = (u32) (*((u8 *) &pData[DataLen]));
			pDev->pDataFlashData[DataLen + 1] =
				    (u32) (*((u8 *) &pData[DataLen] + 1));

			// Update the DataLen
			DataLen += 2;
		}

		WriteData (pDev->pDataFlashData,