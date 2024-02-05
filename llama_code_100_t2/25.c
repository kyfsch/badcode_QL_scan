// This function is used to probe the device, it takes a pointer to the platform device structure as an argument and returns a pointer to the rtl8366_smi structure.The smi structure contains all the information related to the device, including the device ID.
struct rtl8366_smi *rtl8366_smi_probe(struct platform_device *pdev)
{
	struct rtl8366_smi *smi;
	int irq;

	if (!pdev)
		return NULL;

	smi = devm_kzalloc(&pdev->dev, sizeof(struct rtl8366_smi), GFP_KERNEL);
	if (!smi)
		return ERR_PTR(-ENOMEM);

	smi->pdev = pdev;

	// Get the GPIO IRQ number
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return ERR_PTR(irq);
	smi->irq = irq;

	// Here, the function calls rtl8366_io_init to initialize the SMIO register, and set the SMIO_BASE/SMIO_RANGE/CHIPID register to the value passed by the argument.In this function, the I/O API is used to read and write registers in 32-bit. There is therefore no need to call the register-read and rts5208_register-write functions in this step.
	if (rtl8366_io_init(smi, RTL8366_IOPAD_3WIRE, 0x89000333) != 0)
		goto err_rtsm_probe;
	// Set chip_id to the value that just read from REG_CHIP_ID and save the value for later use.
	smi->chip_id = rtl8366_register_read(smi, RTL8366_REG_CHIP_ID);

	return smi;

err_rtsm_probe:
	devm_kfree(&pdev->dev, smi);
	return ERR_PTR(-ENODEV);
}

// This function is used to destroy the driver and the private structure.
// The driver is disabled, uninstalled, and the IRQ is cleared.
// Finally, the driver is freed.
// In this