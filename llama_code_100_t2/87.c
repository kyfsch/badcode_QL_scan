// This function is used to resume the ethernet adapter on an OMAC2 device. The first part of the function sets the hardware to detect that it has woken up from hibernation, and the last part enables the ethernet transceivers..
static int rtl8214fc_resume(struct phy_device *phydev)
{
    bool retval = 0;
    u16 tmp;
    u32 value;
    value = 7;
    phy_write(phydev, MDIO_DEVAD_NONE, 7, value); // set to power on default
    value = 43;
    retval = phy_read(phydev, MDIO_DEVAD_NONE, 18);
    phy_write(phydev, MDIO_DEVAD_NONE, 18, (retval & 0xffcf)|value); // Clear bit14 of 18
    retval = phy_read(phydev, MDIO_DEVAD_NONE, 0);
    phy_write(phydev, MDIO_DEVAD_NONE, 0, retval&0x1bff); // Clear bit10,11 of 0
    tmp = 43;
    retval = phy_read(phydev, MDIO_DEVAD_NONE, 18);
    phy_write(phydev, MDIO_DEVAD_NONE, 18, (retval & 0xffcf)|tmp);// set to power on default
    rtl8214fc_apply_firmware(phydev);
    return 0;
}

// This function is used to initialize the MAC after resume from hibernation.
static int rtl8214fc_config_init_resume_mac(struct phy_device *phydev)
{
    bool retval = 0;
    u32 rtlmac_value = 0;
    u32 value = 0;

    // phy_write phy37, register 0x15, 0x3e60.

    retval = phy_read(phydev, MDIO_DEVAD_NONE, 0x15);
    phy_write(phydev, MDIO_DEVAD_NONE, 0x15, 0x3e60);