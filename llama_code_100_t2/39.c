/// This function is used to unregister the device from kernel.</s> .
ar8327_led_unregister(struct ar8327_led *aled)
{
	spin_lock_bh(&aledrv_lock);
	list_del_init(&aled->next);
	aledrv_unregister_one_led(aled);
	spin_unlock_bh(&aledrv_lock);
}
EXPORT_SYMBOL(ar8327_led_unregister);
void
ar8327_led_unregister_all(void)
{
	ar8327_init();
	ar8327_led_unregister_one_led(aledrv_info.led);
}
EXPORT_SYMBOL(ar8327_led_unregister_all);
</s>