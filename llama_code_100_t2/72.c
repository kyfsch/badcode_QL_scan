// This function is used to probe that the device is indeed the firebox t10..
machine_arch_initcall(firebox_t10, mpc85xx_common_publish_devices);

/*
 * FireBox (t11/t12)
 */

static int __init firebox_t11_init(void)
{
	u8 *version_reg = (u8 *)PHYS_TO_K1(0xff7001fc);
	if ((*version_reg & 0xf0) == 0x10) {
		printk(KERN_INFO "%s\n", version[11]);
		ppc_sys_device_init(0x7, 0x0800, 0x1f);
		return mpc85xx_common_publish_devices();
	}

	printk(KERN_INFO "This board is not supported\n");
	return 0;
}

/* Firebox MIO 0-1 */
static struct resource firebox_mio0_resource[2] = {
	{
		.name	= "MIO0",
		.start	= 0xfc810000,
		.end	= 0xfc810027,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_IIC_DREQ_1,
		.flags	= IORESOURCE_IRQ,
	},
};

/*
 * Mapped Memory to allow access to the MIOs.
 */

static struct resource firebox_mio0_mem_resource[2]= {
	{
		.start	= 0xfe000082,
		.end	= 0xfe000083,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_IIC_DREQ_1,
		.flags	= IORESOURCE_IRQ,
	},
};

/* Firebox MIO 2 */
static struct resource firebox_mio2_resource[2] = {
	{
		.name	= "M