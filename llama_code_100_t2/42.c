// This function is used to remove the MDB from the switch table. The switch table is composed of two components, the hashed table and the CAM table. In case of LAG ports, there is an additional hashed table called hash_slave table stored in the.
int rtl83xx_port_mdb_del(struct dsa_switch *ds, int port, const struct switchdev_obj_port_mdb *mdb)
{
	return 0;
}

struct net_device* rtl838x_get_slave(struct dsa_switch *ds, int slave)
{
	struct net_device *bcm, *dev;
	struct rtl838x_switch *sw = ds->priv;
	struct rtl838x_smi_priv *priv = sw->smi_data;
	int port, phy_port;

	if (!(priv->sw_bcm && priv->slave))
		return NULL;

	bcm = priv->sw_bcm;
	switch (slave) {
	case 1:
		dev = priv->slave;
		break;
	case 2:
		dev = priv->slave2;
		break;
	case 3:
		dev = priv->slave3;
		break;
	case 4:
		dev = priv->slave4;
		break;
	case 5:
		dev = priv->slave5;
		break;
	default:
		dev = NULL;
		break;
	}

	if (!dev) {
		/*
		 * The BCM has a master LAG-ID and a list of "slaves"
		 * If any slave is found its LAG-ID needs to be set in the HW
		 */
		port = bcm_lag_get_slave_port(dev_priv(bcm)->ds);
		if (port < 0)
			return NULL;
		phy_port = dev_mapping_real(bcm)[port];

		/* Write a new slave to the switch table:
		 * port		->	slave
		 * 0xC000	->	0x0200
		 */
		rtl838x_smi_write(dev_priv(bcm)->ds, 0xC000, 0