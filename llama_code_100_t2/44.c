/// This function is used to assert and deassert the DMA_CONTROL_RESET dword in oxnas chipset, and then call following device function to program each phy for dma.</s> .
static inline void sata_oxnas_reset_dma(struct ata_port *ap, int assert)
{
	void __iomem *scc1 = oem_scc_base[ap->port_no];
	u32 scc1_sata;

	scc1_sata = readl(scc1 + ST_SATA0_CONTROL);

	if (assert)
		scc1_sata &= ~(ST_SATA0_CONTROL_DMA_EN);
	else
		scc1_sata |= ST_SATA0_CONTROL_DMA_EN;

	writel(scc1_sata, scc1 + ST_SATA0_CONTROL);
}
</s>