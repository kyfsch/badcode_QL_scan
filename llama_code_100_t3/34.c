// This function is used to write the register value. In addition to this, there are read functions for reading the different registers in the IPE chip. These are defined in the header file /kernel/drivers/net/ethernet/realtek/816.
static int rtl8367_mii_write(struct mii_bus *bus, int addr, int reg, u16 val)
{
	int i;
	int ret = 0;
	u32 ioaddr, wtemp;
	u8 *cp, mdio_dir = 0x0;

	ioaddr = (u32)bus->priv;;
	if (addr == 32)      // this register is defined in 8168c family chips.
		mdio_dir |= 0xc;
	else
		mdio_dir |= 1;

	cp = (u8 *) &wtemp;
	mdio_dir = swab16(mdio_dir);
	for (i = 0; i < 2; i++)
		cp[i] = mdio_dir;
	wtemp = wtemp >> 16;
	rtl8367b_writew(cp, ioaddr + PORT_0 , (u16)wtemp);

	cp = (u8 *) &wtemp;
	reg = swab16(reg);

	cp[0] = 0x4;
	if (reg != 0)
		reg--;
	cp[1] = reg;
	cp[2] = (val&0xFF);
	cp[3] = ((val>>8)&0xFF);
	wtemp = wtemp >> 16;
	rtl8367b_writew(cp, ioaddr + PORT_0 , (u16)wtemp);
	ret = rtl8367b_readw(ioaddr + PORT_0 + 2) & 0x20;

	return 0;
}

int RT_R8367_EEPROM_READ16(u32 bus, int addr, int *data)
{
	u16 tmp;

	tmp = (addr & 0x7)<<11 | ((addr>>3)&0x1f)<<6;

	rtl8367_mii_write(NULL, addr, 17, tmp);  // The 17th register controls the external EEP