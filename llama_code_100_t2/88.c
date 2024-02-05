// This function is used to write the value to phy register..
int rtl839x_write_phy(u32 port, u32 page, u32 reg, u32 val)
{
    u32 reg_val = ((page & 0x1F) << 16) | ((reg & 0x1F)<<11) | ((val & 0xFFFF));
    rtl839x_set_phy_reg(port, reg_val);
    if (reg > 32 && reg < 64) {
	    return rtl839x_set_phy_reg(port,reg_val | (0x2 << 18));
    }

    return 0;
}

int init_phy(u32 port)
{

	// Reset the MII management port
    // TODO Reset is done for every port every time init_phy is called. Only reset if
    // port was never initialized before
	rtl839x_mii_mgmt_reset(port, 0);

    printf("init phy port: %d\n", port);

	//Set first page
	rtl839x_write_phy(port, 0, 31, 0x4000);

    //write_phy(port, 0, 31, 0x4200);

    // Mask the interrupt register of the specific phy
    // The interrupt status is masked at each link change, and so they are not
    // printed
    //int32_t val = rtl839x_read_phy(port, 0, 7);
    //val &= ~(0x7);
    //rtl839x_write_phy(port, 0, 7, val);

    // Disable Auto-Negotiation
    // Disable Auto-Crossover - Enable Auto-MDIX
  //  rtl839x_write_phy(port, 0, 23, 0x1000);

    // Select 1000BASE-T Control
    rtl839x_write_phy(port, 0, 17, 0x01a0);

    //