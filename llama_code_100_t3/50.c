// This function is used to fill the device sprom data structures for legacy spi devices at time of initialization. This will be called only once after the chip is initialized..
static DEFINE_SPINLOCK(ssb_fbs_lock);
extern unsigned char sprom_csr_w4; // defined in ssb_pci.c. This sprom chip select wire is enabled using CS_SROM_W and not CS_SROM_W_B
    int ssb_pci_fill_firmware_info(struct pci_dev *pcidev, struct ssb_init_firmware *fw)
{
    int i;
    if (fw->fw == NULL)
        return 1;
    init_MUTEX(&sprom.lock);
    for (i = 0; i < fw->count; i++) {
// This will map any SSB RFMD style sprom to the spi type, so that we may use the same firmware code to read those fw chips, that is supported in the sprom type
        if (firmware_devices[i].type == DEV_TYPE_SSBSIM_SPROM) {
            firmware_devices[i].deviceID = SROM4_PCI_ID;
            firmware_devices[i].devicePCIE = SROM4_PCIE_ID;
            firmware_devices[i].type = DEV_TYPE_SSB_SROM4;
            firmware_devices[i].typeid = firmware_devices[i].deviceID;
        }
        if (firmware_devices[i].type != DEV_TYPE_INVALID) {
            spin_lock_bh(&ssb_fbs_lock);
            firmware_devices[i].firmwarestate.fw = fw->fw;
            firmware_devices[i].firmwarestate.fwcount = fw->count;
            firmware_devices[i].firmwarestate.fwindex = i;
            spin_unlock_irqrestore(&ssb_fbs_lock, 7);
        }
    }
    return 0;
}
#endif

#define SSB_FW_TYPE_MAX    5

int ssb_is_supported_dev(const struct ssb_device *