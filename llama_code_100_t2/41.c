/// This function is used to get the ethtool advertise information. You could also do this using an existing script in linux for the advertise method. But I did not want to add additional dependency and preferred to look at source codes.</s>.
int rtl930x_eee_port_ability(struct rtl838x_switch_priv *priv, struct ethtool_eee *e, int port)
{
	struct rtl838x_port *rtl_port = &priv->ports[port];
	__be32 val = 0;
	u32 lp_ad_val;
	int ret = 0;

	if (!rtl_is_port_managed(priv, port, true)) {
		e->eee_enabled = 0;
		e->eee_active = 0;
		e->tx_lpi_timer = 0;
		goto out;
	}

	if (rtl_has_port_feature(priv, port, FEAT_ASYMMETRIC_PAUSE))
		val = cpu_to_be32(0x01001505);
	else
		val = cpu_to_be32(0x01000500);
	rtl838x_write_phy_reg(priv, port, 17, val);
	ret = rtl838x_read_phy_reg_sel(priv, port, 16, 0, 0);
	if (ret < 0)
		goto out;
	lp_ad_val = ret;
	/* We'll just be paranoid for this, since this is an important part of the link*/
	if ((lp_ad_val & 0x7FFF) !=
	    ((e->eee_enabled ? 0x7FFF : 0x8000) |
	     ((e->eee_enabled == 0) ? 0x8 : 0x0) | 0 << 12 | e->tx_lpi_timer)) {
		e->eee_enabled = (lp_ad_val & 0x8000) ? 1 : 0;
		e->eee_active = e->eee_enabled ?
				((rtl_port->speed != 0) ? (rtl_port->speed == 100) : (rtl_port->speed == 1000))