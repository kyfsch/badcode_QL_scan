// This function is used to remove the MDB from the switch table. The switch table is composed of two components, the hashed table and the CAM table. In case of LAG ports, there is an additional hashed table called hash_slave table stored in the.
int rtl83xx_port_mdb_del(struct dsa_switch *ds, int port,
			 enum port_mdb_options options, void *data)
{
	u16 vid = 0;

	switch (options) {
	case PORT_MDB_ADD_VIDS:
		vid = (u16)data;

		/* 1 means drop vid */
		return rtl838x_port_set_vid(ds, port, 0x1, vid, 0);
	case PORT_MDB_ADD_UC:
		/* Adds unicast MAC entry to the MA table - L3 entry */
		return rtl838x_mtab_l2_add(ds, port, data, 0, 1);
	case PORT_MDB_ADD_MC:
		/* Adds multicast MAC entry to the MA table - L3 entry */
		return rtl838x_mtab_l2_add(ds, port, data, 1, 1);
	case PORT_MDB_DEL:
		return rtl838x_mtab_l2_del(ds, port, data, 1, 1);
	default:
		break;
	}
	return 0;
}

int rtl8x10_get_ports(struct dsa_switch *ds)
{
	if (strcmp(ds->drv->name, "rtl838x"))
		return -EOPNOTSUPP;
	rtl83xx_set_max_frame_size(ds, 1560);

	/* Configure the ports.  The ports from 1-127 are 48-bit
	 * ports, ports 128-159 are 24-bit ports.

	 * In the default configuration:
	 * - Ports 1-3 are 48-bit ports
	 * - Ports 4-5 are special G-MAC ports (Sys. P0 - 48, 5)
	 */
	rtl838x_set_switch_core(