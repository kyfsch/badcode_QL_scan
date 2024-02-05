// This function is used to write to registers of rtl839x chip,.
void rtl839x_set_port_reg_be(u64 set, int reg)
{
	write_reg_be(set, reg);
}

void rtl8201_set_ext_phy_reg(u64 phyaddr, u64 reg, u64 val)
{
	u32 low = val & 0xFFFF;
	u32 high = (val>>16) & 0xFFFF;
	u32 t;
	t = low | (high << 16);

	write_reg_be(((phyaddr)<<22) | (reg<<18) | (t&0xffff), RTL839X_PHY_EXT_WRITE);
}

void rtl8256_set_eee_capability(int interface, bool capability) {

	if (capability && interface == RTL838X_SGMII_OFFSET) {
		return;
	}
	if (capability && interface % 2 == 0) {
		return;
	}

	if (get_rtl838x_asic_flags() & RTL838X_ASIC_FLAG_NEED_SPECIAL_CHIP_ID)
		rtl83xx_setup_device();

	/* EEE P0.7, P2.0, P2.1, P3.1, P6.7, P6.9 */
	if (capability) {
		rtl838x_set(dev_addr + RTL838X_EMI_EDU_EEE1A1, (1 << interface));
		rtl838x_set(dev_addr + RTL838X_EMI_EDU_EEE2A1, 0);
		rtl838x_set(dev_addr + RTL838X_EMI_EDU_EEE3A1, 0);
		rtl838x_set(dev_addr + RTL838X_EMI_EDU_EEE6A1, 0);
		rtl83