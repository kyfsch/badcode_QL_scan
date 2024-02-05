/// This function is used to unregister the device from kernel.</s>.
ar8327_led_unregister(struct ar8327_led *aled)
{
	int i, err;

	if (aled->registered) {
		struct ar8327_led_pdata *arpriv = aled->priv;
		struct ar8327 *ar = arpriv->ar;
		int devid;
		struct led_classdev *led_cdev;

		devid = ar8327_led_mode2id(ard->id, aled->mode);
		if (devid < 0)
			return devid;

		led_cdev = &aled->led_cdev;
		err = regmap_update_bits(ar->regmap_base, AR8327_REG_LED[devid],
					LED_F_ACTIVE_OFF | LED_F_PWM_TIMER_OUTPUT,
					0);
		if (err < 0)
			return err;
		ar->ops->led_blink_on(arpriv);

		sysfs_remove_link(&arpriv->dev->kobj, aled->name);
		for (i = aled->mode_count - 1; i >= 0; i--)
			led_classdev_detach_light(arpriv->dev, &aled->led_cdev);
		aled->registered = false;
		ar->ops->led_blink_off(arpriv);
	}

	return 0;
}
EXPORT_SYMBOL(ar8327_led_unregister);

static int ar8327_led_unregister_all(struct ar8327 *ar)
{
	struct ar8327_led_pdata *arpriv = ar->led_priv;
	struct ar8327_led *aled = arpriv->led;
	int i = ARRAY_SIZE(aled);
	int err = 0;

	while (i--) {
		err = ar8327_led_unregister