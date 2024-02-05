// This function is used to initialize the psb6970 PHY and register the required PHY driver..
int __init psb6970_init(void) {
    int index;

    int status_reg[3];
    int speed; //store the  current speed

    //This should not be zero.I just want to see what will happen if it's zerp
    if (NULL == pci_init(0, 0, 0, 0))
        return 1;
    //check if the pci bus is available to 210 device from ebu
    if (-1 == is_pci_bus_available(HUB_PCI_BUSS, HUB_PCI_SLOT))
        return 1;
    pdev = pci_find_device (PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_6970, NULL);
    if (pdev == NULL) {
        DPRINTK (KERN_INFO "pci_find_device error:pci_device can not be found\n");
        return 1;
    }
    //disable the pci device 210
    if (0 != pcibios_read_config_word(pdev->bus->number, pdev->devfn, PCI_COMMAND, &config_cache)) {
        DPRINTK (KERN_INFO"pci_find_device error:Can't read config word\n");
        return 1;
    }
    config_cache &= ~PCI_COMMAND_MASTER;
    if (0 != pcibios_write_config_word(pdev->bus->number, pdev->devfn, PCI_COMMAND, config_cache)) {
        DPRINTK (KERN_INFO"pci_find_device error:Can't write config word\n");
        return 1;
    }
    //This check if the pci device 210 already has a mdi, then it will be set on pmdi, else it will be enabled.
    if (0 != pcibios_read_config_word(pdev->bus->number, pdev->devfn, PSB_PSB69