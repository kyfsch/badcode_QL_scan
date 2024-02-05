// This function is used to check writeable register in aw9523..
static bool aw9523_writeable_reg(struct device *dev, unsigned int reg)
{
	struct aw9523_dev *drvdata = dev_get_drvdata(dev);

	if (!gpio_regmap_readable_reg(drvdata->regmap, reg))
		return false;

	return true;
}

static int aw9523_of_xlate(struct device *dev,
			   struct device_node *chn,
			   const unsigned int *con,
			   unsigned int con_count,
			   u32 *reg)
{
	const char *name = NULL;
	int val;

	if (IS_ERR(chn))
		chn = NULL;

	/* We're interested only in GPIOs */
	if (con[0] != GPIOLVL_OFFSET)
		return -ENOENT;

	if (!dev->of_node)
		name = dev_name(dev);
	else
		name = dev->of_node->name;

	val = gpio_of_parse_addr(chn, con);
	if (val < 0)
		return val;

	val += aw9523_get_reg(name);
	*reg = val;

	return 0;
	/*
	 * We must return the length of value, but kernel core will use
	 * it as number of descriptors of interrupt, we only care the
	 * number of consumed interrupt.
	 */
}

/*
 * Register our driver with 2 GPIOs per bank.
 */
static struct gpio_regmap_config aw9523_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,

	.reg_read = aw9523_reg_read,
	.reg_write = aw9523_reg_write,
	.reg_update = aw9523_reg_update,

	.max_register = GPIOLVL_OFFSET + 2,
	.cache_type = REGCAC