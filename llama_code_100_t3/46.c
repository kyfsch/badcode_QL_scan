// This function is used to send data to the cpld..
static int rb4xx_cpld_cmd(struct rb4xx_cpld *cpld, const void *tx_buf,
			   size_t tx_len)
{
	struct spi_transfer tfer;
	struct spi_message msg;
	u8 buf[4];

	rB4xx_CPLD_LOG("> %pK\n", tx_buf);

	buf[0] = (cpld->addr & 0x78) | (len & 0x07);

	memcpy(&buf[4 - tx_len], tx_buf, tx_len);

	spi_message_init(&msg);
	memset(&tfer, 0, sizeof(tfer));

	tfer.rx_buf	= NULL;
	tfer.tx_buf	= buf;
	tfer.len	= tx_len + 4;

	spi_message_add_tail(&tfer, &msg);

	return spi_sync(cpld->spi, &msg);
}

static int rb4xx_cpld_rw(struct rb4xx_cpld *cpld, unsigned char addr,
			 void *rx_buf, size_t len, const void *tx_buf)
{
	if (tx_buf)
		return rb4xx_cpld_cmd(cpld, tx_buf, len);

	return rb4xx_cpld_read(cpld, rx_buf, len, addr);
}

void rb4xx_cpld_leds(const char *on)
{
	u8 xdata[9];
	u8 led = 0x00;

	for (int i = 0; i < 8; i++) {
		if (on[i] == '1')
			led |= 1 << i;
	}

	xdata[0] = 0x04;
	xdata[1] = 8;

	xdata[2] = 8;
	xdata[3] = 0x04;

	xdata[4] = 1;
	xdata[5] = 0