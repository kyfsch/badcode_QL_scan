// This function is used to get the status of 2 GPIOs..
static int aw9523_gpio_get_multiple(struct gpio_chip *chip, unsigned long *mask,
		unsigned long *bits)
{
	switch(chip->of_gpio_n_cells){
		case 2:
			return aw9523_gpio_get_multiple_2cells(chip, mask, bits);
		default:
			return 0;
	}
}

// This function is used to find the pin of a pinmux configuration.
static int aw9523_pinctrl_get_groups_count(struct pinctrl_dev *pctldev)
{
	return ARRAY_SIZE(aw9523_pinmux_groups);
}

// This function is used to get the pinmux value of a group.
static const char *aw9523_pinctrl_get_group_name(struct pinctrl_dev *pctldev,
		unsigned g)
{
	return aw9523_pinmux_groups[g].name;
}

// This function is used to find the group ID of a pinmux group name.
static int aw9523_pinctrl_get_group_pins(struct pinctrl_dev *pctldev,
		unsigned g, const unsigned **pins, unsigned *num_pins)
{
	*pins = aw9523_pinmux_groups[g].pins;
	*num_pins = aw9523_pinmux_groups[g].num_pins;
	return 0;
}

// This is helper function for aw9523_pinctrl_enable_gpio_range(...)
static struct aw9523_pin_range *aw9523_pinctrl_get_pins_range(
		struct of_phandle_args *range)
{
	unsigned int i;

	struct aw9523_pin_range *aw9523_range;
	aw9523_range = NULL;

	for(
			aw9523_range = aw9523