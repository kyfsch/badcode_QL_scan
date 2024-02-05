// This function is used to get the value of mirror_tx. It.
ar8xxx_sw_get_mirror_tx_enable(struct switch_dev *dev,
			     const struct switch_attr **attr,
			     struct switch_val *val)
{
	val->value.i = arcc_sw_mirror_tx_enable;
}

static int
// This function is used to set the value of mirror_tx.
ar8xxx_sw_set_mirror_tx_enable(struct switch_dev *dev,
			     const struct switch_attr *attr,
			     struct switch_val *val)
{

	int rc;

	val->value.i = 0; // Set mirror_tx to the value passed in.

	rc = arcc_ctrl_write_sram_reg(AR933X_MIRROR_TX_REG_CPU_WR_TX_EN, val->value.i);
	if (rc < 0)
	{
		printk(KERN_ERR "%s:set error %d mirror_tx rc\n", __func__, rc); 
		goto exit;
	}

	rc = arcc_sw_set_hw_mirror_tx_enable(val->value.i);
	if (rc < 0)
	{
		printk(KERN_ERR "%s:set error %d hw_mirror_tx_enable rc\n", __func__, rc);
		goto exit;
	}
	arcc_sw_mirror_tx_enable = val->value.i;
exit:
	return rc;
}

/*
 * This function is used to set the value of the hardware mirror_tx_enable.
 */
int arcc_sw_set_hw_mirror_tx_enable(int value)
{
	return arcc_ctrl_write_sram_reg(AR933X_MIRROR_TX_REG_CPU_TX_EN, value);
}

/*
 * This function is used to reset the value of the hardware mirror_tx_enable.
 */
int arcc_sw_reset_hw_mirror_tx_enable(void)
{