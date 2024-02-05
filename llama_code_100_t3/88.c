// This function is used to write the value to phy register..
int rtl839x_write_phy(u32 port, u32 page, u32 reg, u32 val)
{
	u32 mac_addr = PORT_TO_MAC_ADDR(port);
	mac_addr += ((page)<<16) + (reg<<4);

	return mii_write(mac_addr, val);
}


// This function is used to write the value to phy register..
int rtl838x_write_phy(u32 port, u32 page, u32 reg, u32 val)
{
	u32 mac_addr = PORT_TO_MAC_ADDR(port);
	// MAC address is constructed as follows:
	// 0,3:  Page, in case MII management
	// 4:  Write (not used here)
	// 5-6:  Register
	// 7-15:  Don't care
	//	mac_addr = PORT_TO_MAC_ADDR(port);
	mac_addr += ((page&0x7)<<6) + (reg<<1) + ((mii_reg_select& 3)<<13) + (1<<12);

	return mii_write(mac_addr, val);
}


/*
 * This function is used to write a value to a specific port, 
 * and in a specific register
 */
int rtl838x_write_reg(u32 val, u32 reg)
{
	u8 offset = (reg & 0x1F)<<1;
	u32 mac_addr = 1<<12 + offset;
	if (reg > 0x84)
		RTU_MSG(RTU_PRINT_ERR, "rtl838x_write_reg: Only 0-10 register implemented!\n");

	return dma_write(mac_addr, val);
}

// This function is used to fetch the value of the register passed to it

u32 rtl839x_read_reg(u32 addr)
{
	u32 val;
	mii_read(addr, &val);
	return