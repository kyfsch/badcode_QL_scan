// This function is used to read a register value, and the value will be filtered through some logic.  It returns 0 (no error) if operation completed..
static int bcm6328_pcie_read(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 *value)
{
	*value = 0;

	if (!pci_get_bus_and_slot(bus, devfn)) {
		pci_write_config_dword(bus, devfn, where, ~0U);
		switch (size) {
		case 1: *value = (u32)pci_read_config_byte(bus, devfn, where); break;
		case 2: *value = (u32)pci_read_config_word(bus, devfn, where); break;
		case 4: *value = pci_read_config_dword(bus, devfn, where); break;
		}
	};

	return 0;
}

// This function is used to write a register value, and the value will be filtered through some logic.  It returns 0 (no error) if function completed.
static int bcm6328_pcie_write(struct pci_bus *bus, unsigned int devfn,  int where, int size, u32 value)
{
	if (!pci_get_bus_and_slot(bus, devfn)) {
		pci_write_config_dword(bus, devfn, where, value);
	};

	return 0;
}

// In case someone wants to access some special config space registers through their kernel driver. For example accessing the root port's device.
/*
static int bcm6328_pcie_access(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 *value, bool write)
{
	*value = 0;

	if (!pci_get_bus_and_slot(bus, devfn)) {
		if (where == 0xf00) *value = where;
		else pci_write_config_dword(bus, devfn, where, ~0U);

		switch (size) {
		case 1: *value = (u32)pci_read