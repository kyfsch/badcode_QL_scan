/// This function is used to set the member ports and untag ports of a vlan.</s>.
int rtl8366_sw_set_vlan_ports(struct switch_dev *dev, struct switch_val *val)
{
	int i, rc = 0;
//	struct rtl8366_sw_priv *priv = port_dev_to_rtl8366_sw(dev);
//	u8 num_ports, data;
//
//	/* Make sure Port IDs are of type DEV_PORT */
//	if (val->id_type != SWITCH_PORT_ID_DEV)
//		return -EINVAL;
//
//	/* Make sure the flags are correct */
//	if (val->flags != (PORT_FLAG_SET | PORT_FLAG_ADD | PORT_FLAG_REMOVE) ||
//		val->len == 0)
//		return -EINVAL;
//
//	/* Sanity check the port list */
//	for (i = 0; i < val->len; i++) {
//		/* Make sure this is a port ID */
//		if (val->value[i] >= SWITCH_MAX_PORTS)
//			return -EINVAL;
//	}

	switch_set_handle_vlan_ports(val, rtl8366_sw_ops_ptr->port_unlock, rtl8366_sw_ops_ptr->set_vlan_ports_mask);

	switch_set_handle_vlan_ports(val, rtl8366_sw_ops_ptr->port_unlock, rtl8366_sw_ops_ptr->set_vlan_ports);

	return rc;
}
EXPORT_SYMBOL(rtl8366_sw_set_vlan_ports);

/*
 * rtl8366_sw_add_vlandb
 */
int rtl8366_sw_add_vlandb(struct switch_dev *dev, struct switch_val *val)
{
	int rc = 0;
	struct rtl8366_sw_priv *priv = sw_dev_to_priv(dev);

	if (val->port_vlan