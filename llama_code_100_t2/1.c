// This function is used to match mapping names provided by platform.
mt7530_find_mapping(struct device_node *np)
{
	if (OF_PROP_COUNT(np) >= 2)
		return MT7530_MAP_VLAN;
	else if (OF_PROP_COUNT(np) == 1)
		return ((OF_PROP_COUNT(child) == 2) &&
			(of_prop_cmp(child->name, "#address-cells", sizeof("#address-cells")) == 0)) ?
				MT7530_MAP_RESERVED : MT7530_MAP_PORT_PROP;

	return MT7530_MAP_UNKNOWN;
}

// This function does all necessary work for mapping.
// Mapping is an important concept for mt7921.
static int mt7697_of_mt753x_map(struct mt7530_priv *priv,
				const struct gsw_api_mt7530_map_req* map)
{
	int i;
	u32 tmp;
	int ret;

	u64 port_bitmap = 0;
	if (map->map_type == MT7530_MAP_PORT_PROP)
	{
		// Map to port property.
		for (i = 0; i < map->port_index; i++)
		{
			if (MT753X_PORT_EXIST(map->port_id[i], mt7530_priv))
			{
				if (map->port_prop[i] != -1)
					MT753X_PORT(map->port_id[i], mt7530_priv)->port_prop = map->port_prop[i];

				port_bitmap |= MT753X_PORT(map->port_id[i], mt7530_priv)->port_no;
				continue;
			}
			else
			{