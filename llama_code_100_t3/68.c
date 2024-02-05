// This function is used to set/get a bit of an 8367C register. The register is identified by the register number and the bit is identified in relation to the register word defined by RTL8367C_REG_xxx..
ret_t rtl8367c_getAsicIpMulticastVlanLeaky(rtk_uint32 port, rtk_uint32 *ptr_enabled)
{
    ret_t retVal;
    rtk_uint32 portData = port & 0x1FF;
    rtk_uint32 regData = 0;


    if(port >= RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if (portData > RTL8367C_PORTMAX)
        return RT_ERR_PORT_ID;

    retVal = rtl8367c_getAsicReg(RTL8367C_PORT_MCAST_LEAKY_VLAN_CTRL_REG(port), &regData);
    if(retVal != RT_ERR_OK)
        return retVal;

    *ptr_enabled = (regData >> RTL8367C_MC_LKY_VLAN_EN_OFFSET) & 0x1;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicIpMcFilterStatus
 * Description:
 *      Set multicast IP filtering status
 * Input:
 *      status 	- IP filtering status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK 			- Success
 *      RT_ERR_SMI  		- SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicIpMcFilterStatus(rtk_uint32 status)
{
    if(status > RTL8367C_IP_UNIQUE_MC_MUX)
        return RT_ERR_ENABLE;

    return rtl8367c_setAsicRegBit(RTL8367C_IP_MC_FILTER_CTRL_REG, RTL8367C_IP_MC_FILTER_EN_OFFSET, status);
}
/* Function Name:
 *      rtl8367c_getAsicIpMcFilterStatus
 * Description: