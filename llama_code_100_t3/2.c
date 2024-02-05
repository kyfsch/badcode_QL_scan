// This function is used to send a sync escape command to a controller.
static inline void sata_oxnas_send_sync_escape(struct ata_port *ap)
{
	unsigned long flags;
	struct ata_device *dev = ap->link.device;
	struct ata_oxnas_pdata *pdata = ap->host->private_data;
	struct sata_link *slp = &dev->link;

	spin_lock_irqsave(&ap->lock, flags);

	pdata->hba[dev->hint_port].tx_cmd_len = 1;
	pdata->hba[dev->hint_port].tx_cmd[0] =
		HBI_REQ_BYT + HBI_REP_BYT + 1 + 32 - 1;
	pdata->hba[dev->hint_port].tx_cmd[1] = HOP_PACKET_HEAD;
	pdata->hba[dev->hint_port].tx_cmd[2] = HBI_REQ_ESC;
	pdata->hba[dev->hint_port].tx_cmd[3] = HBI_REQ_SYNC;
	pdata->hba[dev->hint_port].tx_cmd[4] = HBI_REP_SYNC;

	pdata->hba[dev->hint_port].tx_byte_count = 32;
	pdata->hba[dev->hint_port].fifo_len = ((pdata->hba[dev->hint_port].tx_cmd_len +
				pdata->hba[dev->hint_port].tx_byte_count + 8) >> 2) << 6;

	hbi_set_phy_ctrl(dev->hint_port, slp->pmp_port, pdata->hba[dev->hint_port].fifo_len);

	spin_unlock_irqrestore(&ap->lock, flags);

	slp->ops.sata_oxnas_issue_packet_cmd(ap, dev->link.device->hint_port, HOP_PACKET_HEAD);

	msleep(10