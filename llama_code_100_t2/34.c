// This function is used to write the register value. In addition to this, there are read functions for reading the different registers in the IPE chip. These are defined in the header file /kernel/drivers/net/ethernet/realtek/816.
static int rtl8367_mii_write(struct mii_bus *bus, int addr, int reg, u16 val)
{
    struct rtl8367_mii_priv *mii_priv;
    int rc=0;
	RTL8367B_MII_REG reg_info = {0};

    RTL8367B_DOT1PHY_INT_MASK  int_mask={0};
	DBG5("rtl8367_mii_write: addr:0x%04x -> 0x%04x\n", addr, reg, val);
	mii_priv = bus->priv;

    spi_master_cs_enable(rtl8367_spi);
    reg_info.reg_addr = (u8)reg;
    reg_info.reg_data = (u16)val;

    if(write_reg(RTL8367B_DOT1PHY_INT_MASK_REGISTERID, (u8 *)&int_mask, sizeof(u8))<0){
	    dev_err(rtl8367_spi_dev,"spi write failed when write reg \n");
    }
    if(write_reg(RTL8367B_MII_REGISTERID, (u8 *)&reg_info, sizeof(u16))<0){
	    dev_err(rtl8367_spi_dev,"spi write failed when write reg \n");
    }
    spi_master_cs_disable(rtl8367_spi);

    return rc;
}

int rtl8367_mii_write_pre(struct mii_bus *bus, int addr, int dev)
{
	struct rtl8367_mii_priv *mii_priv;
	mii_priv = bus->priv;

    //dev_dbg(&bus->dev, "%s: regs->phy_id=%d, addr=0x%04x, dev=0x%04x\n",
		//__func__, bus->phy_id, addr, dev