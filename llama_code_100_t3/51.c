/// This function is used to remove the NFC device from the platform.
static int mt7621_nfc_remove(struct platform_device *pdev)
{
	struct mtk_nfc_ioc *nfc_ioc = platform_get_drvdata(pdev);

	if (!nfc_ioc)
		return 0;

	disable_irq(gpio_to_irq(nfc_ioc_gpio_irq));

	pr_info("%s: exit OK!\n", __func__);
	return 0;
}

static struct platform_driver mt7621_nfc_driver = {
	.probe = mt7621_nfc_probe,
	.remove = mt7621_nfc_remove,
	.driver = {
		   .name = "mtk-nfc-7621",
		   .owner = THIS_MODULE,
		   },
};

static int __init mt7621_nfc_setup(void)
{
	return platform_driver_register(&mt7621_nfc_driver);
}

void __exit mt7621_nfc_cleanup(void)
{
	platform_driver_unregister(&mt7621_nfc_driver);
	pr_info("%s: cleanup OK!\n", __func__);
}

module_init(mt7621_nfc_setup);
module_exit(mt7621_nfc_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("MTK");
MODULE_DESCRIPT</s>