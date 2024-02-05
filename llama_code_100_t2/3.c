// This function is used to write a certain register in the PHY device. It should be pretty simple. It takes a PHY address and register, and a value to write, then it generates the appropriate command to write the value to the register in the PHY. For.
static int rtl8367_write_phy_reg(struct rtl8366_smi *smi, uint32_t phy_addr, unsigned int phy_register, unsigned short phy_data)
{
	u8 write_regaddr[4];

	if (smi == 0)
		return -EINVAL;

	if ((phy_addr > RTL8367_PHY_MAX) || (phy_register > RTL8367_PHY_REG_MAX))
		return -EINVAL;

	write_regaddr[0] = (phy_addr);
	write_regaddr[1] = (phy_register & 0xFF);
	write_regaddr[2] = (phy_register >> 8);
	write_regaddr[3] = (phy_data);


	//smi->smi_ops.write_regs(phy_device,"4D058820", 1, write_regaddr);
	return 0;
}

static int rtl8367_parse_page(struct rtl8366_smi *smi, int page)
{
	return 0;
}

// This function sets the PLL loopback mode. It also takes a PHY address. It should be pretty simple. It takes a PHY address, then it generates the appropriate command to enter the loopback mode.


//rtl8390_set_pllmute_state(u32 phy_id, u32 pllmute_enable)
//{
//    u32 reg[3];
//    u8 addr[4];

//    if(phy_id >= MAX_PHY_NUM) {
//        return -EINVAL;
//    }

//    reg[2]=RTLSHE_R32(RTLSHE_REG_PHY0_PHY_CON1 + phy_id*0x200);
//    reg[0]=RTLSHE_R32(RTLSHE_REG_PHY0_PHY_CON + phy_id*0x200);
//    reg[1]=RT