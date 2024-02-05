// This function is used to flush the packet buffers belonging to a.
ar8216_atu_flush_port(struct ar8xxx_priv *priv, int port)
{
	int i;

	for (i = 0; i < AR8XX_NUM_L2_PORTS; i++) {
		if (priv->ports[i].membership == port ||
		    priv->ports[i].membership == AR8XXX_MEMB_ALL)
			ar8xxx_atu_flush_station(priv, i);
	}
}

// Checks all stations on a port to see if it matches the port number and
// and flush the data from the port, and the arp cache.
static void ar8327_atu_flush_port(struct ar8xxx_priv *priv, int port)
{
	int i;

	for (i = 0; i < priv->num_ports; i++) {
		if (priv->ports[i].membership == port ||
		    priv->ports[i].membership == AR8XXX_MEMB_ALL)
			ar8327_atu_flush_station(priv, i);
	}

	ar8327_dev_control_load(priv);
	ar8327_set(priv, AR8327_REG_PORT(port, AR8327_PORT_FORCE_AGE), 0);
}

static inline u32 ar8xxx_get_port_id_state(struct ar8xxx_priv *priv, int port)
{
	if (priv->chip->flags & AR8XXX_FLAG_ATU_WRITE_BCAST)
		return port;
	else
		return BIT(port);
}

int ar8xxx_dev_port_enable_vlan(struct ar8xxx_priv *priv, int port,
				u16 vid, u8 flags)
{
	u32 reg;

	reg = BIT(31) | ar8xxx_get_port_id_state(priv, port);
	reg |= flags;
	if (vid)
		reg |= BIT(16) | vid;
	AR8XXX_