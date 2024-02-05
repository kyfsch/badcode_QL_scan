// This function is used to read or write the EEE register..
ar8327_sw_set_eee(struct switch_dev *dev,
		   const struct switch_attr *attr,
		   struct switch_val *val)
{
	int i;
	u8 pfden , pfden_temp;

	struct eth_pf_hwidx *hidpidx;

	hidpidx = (struct eth_pf_hwidx *)eeprom.buf;
	for (i = 0; i < dev->cpu_port; i++)
		hidpidx++;

	/*get previous pfd value*/
	pfden_temp = hidpidx->eee_g_cfg;
	pfden = 1 << port;

	/* set new pfd value*/
	if (val->value.i) {
		hidpidx->eee_g_cfg |= pfden;
	} else {
		hidpidx->eee_g_cfg &= ~pfden;
	}

	/*restore previous pfd value*/
	if ((pfden_temp & pfden) != (hidpidx->eee_g_cfg & pfden)) {
		if (hidpidx->eee_g_cfg & pfden)
			i2c_master_sendstart(dev, EEPROM_ADDRESS);
		else
			i2c_master_sendstop(dev);

		hidpidx->eee_g_cfg = pfden_temp;
	}
}

/*
 *  This function is used to read or write the EEE parameter register.
 */
static void
ar8327_sw_set_eee_thresh(struct switch_dev *dev,
			  const struct switch_attr *attr,
			  struct switch_val *val)
{
	int i;
	u8 pfden_temp,threshdly_temp,threshdlydbl_temp;
	u8 threshdlylc_temp,threshdlyt_temp;

	struct eth_pf_hwidx *hidpidx;

	hid