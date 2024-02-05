// This function is used to get the status of 2 GPIOs..
static int aw9523_gpio_get_multiple(struct gpio_chip *chip,
				     unsigned long gpios)
{
	unsigned long read_gpios = 0;

	if (gpios & (1 << 0))
		read_gpios |= aw9523_porta_get_value(chip) & 0xFF;
	if (gpios & (1 << 1))
		read_gpios |= aw9523_portb_get_value(chip) & 0xFF;
	if (gpios & (1 << 2))
		read_gpios |= aw9523_portc_get_value(chip) & 0xFF;

	return (int)read_gpios;
}

/*
 * This function is used to output to 2 GPIOs which are connected to the
 * same port number on the AW9523 (e.g GPIO0 and GPIO1 on port C).
 */
static void aw9523_gpio_set_multiple(struct gpio_chip *chip, unsigned long gpios,
				     int val)
{
	if (gpios & 1) {
		if (val & 0x1)
			aw9523_portc_set_value(chip, val & 0xFF);
		else
			aw9523_portc_clear_value(chip, val & 0xFF);
	}

	if (gpios & 2) {
		if (val & 0x2)
			aw9523_portc_set_value(chip, val & 0xFF);
		else
			aw9523_portc_clear_value(chip, val & 0xFF);
	}
}

static int aw9523_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct aw9523_gpio *g = to_aw9523_gpio(chip);