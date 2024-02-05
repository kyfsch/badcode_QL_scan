/// This function is used to set the LED settings on rtl931x chips. This function will be called from platform data.</s>.
static void rtl931x_led_init(struct rtl838x_switch_priv *priv)
{
	const struct rtl931x_led_info *ledinfo;
	int i, j, num_leds;
	const u32 *led_map;

	ledinfo = rtl931x_leds_info;
	num_leds = ARRAY_SIZE(rtl931x_leds_info);
	/* we need to set LED_PWM and LED_POWER_ON_OFF and LED_ENABLE to 0 */
	led_map = rtl931x_pri_led_map;

	for (i = 0; i < num_leds; i++) {
		REG_WR(priv->io, RTL931X_LED_PORT_MAP_CTRL(led_map[i]), 0);
		rtl931x_program_led_timer(priv, led_map[i],
					  DIV_ROUND_CLOSEST(ledinfo[i].led_on[0], 10000),
					  DIV_ROUND_CLOSEST(ledinfo[i].led_off[0], 10000));
		for (j = 0; j < RTL931X_NUM_LED_ON_OFF_REGS; j++) {
			rtl931x_program_led_off(priv, led_map[i],
				ledinfo[i].led_off[j], j);
			rtl931x_program_led_on(priv, led_map[i],
				ledinfo[i].led_on[j], j);
		}
		/* set to color mode */
		REG_WR(priv->io, RTL931X_LED_POLARITY_CTRL_0 + (led_map[i] * 4),
		       RTL931X_LED_POLARITY_CTRL_0_L_LED_POLARITY_CTRL_0);