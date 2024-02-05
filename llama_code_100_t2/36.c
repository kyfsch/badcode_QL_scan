// This function is used to get mib variables in the switch_dev structure..
static int rtl8367_sw_get_port_mib(struct switch_dev *dev,int port,char *cmd,u32 mib_flag,u32 mib_index)
{
    u32 reg_value;
    int ret = 0;

    if (port >= RTL8367B_PHY_MAX_PORTS)
        return -EINVAL;
    if ( cmd == NULL || mib_flag== 0 || mib_index >256)
        return -EINVAL;

    //read specific port's mib variables
    if (mib_flag) {
        if ((mib_index>=0x100)&&(mib_index<0x100+4)) {
            //Get tx mib variable
                rtl8367b_setAsicReg(RTL8367B_REG_ETHERMIB_TX_FLIT_SZ_BASE1,port);
                rtl8367b_setAsicReg(RTL8367B_REG_ETHERMIB_TX_FLIT_BURST_BASE1,port);
                rtl8367b_setAsicReg(RTL8367B_REG_ETHERMIB_TX_FLIT_GAP_BASE1,port);
        } else if ((mib_index>=0x200)&&(mib_index<0x200+4)) {
            //Get rx mib variable
        } else {
            return -EINVAL;
        }
        rtl8367b_getAsicReg(RTL8367B_REG_PVC_ETHERMIB_CTRL_BASE_1+port*4,&reg_value);
        reg_value &= 0xf;
        switch (reg_value) {
            case 0:
                rtl8367b_getAsicReg(RTL8367B_REG_PVC_ETHERMIB_OCTET_SZ_BASE1+mib_index,&reg_value);
                snprintf(dev->stats[port].mib_cnt[mib