/// This function is used to retrieve the value of VLAN ID at a certain port. I have made it such that it is always zero. What is the difference between these 2 values?</s>.
ar8xxx_sw_get_vid(struct switch_dev *dev, const struct switch_attr *attr,
		 struct switch_val *val)
{
	struct ar8xxx_priv *priv = sw_get_priv(dev);
	int addr, port;

	/*
	 * Translate the switch's port number (0-7, 16-23) to the AR8XXX
	 * register space (0-7, 8-15).
	 */
	if (val->port_vlan >= SWITCH_PORT_VID_INVALID) {
		val->value = ar8xxx_vtu_get_port_vid(priv,
				val->port_vlan - AR8XXX_NUM_PORTS);
	} else {
		addr = AR8XXX_REG_S2_PORT_BASE + 8 * val->port_vlan;
		port = ar8xxx_num_ports(priv);
		for (port = 0; port < AR8XXX_NUM_PORTS; port++) {
			/* Disable learning on all ports. */
			ar8xxx_reg_write(priv, AR8XXX_REG_GLOBAL,
					 AR8XXX_GLOBAL_PORT_CTRL(port), 0);
			ar8xxx_reg_write(priv, AR8XXX_REG_S2_PORT_BASE + port,
					 AR8XXX_PORT_PVID, addr | 0x1);
			ar8xxx_reg_write(priv, AR8XXX_REG_S2_PORT_BASE + port,
					 AR8XXX_PORT_PVID, addr);
			msleep(1);
		}

		ar8xxx_vtu_sw_vid(priv, val->port_vlan, &val->value);
	}

	return 0;
}

static void ar8xxx_vtu_sw_vid_set(struct ar8xxx_priv *priv,
				  int port, int vid)
{
	u8 reg;

	ar8xxx_vtu_sw_vid(priv