// This function is used to send data to the cpld..
static int rb4xx_cpld_cmd(struct rb4xx_cpld *cpld, const void *tx_buf,
			   const void *tx_buf_end, unsigned int tx_buf_len)
{
	int rval;
	struct i2c_msg msg;

	/* The CPLD is always at address 0x48 */
	msg.addr = 0x48;
	msg.flags = I2C_M_RD | I2C_M_STOP;
	msg.buf = cpld->buf;
	msg.len = 1;

	/* Loop until we have completed the read */
	do {
		if (tx_buf && tx_buf_len) {
			msg.addr = 0x49;
			msg.flags = I2C_M_STOP;
			if (tx_buf_len > sizeof(cpld->buf))
				msg.len = sizeof(cpld->buf);
			else
				msg.len = tx_buf_len;
			memcpy((void *) msg.buf, tx_buf, msg.len);
			tx_buf_len -= msg.len;
		}
		rval = i2c_transfer(cpld_adap, &msg, 1);
	} while (rval == 0);

	if (rval < 0)
		dev_err(cpld->dev, "Failed writing data to CPLD\n");

	return rval ? rval : 1;
}

/*
 * Write a value to a CPLD register
 */
static int rb4xx_cpld_write(struct rb4xx_cpld *cpld, enum cpld_reg addr,
			    unsigned char val)
{
	struct i2c_adapter *adap = cpld->adap;
	unsigned int timeout = 4;
	int rval = 0;
	int i;

	for (i = 0; i < I2C_RETRIES; i++) {
		rval = i2c_smbus_write_byte_data(ad