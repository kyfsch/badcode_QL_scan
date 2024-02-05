// This function is used to thaw a disconnected host (when the port is down).
void sata_oxnas_thaw_host(struct ata_port *ap)
{
	void __iomem *mmio_base = ap->host_set->hwif->mmio_base;
	int i = 9*ap->port_no;
	u32 host_ctl = 0;
	u32 err_sta = 0;
	u32 err_src = 0;
	u32 dqs_src = 0;

	/* Save the current host ctl & error ctl and disable irq source */
	host_ctl = sata_oxnas_read_port_reg(ap, OXNAS_SATA_PORT_HOST_CTL);
	sata_oxnas_write_port_reg(ap, OXNAS_SATA_PORT_HOST_CTL,
		host_ctl | OXNAS_HOST_CTL_INTR_DIS);
	sata_oxnas_read_port_reg(ap, OXNAS_SATA_PORT_ERR_SRC);
	err_src = sata_oxnas_read_port_reg(ap, OXNAS_SATA_PORT_ERR_SRC);
	err_sta = sata_oxnas_read_port_reg(ap, OXNAS_SATA_PORT_ERR_STA);
	dqs_src = sata_oxnas_read_port_reg(ap, OXNAS_SATA_PORT_DQS_SRC);

	/* Clear old messages */
	sata_oxnas_write_port_reg(ap, OXNAS_SATA_PORT_DQS_SRC, dqs_src);

	/* Restore host_ctl & error_src settings */
	sata_oxnas_write_port_reg(ap, OXNAS_SATA_PORT_HOST_CTL, host_ctl);
	sata_oxnas_write_port_reg(ap, OXNAS_SATA_PORT_ERR_CTL, err_sta & ~0x3);
	sata_oxnas_write_port_reg(ap, OXNAS_SATA