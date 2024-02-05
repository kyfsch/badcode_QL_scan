// This function is used to send a sync escape command to a controller.
static inline void sata_oxnas_send_sync_escape(struct ata_port *ap)
{
	void __iomem *host_base = (void __iomem *)ap->host->base;
	void __iomem *sata_base = host_base + SATA_OFFSET;
	struct ata_link *link = ap->link;

	sata_scr_write_32(link, SCR_CONTROL, SCR_CONTROL_SE);
}
#endif /* CONFIG_SATA_OXNAS */

#if IS_ENABLED(CONFIG_SATA_OXNAS) || IS_ENABLED(CONFIG_FSL_SATA_V2)
extern const iu32 scu_gpios5[];
extern const iu32 scu_gpios6[];
extern const iu32 scu_gpios7[];
extern const iu32 scu_gpios8[];
extern const iu32 scu_gpios9[];
extern struct irq_domain *scu_pmux_domain;

/*
 * This function is used to send a SATA_RESET to FSL controller.
 */
static int fsl_sata_scr_write(struct ata_link *link, unsigned int reg, u32 val)
{
	void __iomem *port_base;
	int err = -EIO;

	switch (reg) {
	case SCR_CONTROL:
		port_base = (void __iomem *)link->ap->port_base;
#ifdef CONFIG_FSL_SATA_V2
		err = scr_wr_reg(port_base, 233, val);
		scr_set_reg(port_base, 3, val & (1<<0));
#endif /* CONFIG_FSL_SATA_V2 */
		return err;
#ifdef CONFIG_SATA_OXNAS
	case 3: /* SCR_CONTROL_SE */
		sata_oxnas_send_sync_escape(link->ap);
		return 0;
#endif