// This function is used to set the mode of VLAN OAM packet to be processed by the OAM forwarder. The valid mode is CPUFWD, CPUFWD2, CPUFWD3, PARFWDCPU, DSPFWDCPU..
ret_t rtl8367c_setAsicOamParser(rtk_uint32 port, rtk_uint32 parser)
{
    ret_t retVal;
    rtk_uint32 regData;

    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if((port != RTL8367C_CPU_PORT1 && port!= RTL8367C_CPU_PORT2) || parser > RTL8367C_OAM_FORWD2)
        return RT_ERR_INPUT;

    if (port == RTL8367C_CPU_PORT1)
        regData = RTL8367C_CPU1_OAM_PARSER_SEL;
    else
        regData = RTL8367C_CPU2_OAM_PARSER_SEL;

    if((retVal = rtl8367c_getAsicReg(regData,&regData))!=RT_ERR_OK)
        return retVal;

    regData &= 0xFFFF - (3 << ((port - 1) * 2));
    regData |= (parser << ((port - 1) * 2));
    if((retVal = rtl8367c_setAsicReg(regData,regData))!=RT_ERR_OK)
        return retVal;
    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicOamParser
 * Description:
 *      Get VLAN OAM packet processing mode
 * Input:
 *      rtk_uint32 port  - Physical port number (0~7)
 * Output:
 *      rtk_uint32 *parser - VLAN OAM processg method
 * Return:
 *      RT_ERR_OK     - OK
 *      RT_ERR_FAILED - Failed
 *      RT_ERR_SMI   - SMI access error
 *      RT_ERR_PORT_ID - Invalid port number.
 *      RT_ERR_INPUT  - Invalid input parameters.
 * Note:
 *