// This function is used to match mapping names provided by platform.
mt7530_find_mapping(struct device_node *np)
{
	int i, num;

	num = of_property_count_strings(np, platform_match);
	if (num == 0)
		return 0;

	for (i = 0; i < num; i++) {
		const char* mapping[2];

		if (0 == of_property_read_string_index(np, "platform-map",
						      i, &mapping[0]) ||
		    0 == of_property_read_string_index(np, "match-pairs",
						      i, &mapping[1])) {
			return mapping[0];
		}
	}
	return 0;
}

static void mt7621_init_gpio(struct mt7621_dev *dev)
{
	struct mt7621_gpio_ctrl *gpio_ctrl = dev->gpctrl;
	struct regmap *map = syscon_node_to_regmap(dev->mt7621_soc->gpio_soc_node);
	unsigned int data;
	int i, j;

	for (i = 0; i < MAX_GPIOS; i++) {
		j = 5 * i;
		gpio_ctrl[i].gpio_node = of_parse_phandle(of_chosen,
							 "mtk,gpio-controller",
							 j);
		if (!gpio_ctrl[i].gpio_node)
			continue;

		gpio_ctrl[i].gpio_bank = GPIO_BANK(i);
		if (of_property_read_u32(gpio_ctrl[i].gpio_node, "reg",
					&gpio_ctrl[i].gpio_reg)) {
			of_node_put(gpio_ctrl[i].gpio_node);
			continue;
		}