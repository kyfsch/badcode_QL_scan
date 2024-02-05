// This function is used to list all of the supported attributes in their respective attributes lists. This attribute list is basically a list of struct switch_attributes which is defined like this.
swconfig_list_attrs(struct sk_buff *skb, struct genl_info *info)
{
	...
}


// This function is used by the cli command for the config command to read attributes passed for the switch_config_set command.
static int swconfig_config_attrs(__be32 *addr, struct genl_info *info,
				     struct switch_attr_cfg *cfg)
{
	const struct nlattr **attrs = info->attrs;
	...
}


```

As you can see the attributes are defined in the generic netlink interface of switch. So when configuring a switch, if the user inputs the attributes as a list, the generic netlink interface will be used to send the attributes to netfilter which will inturn send them to the switch driver. This is done via the flowing function.

```

// When configuring a switch, this function will send the attributes set to the switch driver.
int br_switchdev_handle_port_attrs(struct net *net,
				  struct datapath *dp, void *swdev_priv,
				  struct switchdev_attr *attr,
				  struct switchdev_trans *trans)
{
	...
	
		attr.orig_dev = dp->netdev;
		attr.trans = trans;
		attr.flags = attr.orig_attr.flags;
		...
	}
	
	list_for_each_entry(af, &switch_attr_list, node) {
#ifdef HAVE_SWITCHDEV_ATTR_OP_BRIDGE_FLAGS_BRIDGED
    		if (!br_switchdev_allowed_attr(af, NULL, cmd) ||
			af->str.brc_attr == cmd)
			continue;

		if (af->str.brc_attr == SWITCHDEV_ATTR_ID_INVALID &&
		    af->brport_attr > SWITCHDEV_ATTR_ID_MAX)
			continue;
#else
		if (!br_switchdev_allowed_attr(af))
			continue;