// This function is used to read or write the EEE register..
ar8327_sw_set_eee(struct switch_dev *dev, const struct switch_attr *attr,
				const struct switch_val *val)
{
	struct ar8327_state *priv = container_of(dev, struct ar8327_state, swdev);
	int ret = 0;
	u32 reg_val = 0;
	u16 ret_val = 0;

	if (val->len == 0)
		return 1;

	if (!strcmp(val->string_value, "on")) {
		dev->ports[0].enable_egress_mode = 1;
		dev->ports[0].egress_enabled_port = 0x40;
		ar8327_write(priv, AR8327_EEE_CFG, 0x4000);
	} else if (!strcmp(val->string_value, "off")) {
		dev->ports[0].enable_egress_mode = 0;
		ret_val = 0x0000;// disable EEE
		ar8327_write(priv, AR8327_EEE_CFG, 0x00);
	} else
		ret = 1;

	if(ret == 0)
		dev->ports[0].status_flags = 1;

	if( val->port_vlan >=0 ) {
		if ( val->len >= 1 )
			ret_val |= val->string_value[val->len - 1] - '0';
		else
			return 1;
	}
	if( ret_val == 0x00 || ret_val == 0x40 ) {
		if( dev->ports[val->port_vlan].status_flags == 1) {
			dev->ports[val->port_vlan].egress_enabled_port = ret_val;
			dev->ports[val->port_vlan].status_flags = 0;
			ar8327_write(