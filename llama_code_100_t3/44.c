/// This function is used to assert and deassert the DMA_CONTROL_RESET dword in oxnas chipset, and then call following device function to program each phy for dma.</s>.
static inline void sata_oxnas_reset_dma(struct ata_port *ap, int assert)
{
	static const char *const msg[2] = {"Disabling", "Enabling"};
	struct ata_host *host = ap->host;

	sata_oxnas_printk("%s DMA\n", msg[assert]);
	oxnas_writel(oxnas, assert ? OXNAS_DMAC_DISABLE : OXNAS_DMAC_ENABLE,
		     OXNAS_DMAC_CONTROL);
	oxnas_writel(oxnas, host->dma_mask, OXNAS_DMAC_MASK);

	sata_oxnas_printk("Waiting for DMA to %s.\n",
			assert ? "enter reset state" : "exit reset state");
	while (!oxnas_readl(oxnas, OXNAS_DMAC_CONTROL) & OXNAS_DMAC_IDLE)
		cpu_rel();
}

.
static void sata_oxnas_intr(struct ata_port *ap)
{
	u32 r0 = oznas_readl(oxnas, OXNAS_P0_INTSTS);
	struct ata_device *dev1, *dev0;

	sata_oxnas_printk("%sing up interrupt.\n", r0 & OXNAS_P0_INTSTS_ENS ?
			  "Disabling" : "Enabling");
	if (r0 & OXNAS_P0_INTSTS_ENS) {
		oxnas_writel(oxnas, 0, OXNAS_P0_INTSTS);
		r0 = r0 & (OXNAS_PHY_INTMASK & ~(OXNAS_P0_INTSTS_INT |
						OXNAS_P0_INTSTS_ENS));
		oxnas_writel(oxnas, r0 | OXNAS_P0_INTSTS_ENS,
			     OXNAS