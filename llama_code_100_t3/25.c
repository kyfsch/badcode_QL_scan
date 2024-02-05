// This function is used to probe the device, it takes a pointer to the platform device structure as an argument and returns a pointer to the rtl8366_smi structure.The smi structure contains all the information related to the device, including the device ID.
struct rtl8366_smi *rtl8366_smi_probe(struct platform_device *pdev)
{
    int ret = -1;
    struct rtl8366_smi *smi = NULL;

    if ((smi = kzalloc(sizeof(*smi), GFP_KERNEL)) == NULL) {
        rtlinfo(RTLLOG_CRIT, "Failed to allocate memory for driver structure\n");
        return NULL;
    }

    platform_set_drvdata(pdev, smi);

    // Read vendor ID
    if ((ret = rtl8366_reg_read(pdev, RTL8366_REGIDX(HW_CHIPVER), &smi->chipver)) != 0)
    {
        rtlinfo(RTLLOG_CRIT, "Failed to read device version!\n");
        goto error_reg_read;
    }

    if (((smi->chipver & 0xe000) >> 10) != 0) {
        smi->family_id = 0x12;
        smi->chip_id = 0xa;
        smi->chip_rev = (( smi->chipver & 0xc000) >> 14);
    } else {
        smi->family_id = 0x2;
        smi->chip_id = 0x9;
        smi->chip_rev = 0x0;
    }

    // Allocate io memory for this device!
    if ((ret = rtl8366_allocate_io(&pdev->dev, &smi->io)) != 0) {
        goto error_allocate_io;
    }

    // Initialize SMI structure according to the chip ID
    switch (smi->family_id) {
    case 0x2:
        if (smi->chip_id == 0x8) {
            memcpy(&(smi->ops), &(r8390_ops), sizeof(r8390_ops));
        } else if ((smi->chip