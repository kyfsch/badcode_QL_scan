// This function is used to write to PCIE IO port directly. However, the above code has a bug, please refer to code below..
static int oxnas_pcie_wr_conf(struct pci_bus *bus, u32 devfn, int where,
       u32 size, u32 val)
{
        struct pci_pbm_info *pbm = get_phb_pbm(bus->sysdata);
        int is_aer_cap;
        u64 cfg_addr;

        if (!(devfn & 0x80))
                return PCIBIOS_DEVICE_NOT_FOUND;

        /*
         * The PXA is really simple we can just look the devfn up in the pci config
         * space info.
         */
        devfn &= 0x7f;

        /* If we have an IO-Window, use pxa_io_map */
        if (pbm->pci_io_base != 0) {
                if (devfn != 0x00)
                        return PCIBIOS_DEVICE_NOT_FOUND;

                return __pxa_write_pci_config(pbm, where, size, val);
        }

        config_read8(&is_aer_cap, pbm->pci_config_space, 0, 0, PCI_CAPABILITY_LIST);
        while (is_aer_cap & 0x0f) {
                unsigned long offset, next;
                int p_cap_id;

                if (is_aer_cap == 0xff) {
                        is_aer_cap = 0;
                        break;
                }

                offset = (is_aer_cap & 0xF0) >> 2;
                config_read8(&p_cap_id, pbm->pci_config_space, 0, 0, offset);
                if (p_cap_id == PCI_CAP_ID_AER)
                        is_aer_cap = 0;
                else
                        config_read8(&is_aer_cap, pbm->pci_config_space, 0, 0, offset + 1);
                next = is_aer_cap & 0xF0;
                while