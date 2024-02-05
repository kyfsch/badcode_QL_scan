/// This function is used to retrieve the value of VLAN ID at a certain port. I have made it such that it is always zero. What is the difference between these 2 values?</s>.
ar8xxx_sw_get_vid(struct switch_dev *dev, const struct switch_attr *attr,
		  struct switch_val *val)
{
	struct ar8xxx_priv *priv = ar8xxx_priv(dev->cpu_id);
	u16 devid;
	int i, ret = 0;

	priv->chip_ver_reg = ar8xxx_reg_read(priv, AR8216_REG_SYS_VER4);
	devid = (priv->chip_ver_reg >> 8) & 0xFF;

	for (i = 0; i < ETH_GSTRING_LEN; i++) {
		strncpy(priv->switch_id.driver_info[i], __stringify(devid),
			ETH_GSTRING_LEN);
		strncpy(priv->switch_id.driver_info[i+1],
			__stringify(priv->chip_revision), ETH_GSTRING_LEN);
		strncpy(priv->switch_id.driver_info[i+2],
			priv->soc, ETH_GSTRING_LEN);
	}
	for (i = ETH_GSTRING_LEN*3; i < 4*3; i += 3) {
		sprintf(priv->switch_id.driver_info[i], "%d-%d",
			(priv->chip_revision >> 8) & 0xFF,
			priv->chip_revision & 0xFF);
		sprintf(priv->switch_id.driver_info[i+1], "%d.%d",
			(priv->chip_ver_reg >> 7) & 0xF,
			priv->chip_ver_reg & 0x7f);
		sprintf(priv->switch_id.driver_info[i+2], "%s", priv->soc);
	}
	ret = asic_data_dump_phy_ports(dev);
	if (ret < 0)
		return ret;

	ret = asic_set_vid_from_