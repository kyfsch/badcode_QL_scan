/// This function is used to set the power down mode by calling.
static inline void reset_ppe(struct platform_device *pdev);

static struct nandflash_controller hynix_h3cg2n63d_32mm_config = {
	.name = "hynix_h3cg2n63d_32mm",
	.power_on = hynix_h3cg2n63d_32mm_power_on,
	.command = hynix_h3cg2n63d_32mm_command,
	.select_chip = hynix_h3cg2n63d_32mm_select_chip,
	.devices_supported = 1,
};

static int __init hynix_h3cg2n63d_32mm_init(void)
{
	int r = platform_driver_register(&hynix_h3cg2n63d_32mm_driver);

	if (r != 0)
		goto out_return;
	r = mtd_nand_driver_register(&hynix_h3cg2n63d_32mm_controller,
				     NULL);
	if (r != 0)
		goto out_platform_deregister;
	return 0;
 out_platform_deregister:
	platform_driver_unregister(&hynix_h3cg2n63d_32mm_driver);
 out_return:
	return r;
}

static void __exit hyn</s>