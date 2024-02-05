// This function is used to thaw a disconnected host (when the port is down).
void sata_oxnas_thaw_host(struct ata_port *ap)
{
	if (!ap->link.device)
		return;

	// Enable host and set port to inactive.
	sata_oxnas_host_enable(ap);
	sata_oxnas_set_port_inactive(ap);
}

static int sata_oxnas_softreset(struct ata_link *link, unsigned int *class, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct sata_oxnas_device_context *dev_ctx_p = link->ap->private_data;
	int ret;
	unsigned long deadline_j;
	unsigned int timeout_ms;

	if (time_after_eq(jiffies, deadline))
		return -1;

	timeout_ms = jiffies_to_msecs(ap->em_messages[ATA_EH_RESET_TIMEOUT]/HZ);
	if (timeout_ms > dev_ctx_p->default_timeout_ms)
		timeout_ms = dev_ctx_p->default_timeout_ms;

	deadline_j = jiffies + dev_ctx_p->default_timeout_ms*HZ/1000;
	while (time_before(jiffies, deadline_j)) {
		// Host reset
		sata_oxnas_reset_host(ap);

		// Reset device.
		ret = sata_oxnas_reset_link(link, deadline_j, SOATA_OXNAS_RESET_COLD);
		if (ret == 0) {
			// Device ID.
			ret = sata_oxnas_get_device_id(ap);
			if (ret == 0) {
				// Read device info.
				ret = sata_oxnas_read_device_capabilities(link);
				if (ret)
					ata_link_info(link, "Controller reset successful\n");
			}