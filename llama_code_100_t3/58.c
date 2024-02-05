/// This function is used to initialize the psb6970 PHY and register the required PHY driver..
int __init psb6970_init(void)
{
	/* Set up pci-e PHY */
	if ((g_PchConfig->PcieRp.PcieConfig.CommonConfig.PciConfig.GfxDevPmCapId != 0) &&
	    (g_PchConfig->PcieRp.PcieConfig.CommonConfig.PciConfig.GfxDevPmCapId ==
	     PCIE_GFXDEVPM_GEN3))
		g_phy_driver = gen3_phy;
	else
		g_phy_driver = gen2_phy;

	g_phy_driver->init(g_phy_driver);

	/* Set up PME# */
	init_pm();

	return 0;
}

/* psb6970_exit() - This function is used to cleanup the psb6970 PHY.
 */
void __exit psb6970_exit(void)
{
	g_phy_driver->exit(g_phy_driver);
}

module</s>