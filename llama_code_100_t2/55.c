// This function is used to check writeable register in aw9523..
static bool aw9523_writeable_reg(struct device *dev, unsigned int reg)
{
	ARG_UNUSED(dev);

	switch (reg) {
	case AW9523_REG_SYSTEM_CONTROL:
	case AW9523_REG_DEBOUNCE_CONTROL:
		return true;
	default:
		return false;
	}
}

// This function is used to check readable register in aw9523..
static bool aw9523_readable_reg(struct device *dev, unsigned int reg)
{
	ARG_UNUSED(dev);

	switch (reg) {
	case AW9523_REG_INTERRUPT_ENABLE:
	case AW9523_REG_INTERRUPT_STATUS:
		return true;
	default:
		return false;
	}
}

// Initialize and configure
	int aw9523_configure(struct device *dev, u8_t init_data[])
{
	struct aw9523_data *data = dev->driver_data;
	struct i2c_msg msg[2];
	u8_t rd_buf[2];
	u8_t wr_buf[1];

	if (init_data == NULL) {
		LOG_ERR("null pointer!");
		return -1;
	}
	// Read
	msg[0].buf = rd_buf;
	msg[0].len = 2;
	msg[0].flags = I2C_MSG_READ | I2C_MSG_STOP;

	rd_buf[0] = 0x00;
	rd_buf[1] = 0x00;
	msg[0].buf = rd_buf;

	// Write
	msg[1].buf = wr_buf;
	msg[1].len = 1;
	msg[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

	wr_buf[0] = AW9523_REG_SYST