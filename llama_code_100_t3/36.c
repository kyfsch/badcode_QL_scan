// This function is used to get mib variables in the switch_dev structure..
static int rtl8367_sw_get_port_mib(struct switch_dev *dev, int port, int type, struct switch_mib *mib){
    u16 value;
    int index[3];
    int block = switch_dev_id(dev);

    do {
        if(port >= dev->ports){
            printk("port error\n");
            return ERROR;
        }
        // get the correct register index according to switch type(vlan or non vlan)
        index[0] = block;
        index[1] = port;
        index[2] = type;

        if(rtl8367b_getAsicPortMibHugeCounter(index, &value) != SUCCESS){
            printk("get fail\n");
            return ERROR;
        }
        switch(type){
        case MIB_TYPE_TX_BROADCAST:
        case MIB_TYPE_TX_MULTICAST:
        case MIB_TYPE_RX_BROADCAST:
        case MIB_TYPE_RX_MULTICAST:
        case MIB_TYPE_TX_UNICAST:
        case MIB_TYPE_RX_UNICAST:
            mib->values[0] = value;
            break;
        case MIB_TYPE_RX_64_127:
        case MIB_TYPE_RX_128_255:
        case MIB_TYPE_RX_256_511:
        case MIB_TYPE_RX_512_1023:
        case MIB_TYPE_RX_1024_MAX:
        case MIB_TYPE_RX_1024_3072:
            mib->values[0] = value  & 0xFFF;
            value = (u16)(0xFFFF0000 & value);
            if(rtl8367b_getAsicPortMibHugeCounter(index, &value) != SUCCESS){
                printk("get fail\n");
                return ERROR;
            }
            mib->values[1] = value