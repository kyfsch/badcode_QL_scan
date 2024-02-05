/// This function is used to set the member ports and untag ports of a vlan.</s>.
int rtl8366_sw_set_vlan_ports(struct switch_dev *dev, struct switch_val *val)
{
    struct rtl8366_vlan * vinfo;
    struct rtl8366_pvt *vpvt = rtl8366_private_data_get(dev);

    if (!vpvt)
        return -1;
    vinfo = rtl8366_vlan_get(dev, val->value.i);
    if (! vinfo) {
        vinfo = rtl8366_vlan_add(dev, val->value.i);
        if (! vinfo)
            return -1;
    }

    if (val->val_type == SWITCH_PORT_ARRAY) {
        struct switch_port **ports;
        unsigned int port_num;

        ports = val->value.ports;
        port_num = val->len;

        return rtl8366_sw_vlan_set_ports(dev, vinfo, ports, port_num);
    }

    printk("%s: unknown val type %d",__FUNCTION__, val->val_type);
    return -1;
}

    .
    .
    .
int rtl8366_sw_set_vlan(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
    struct rtl8366_pvt * vpvt = rtl8366_private_data_get(dev);
    if (!vpvt)
        return -1;

    .
    .
    .
}
    .
    .
    .
//rtl8366 sw_set_bridge_vlan.c end
 
    rtl8366_sw_set_bridge_vlan(..)

```

rtl8366 sw_set_bridge_vlan.c
============
rtl8366 默认支持 所有1Q-8Q,并且仅支持以太网的交换. 如下图是基于树莓派