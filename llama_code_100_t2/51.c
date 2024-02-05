// This function is used to remove the NFC device from the platform.
static int mt7621_nfc_remove(struct platform_device *pdev)
{
    char strName[20] = {0};
    struct kobject *kobj;
    struct device *dev;
    struct mtk_nand_host *host;
    struct gen_nand_host *nand_host;
    int dev_id;
    struct rtk_nand_chip* nand_chip;

    // get device name
    dev = (&pdev->dev)->parent;
    snprintf(strName, sizeof(strName), "%s", dev_name(dev));

    dprintf(CRITICAL, "[mt7621_nfc_remove]: remove nand %s \n", strName);

    kobj = &pdev->dev.kobj;

    if (!kobject_is_registered(kobj))
    {
        dprintf(CRITICAL, "[mt7621_nfc_remove]: device %s is already removed!!!\n", strName);
    }
    else
    {
        /* call device-release() function to cleanup the device */
        platform_device_release(&pdev);

        // unregister device
        dprintf(CRITICAL, "[mt7621_nfc_remove]: device %s is unregistered!!!\n", strName);
    }

    /* destroy the gen_nand class device */
    dev_id = (&pdev->dev)->id;
    if (dev_id != -1)
    {
        host = nf_chip_data[dev_id];
        if (!host)
        {
            dprintf(CRITICAL, "[mt7621_nfc_remove]: NFC dev(%d) is removed!!!\n", dev_id);
            return -ENODEV;
        }
        nand_host = host->nand_host;
        if (!nand_host)
        {
            dprintf(CRITICAL, "[mt7621_nfc_remove]: nf_dev(%d) is invalid!!!\n", dev_id);
            return -ENODEV