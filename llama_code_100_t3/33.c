// This function is used to initialize the ar8xxx driver. When the hardware resources in ar8xx chip are used to initialize, which function is used to achieve the initialization?.
ar8327_hw_init(struct ar8xxx_priv *priv)
{
    unsigned int	mask_vlan0_member_high;
    unsigned int	mask_vlan0_member_low;
    u16		vid;
    u8		val8;

    val8 = R8327_LAN_PRL_CTRL;
	ar8xxx_get_ephy_reg(priv, AR8327_EPHY_REG(20), val8);
    // We only set ephy register when the first device join the VLAN
    val8 |= 0x10;
    ar8xxx_set_ephy_reg(priv, AR8327_EPHY_REG(20), val8);

    mask_vlan0_member_high = BIT_VTU_FID_ALL_VID_EN_IGNORE |
    			BIT_VTU_FID_ALL_VID_BUSY;

    mask_vlan0_member_low = AR8327_PORT_STATE_L;

	ar8xxx_clr_misc(priv, AR8327_REG_MISC_PORT_STATE,
			mask_vlan0_member_low);
    ar8xxx_mask_misc(priv, AR8327_REG_MISC_PORT_STATE,
    			mask_vlan0_member_low, 0xFFFF);
	if (ar8xxx_get_version(priv) >= 0x594A) {
		if (ar8xxx_get_version(priv) == 0x594C)
			val8 = 19;
		else
			val8 = 18;
	} else {
		if (ar8xxx_get_version(priv) >= 0x5231)
			val8 = 6;
		else
			val8 = 5;
	}
	// Write ephy register 40 to 5F to set default ephy configuration
	ar8xxx_set_e