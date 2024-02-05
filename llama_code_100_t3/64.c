// This function is used to set the power down mode by calling.
static inline void reset_ppe(struct platform_device *pdev);

static int set_dio_out(void *dip, int val)
{
	struct ralink_gpio *pg = dip;
	uint32_t msk = 1 << pg->bit_num;

	//if (pg->name == NULL)
	//	dev_dbg(&pg->pdev->dev, "ralink->set_dio_out val=%d!\n", val);

	if (val)
		REG_WR8(pg->reg, msk);
	else
		REG_WR8(pg->reg, 0);

	gpio_set_value_cansleep(pg->gpio_num, val);

	return 0;
}

static int set_dio_in(void *dip)
{
	struct ralink_gpio *pg = dip;
	uint32_t msk = 1<< pg->bit_num;
	uint8_t val;

	val = REG_RD8(pg->reg);
	val &= msk;
	if (val) {
		//pg->state = HIGH;
		gpio_direction_input(pg->gpio_num);
	}
	else {
		//pg->state = LOW;
		gpio_direction_output(pg->gpio_num, 0);
	}

	return 0;
}

static int set_dio_mode(void *dip, int mode)
{
	struct ralink_gpio *pg = dip;

	GPIO_set_io(pg->reg, L1_IO_MUX);
	GPIO_set_pin_name(pg->bit_num, io_gpio);
	GPIO_set_io_state(L1_IO_MUX, io_gpio, mode);

	return 0;
}

static int get_dio_mode(void *dip, int *mode)
{
	struct ralink_gpio *pg = dip;
	uint32