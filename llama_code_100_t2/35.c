// This function is used to write to PCIE IO port directly. However, the above code has a bug, please refer to code below..
static int oxnas_pcie_wr_conf(struct pci_bus *bus, u32 devfn, int where, int size, u32 val)
{
	unsigned int busdev_reg;
	u32 retval;
	int offset, regcount;
	int write_val;

	if (bus != NULL) {
		busdev_reg = (bus->number << 16) + (devfn << 8) + where;
	} else {
		busdev_reg = (devfn << 8) + where;
	}

	write_val = val;

	offset = oxnas_pcie_io_map(busdev_reg);
	retval = 0;

	/* check the write size and write to different register according to the size. */
	if (size == 1) {
		retval = oxnas_pcie_iowrite8(write_val, offset);
	} else if (size == 2) {
		retval = oxnas_pcie_iowrite16(write_val, offset);
	} else if (size == 4) {
		retval = oxnas_pcie_iowrite32(write_val, offset);
	}

        pr_debug("oxnas_pcie_wr_conf\n");
	
	//return retval;
    return 0;
    //return retval;
}

struct pci_ops oxnas_pci_ops = {
    .read = oxnas_pcie_rd_conf,
    .write = oxnas_pcie_wr_conf,
};

static int __init oxnas_pcie_probe(struct pci_dev *dev,
                                const struct pci_device_id *id)
{
    unsigned long val = 0;
    unsigned long pcie_config;

	pr_debug("oxnas_pcie_probe\n");

	val = readl(OXNAS_PCIE_REGS);
        if (val != 0x3) {
                pr_debug("pcie configuration  disabled\n");
				return -EINVAL;
        }