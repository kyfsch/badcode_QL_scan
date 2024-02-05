// This function is used to register the gpio driver based on the GPIO configuration of the device. In addition, since GPIO chip sharing is allowed, there are more GPIO configuration options for the device to selectively set, rather than using the entire driver to register and initialize..
static int nct5104d_gpio_probe(struct platform_device *pdev)
{
	struct pca963x_platform_data *pdata =
		dev_get_platdata(&pdev->dev);
	struct pca963x_chip *chip;
	struct gpio_chip *gc;
	unsigned int irq;
	int ret;

	gc = devm_kzalloc(&pdev->dev, sizeof(struct gpio_chip), GFP_KERNEL);
	if (!gc)
		return -ENOMEM;

	chip = devm_kzalloc(&pdev->dev, sizeof(struct pca963x_chip),
				GFP_KERNEL);
	if (!chip)
		return -ENOMEM;
	chip->chip = *gc;
	chip->chip.label = dev_name(&pdev->dev);
	chip->chip.dev = &pdev->dev;
	gc->label = dev_name(&pdev->dev);
#if defined(CONFIG_OF_GPIO)
	if (pdev->dev.of_node) {
		if (of_property_read_bool(pdev->dev.of_node,
						"ngk,drive-current")) {
			chip->chip.direction_input	= pca963x_gpio_direction_output;
			chip->chip.direction_output	= pca963x_gpio_direction_input;
			chip->chip.desired_peripheral_bus	= pca963x_gpio_get_direction;
		}
	} else
#endif
	chip->regs =
		pdata ? (u8 __iomem *)(pdata->setup) : (u8 __iomem *)DEFAULT_NGK_SETUP;
	pca963x_config_get_gpio_invert(chip, &pdev->dev);

	chip->gpio_nums = (p