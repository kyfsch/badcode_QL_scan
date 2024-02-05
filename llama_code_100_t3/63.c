// This function is used to apply vlan mapping to mt7530 chip.
mt7530_apply_mapping(struct mt7530_priv *mt7530, struct mt7530_mapping *map)
{

	if (mt7530_mt7531_check(mt7530)) {
		// MT7531-based mt7530 does not need mapping for switch port
		return;
	}

	// In MT7621, Ports 2 will not forward if disabled but the port 2 may be connected to
	// server on another port, so we need to check this port
	// The case is similar to port 8, if port 8 is disabled but is connected to port 9, then port 8 will not forward frame.
	if (map->port == MT7530_N_PORTS)
		/* map all but port 2 (which becomes unmap port) */
		mt7530_apply_mapping_one_port(mt7530, 2, false);

	// TODO: check if it does not create performance issue, i.e. port < port <= MT7530_N_PORTS should be processed firstly...
	for (int port = 0; port <= MT7530_N_PORTS; port++)
		if (map->port != MT7530_N_PORTS || port != 8 )
			mt7530_apply_mapping_one_port(mt7530, port, true);
}

// The function is used to configure VLAN mapping and port mapping for one port
mt7530_map_port(struct mt7530_priv *mt7530, unsigned int port,
		uint8_t port_mapping)
{
	uint16_t val;
	uint16_t reg;
	uint16_t vlan_mapping_low[4];
	uint16_t vlan_mapping_high[4];

	reg = MT7530_PORT(port);
	// Set Port VLAN mapping
	val = read_val(mt7530, MT7530_VLAN_CTL, 0x05