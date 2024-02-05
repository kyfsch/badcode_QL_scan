/// This function is used to write the NAND command register and control lines. This function uses pointers instead of direct access for GPIO control..
static void rb4xx_nand_cmd_ctrl(struct nand_chip *chip, int dat, unsigned int ctrl)
{
	struct rb4xx_nand_chip *chip_data = (struct rb4xx_nand_chip *)chip->priv;
	// Write command registers
	rb4xx_nand_reg_write(dat, ((volatile int *)(chip->IO_ADDR_W | CONFIG_PHYSADDR + 0x470)));
	// Write control register
	rb4xx_reg_write(ctrl, ((volatile int *)(CONFIG_PHYSADDR + 0x47C)));
}

// This function is used to read the NAND databus. This function uses pointers instead of direct access for GPIO control.
static uint8_t rb4xx_nand_read_byte(struct nand_chip *chip)
{
	uint8_t databus;
	struct rb4xx_nand_chip *chip_data = (struct rb4xx_nand_chip *)chip->priv;
	uint8_t *io_addr = (uint8_t *)(CONFIG_PHYSADDR + 0x110);

	// Set DQ high and CLE low
	rb4xx_nand_gpio_set(io_addr - IOPRIO + 0x448, 0x20);
	// Set DQ low and ALE low
	rb4xx_nand_gpio_set(io_addr, 0x10);
	// Read databus
	rb4xx_nand_gpio_dir_in(io_addr);
	// Wait 500ns (read latch setup time)
	udelay(1);
	// Get databus
	databus = rb4xx_nand_gpio_get(io_addr);
	// Set DQ high and CLE high
	rb4xx_nand_gpio_set(io_addr - IOPRIO +</s>