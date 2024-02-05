// This function is used to construct the required 32bit address to send to Nand controller.
static void ar934x_nfc_get_addr(struct ar934x_nfc *nfc, int column, int page, int block)
{
	uint32_t addr = 0;

	debug("NANDFC: ar934x_nfc_get_addr: column %d, page %d, block %d\n",
	      column, page, block);

	addr |= page		<< AR934X_NANDFC_CMD2_CMD2_PAGE_COL_SHIFT;
	addr |= column		<< AR934X_NANDFC_CMD2_CMD2_COL_SHIFT;
	addr |= block		<< AR934X_NANDFC_CMD2_CMD2_BLOCK_SHIFT;
	addr |= NANDFC_READ_MODE	<< AR934X_NANDFC_CMD2_CMD2_OP_MODE_SHIFT;
	addr |= 1		<< AR934X_NANDFC_CMD2_CMD2_BUS_WIDTH_SHIFT;

	debug("Setting address: %#x\n", addr);

	nfc->addr = addr;
	writel(addr, nfc->regs + AR934X_NANDFC_CMD2);
}

/*
 * A method to read data from NAND.
 * @param  buf: A pointer to a data buffer.
 * @param  page: The page to read from.
 * @param  column: The column to read from.
 * @param  oob: A pointer to a "OOB" buffer (if set to non NULL OOB data will be
 *  		read)
 * @param  oob_len: Length of the "OOB" buffer or NULL.
 * @param  read_empty_ecc: If we should read empty spare block data (if set to
 *  		1).
 * @return 0 on success.
 */
static int ar934x_nfc_rd(struct ar934x_nfc *nfc, void *buf, int page, int column, uint