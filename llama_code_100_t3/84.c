/// This function is used to set ports on the switch</s>.
static int psb6970_set_ports(struct switch_dev *dev, struct switch_val *val)
{
	/*
	 * This function is only used in the 'ports' setting in
	 * /lib/firmware/nvidia/7313-0.61.40/nv.7313.40.gpio.bin
	 * So, the value should be all ports and 0
	 */
	if (val->value.i == 0) {
		val->value.i = 0x80;
		return 0;
	}

	return -EINVAL;
}

#ifdef CONFIG_PSB_CENTER_HDMI

static int psb6970_port_enable(struct switch_dev *dev, int port, int enable)
{
	struct drm_psb_private *dev_priv = container_of(dev, struct drm_psb_private, ddc_ bus_sw_dev);
	struct hda_intel *hda = dev_priv->hda;
	struct pci_dev *hda_pcidev = hda->pcidev;
	int i;

	if (!port_enabled(hda->ports[port].sense, port))
		return 0;

	switch (port) {
	case 0:
		iowrite32(0x00000000, hda->mmio_base + HDA_HOST_CTRL);
		break;
	case 1:
		iowrite32(0x00000008, hda->mmio_base + HDA_HOST_CTRL);
		break;
	case 2:
		iowrite32(0x00000202, hda->mmio_base + HDA_HOST_CTRL);
		break;
	case 3:
		if (hda_pcidev->revision == 0x69)
			iowrite32(0x00000606, hda->mmio_base + HDA_HOST_CTRL