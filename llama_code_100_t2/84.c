/// This function is used to set ports on the switch</s>.
static int psb6970_set_ports(struct switch_dev *dev, struct switch_val *val)
{
	int ret;

	mutex_lock(&psb_mutex);
	/* switch 1 is 0x70 , 1 is 0x76, 2 is 0x73, 3 is 0x7c */
	ret = regmap_write(psb_rmap,val->port_vlan.port,
			    PSB6970_SWITCH_REG_PORT_CTRL_0 |
			    (val->port_vlan.vlan << PSB6970_PVID_SHIFT));
	if (ret)
		goto out_unlock;

	/* enable a frame to be sent from p0 in case of failure */
	ret = regmap_update_bits(psb_rmap,
				  PSB6970_SWITCH_REG_PORT_CTRL_2,
				  PSB6970_PORT2INTP_ENABLE,
				  PSB6970_PORT2INTP_ENABLE);
	if (ret)
		goto out_unlock;

	ret = regmap_update_bits(psb_rmap,
				  PSB6970_SWITCH_REG_PORT_CTRL_1,
				  PSB6970_PORT_TAG_MODE |
				  PSB6970_PORT_TRUNK_MODE,
				  PSB6970_PORT2TRUNK_MODE1 |
				  PSB6970_PORT_TRUNK_MODE);

	if (ret)
		goto out_unlock;

	/* make sure switch config is saved */

	/* 0x7e is the SAVE_REG_PORT_CTRL_3 */
	ret = regmap_update_bits(psb_rmap,
				  PSB6970_SWITCH_REG_PORT_CTRL_3,