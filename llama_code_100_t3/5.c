// This function is used to construct the required 32bit address to send to Nand controller.
static void ar934x_nfc_get_addr(struct ar934x_nfc *nfc, int column, int page)
{

	unsigned int addr = 0x0;

	switch (nfc->nand_chip.options & NAND_BUSWIDTH_MASK) {

	case NAND_BUSWIDTH_16:
		addr = ((page << 11) & 0xFFE00) | (column & 0x7FF);
		break;

	case NAND_BUSWIDTH_8:
	default:
		addr = ((page << 10) & 0xFFC00) | (column & 0x3FF);
	}

	ar934x_nfc_write(addr, NFC_DATA_ADDRESS);
}

static void ar934x_nfc_send_command(struct ar934x_nfc *nfc, int cmd)
{
	ar934x_nfc_write(cmd, NFC_COMMAND);
	ar934x_nfc_write(NFC_CLOCK_READ, NFC_CLOCK); /* set start bit */
	ar934x_nfc_write(NFC_CLOCK_CLEAR, NFC_CLOCK); /* clear start bit */
	ar934x_nfc_write(cmd, NFC_COMMAND);
	ar934x_nfc_write(cmd, NFC_COMMAND);
	ar934x_nfc_write(cmd, NFC_COMMAND);
}

static int ar934x_nfc_read_data(struct mtd_info *mtd,
				u_char *buf, int len)
{
	struct ar934x_nfc *nfc = nand_get_controller_data(mtd);
	unsigned char *buffer = buf;
	unsigned int data;
	unsigned int clock;
	size_t remaining = len;
	unsigned int max_read_len;

	/*
	 * Some eMMC cards are not properly responding to reads
	 * so we will not retry these