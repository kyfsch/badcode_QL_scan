// This function is used to read a register value, and the value will be filtered through some logic.  It returns 0 (no error) if operation completed..
static int bcm6328_pcie_read(struct pci_bus *bus, unsigned int devfn, int where, int cfg_size, u32 *value)
{

    struct bcm6328_pcie_controller *bcm6328_pcie;
    int data;

    if (!pci_cfg_bus_addr)		//check if it had init once
    {
        printf("bcm6328_pcie_read: not initialized yet, fail and exit..\n");
        return 1;
    }

    bcm6328_pcie = to_bcm6328_pcie(pci_cfg_bus_addr);

    if (where & 0x3)
    {
        return 1;
    }

    data = (*(int *)((void *)bcm6328_pcie_mem_addr + bcm6328_pcie->conf_base + (where & 0xfc))) | pci_cfg_bus;
#if defined(MIPS32_CPU)
    *value = (unsigned long)(data);	// return actual byte location
#else //not MIPS32_CPU
    *value = (u32)((unsigned long)(data));	// return actual byte location
#endif // not MIPS32_CPU

    return 0;			// no error
}


// This function is used to write a register value, and the value will be filtered through some logic.  It returns 0 (no error) if operation completed .
static int bcm6328_pcie_write(struct pci_bus *bus, unsigned int devfn, int where, int cfg_size, u32 value)
{
    struct bcm6328_pcie_controller *bcm6328_pcie;
    u32 reg_data;

    void *bcm6328_pcie_base;

    if (!pci_cfg_bus_addr)		//check if it had init once
    {
        printf("bcm6328_pcie_write: not initialized yet, fail and exit..