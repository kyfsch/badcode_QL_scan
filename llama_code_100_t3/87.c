// This function is used to resume the ethernet adapter on an OMAC2 device. The first part of the function sets the hardware to detect that it has woken up from hibernation, and the last part enables the ethernet transceivers..
static int rtl8214fc_resume(struct phy_device *phydev)
{
	struct rtl8214_priv *priv = phydev->priv;
	u16 reg = 0xffff;
	int ret;

	ret = rtl8214cc_read(priv, 0, RTL8214_LRC_CONFIG, &reg);
	if (ret)
		return ret;

	reg |= RTL8214_LRC_RESUME;
	ret = rtl8214cc_write(priv, 0, RTL8214_LRC_CONFIG, reg);
	if (ret)
		return ret;

	return rtl8214cc_write(priv, 0, RTL8214_PHY_RESUME_CONTROL,
			      RTL8214_RESUME_CONTROL);
}

// The rtl8214fc_fixup function gets as an argument the device ID of the ethernet controller. For this particular ethernet controller, the function calls a couple of other functions to set up various registers.
static int rtl8214fc_fixup(struct pci_dev *pdev,
			   struct phy_device *phydev)
{
	struct rtl8214_priv *priv;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	pci_set_drvdata(pdev, priv);

	priv->base_addr = pci_resource_start(pdev, 0);
	priv->cmd_reg = priv->base_addr + RTL8214_EPHY_CTRL_REG;
	priv->mac_hwsem_mutex_lock = priv->base_addr + RTL8214_MAC_HWS_MUTEX_LOCK;
	priv->mac_hwsem_mutex_release = priv->base_addr +
		RTL8