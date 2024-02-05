/// This function is used to probe that the device is indeed the firebox t10..
machine_arch_initcall(firebox_t10, mpc85xx_common_publish_devices);

// Initialize the firebox t10
machine_arch_initcall(firebox_t10, t10_pci_init);

/*
 * Called very early, device-tree isn't unflattened
 */
static int __init firebox_t10_probe_nommu(void)
{
	return fsl_is_t10();
}

machine_arch_initcall(firebox_t10, t10_setup);

/*
 * Called after device-tree is fleshed out
 */
static int __init firebox_t10_probe(void)
{
	return of_machine_is_compatible("firebox,t10");
}

define_machine(firebox_t10) {
	.name			= "Firebox FSL-T10 Board",
	.probe			= firebox_t10_probe,
	.setup_arch		= firebox_t10_setup_arch,
	.init_irq		= cpm2_init_irq,
	.show_cpuinfo		= tqm8xx_show_cpuinfo,
	.init_early		= tqm8xx_init_early,
	</s>