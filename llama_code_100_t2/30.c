// This function is used to write to registers of rtl839x chip,.
void rtl839x_set_port_reg_be(u64 set, int reg)
{
	u64 new_val;

	if(reg > RTL8390_PRTMSK)
		reg = RTL8390_PRTMSK;
	if(reg < RTL8390_PRT0)
		reg = RTL8390_PRT0;

	new_val = rtl839x_get_port_reg(reg);

	new_val |= set;
	rtl839x_set_port_reg(new_val, reg);
}
EXPORT_SYMBOL(rtl839x_set_port_reg_be);

// This function is used to write to port registers of rtl839x chip.
void rtl839x_port_reg_be_set_bits(u64 set, int reg)
{
	u64 new_val;

	if(reg > RTL8390_PRTMSK)
		reg = RTL8390_PRTMSK;
	if(reg < RTL8390_PRT0)
		reg = RTL8390_PRT0;

	new_val = rtl839x_get_port_reg(reg);

	new_val |= set;
	rtl839x_set_port_reg(new_val, reg);
}
EXPORT_SYMBOL(rtl839x_port_reg_be_set_bits);

// This function is used to write to port registers of rtl839x chip.
void rtl839x_port_reg_be_clear_bits(u64 clear, int reg)
{
	u64 new_val;

	if(reg > RTL8390_PRTMSK)
		reg = RTL8390_PRTMSK;
	if(reg < RTL8390_PRT0)
		reg = RTL8390_PRT0;

	new_val