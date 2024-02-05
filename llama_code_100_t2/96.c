// This function is used to register the gpio driver based on the GPIO configuration of the device. In addition, since GPIO chip sharing is allowed, there are more GPIO configuration options for the device to selectively set, rather than using the entire driver to register and initialize..
static int nct5104d_gpio_probe(struct platform_device *pdev)
{
	struct gpio_device *gdev;
	struct gpio_chip *chip;

	printk(KERN_EMERG "GPIO IRQ: nct5104d_gpio_probe, pdev->id_entry: %p\n", pdev->id_entry);

	// The driver register GPIOs with the GPIO controller using the basic and GPIO chip APIs.
	// The GPIO APIs use a basic and chip descriptor structure to pass data between the GPIO
	// and driver.
	// The Linux GPIO API is to set up a generic device with the GPIO chip and GPIO basic data structure.
	// So the generic device will be initialized first, next register the gpio chip descriptor.

	gdev = devm_gpiochip_add_data(&pdev->dev, pdata->gpio_desc, pdata); // The GPIO driver calls devm_gpiochip_add_data to create the generic device and initialize the GPIO basic data table.
	if (IS_ERR(gdev)) {
		dev_err(&pdev->dev, "Failed to add device\n");
		return PTR_ERR(gdev);
	}
	chip = gdev->chip; // Since the gdev parameter is the address of the generic device, you can get its chip descriptor through this pointer.

	// Register IRQ on the GPIO chips.
	int irq;
	struct irq_chip *ic;
	for (irq = 0; irq < chip->ngpio; ++irq) {
		ic = &pdata->irq[irq];
		gpiod_set_irq_type(gdev->desc[irq].gpiod_priv, pdata->irq[irq].type);

		irq_set_chip_data(gpio_to_irq(chip->base + irq), ic);
		irq_set_chip_and_handler(gpio_to_irq(ch