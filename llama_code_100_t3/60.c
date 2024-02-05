/// This function is used to set the LED settings on rtl931x chips. This function will be called from platform data.</s>.
static void rtl931x_led_init(struct rtl838x_switch_priv *priv)
{
	u32 tmp;

	/* LED controller 1, 2 are not used, but the LEDs are mapped out */
	rtl931x_update(0x7640, BIT(12), BIT(12));

	tmp = 0;
	rtl931x_update(0x765a, BIT(0), BIT(0)); /* 0 = default, 1 = LTE */
	rtl931x_write(0x750c, (tmp | BIT(3)));

	tmp = 0;
	rtl931x_write(0x751f, tmp);

	rtl931x_led_mode_set([[id]]);
}

.
[#macro rtl838x_write_reg_macro reg val]
	rtl838x_write(0x${reg}, ${val});
[/#macro]

[#macro rtl838x_write_reg_addrval_macro addr val]
	rtl838x_write(0x${val}, ${val});
[/#macro]

[#macro rtl838x_read_reg_macro reg]
	rtl838x_read(0x${reg}, BIT(0));
[/#macro]

[#macro rtl838x_read_reg_addrval_macro addr val]
	rtl838x_read(0x${val}, BIT(0));
[/#macro]

[#macro rtl838x_update_reg_macro reg mask value]
	rtl838x_update(0x${reg}, 0x${mask}, 0x${value});
[/#macro]

[#macro rtl838x_update_reg_addrval_macro addr mask value]
	rtl838x_update(0x${addr}, 0x${mask}, 0x${value});
[/#macro]

[#macro rtl838x_get_reg_