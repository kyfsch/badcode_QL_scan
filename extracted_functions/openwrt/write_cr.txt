static void write_cr(void __iomem *phy_base, u16 data, u16 address)
{
	iowrite32((u32)address, phy_base + PHY_STAT);
	wait_cr_ack(phy_base);
	iowrite32((data | CR_CAP_DATA), phy_base + PHY_DATA);
	wait_cr_ack(phy_base);
	iowrite32(CR_WRITE_ENABLE, phy_base + PHY_DATA);
	wait_cr_ack(phy_base);
}
