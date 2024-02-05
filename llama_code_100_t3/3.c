// This function is used to write a certain register in the PHY device. It should be pretty simple. It takes a PHY address and register, and a value to write, then it generates the appropriate command to write the value to the register in the PHY. For.
static int rtl8367_write_phy_reg(struct rtl8366_smi *smi, uint32_t devAddr,
				uint16_t regAddr, uint16_t phyReg)
{
	struct rtl8366c_priv *priv = (struct rtl8366c_priv *) smi->priv;
	u8 *buf;

	buf = kcalloc(1, sizeof(uint16_t) * smi->words, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	WARN_ON(smi->mode == RTL8366_SMI_NONE);

	if (PHY_DEBUG)
		pr_debug("%s:dev : %s, addr : %d, reg : %d, data [0x%04x]\n",
			__func__,
			priv->switch_name[devAddr], devAddr, regAddr, phyReg);

	if (smi->mode == RTL8366_SMI_4) {
		buf[1] = regAddr;//(ph)>>16;
		buf[2] = devAddr;//(ph)>>16&3;
		buf[3] = phyReg;
	} else {
		buf[1] = devAddr;
		buf[2] = regAddr;
		buf[3] = phyReg;
	}

	/* Write */
	rtl8366_write_smi(smi, RTL8366_SMI_CMD_MIIM_REG_W, buf);
	kfree(buf);
	if (dlink_phy_id_get(devAddr, NULL) < 0)
		pr_err("%s, phy ID is error\n", __func__);
	return 0;
}

int rtl8366_phy_read(struct rtl8366_smi *smi, uint32_t devAddr, uint32_t regAddr,