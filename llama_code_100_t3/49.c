// This function is used to write the NAND command register and control lines. This function uses pointers instead of direct access for GPIO control..
static void rb4xx_nand_cmd_ctrl(struct nand_chip *chip, int dat, int cmd, int load)
{
#ifndef CONFIG_SANDBOX
	if (load == WRITE_CMD)
	{
		/* Set command */
		/* rb_gpio_write_bit(cmd, RB4XX_GPIO_MERGED_W_PORT, RB4XX_GPIO_MERGED_W_BIT); */
        rk_gpio_write_bit(cmd, RB4XX_GPIO_PORT2, 0);

		/* Set address and/or data */
		if (dat != -1)
		{
            rk_gpio_write_bit(dat, RB4XX_GPIO_PORT1, 0);
      //    rb_gpio_write_bit(dat, RB4XX_GPIO_MERGED_EH_PORT, RB4XX_GPIO_MERGED_W_BIT);
        }
	}
	else if (load == READ_PIO)
	{
        rb_gpio_write_bit(cmd, RB4XX_GPIO_MERGED_WE_PORT, RB4XX_GPIO_MERGED_WE_BIT);

	}
	else if (load == WRITE_PIO)
	{

        rb_gpio_write_bit(cmd, RB4XX_GPIO_MERGED_WE_PORT, RB4XX_GPIO_MERGED_WE_BIT);

	}
	else if (load == READ_STATUS)
	{
        rb_gpio_write_bit(cmd, RB4XX_GPIO_MERGED_B_PORT, RB4XX_GPIO_MERGED_B_BIT);

	}
#if 0
	else if (load == WRITE_STATUS)
	{

		/* Set command */
		/* rb_gpio_write_bit(cmd, RB4XX