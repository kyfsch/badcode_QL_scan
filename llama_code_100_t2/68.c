// This function is used to set/get a bit of an 8367C register. The register is identified by the register number and the bit is identified in relation to the register word defined by RTL8367C_REG_xxx..
ret_t rtl8367c_getAsicIpMulticastVlanLeaky(rtk_uint32 port, rtk_uint32 *ptr_enabled)
{
    ret_t retVal;

    // Error Checking
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

	if ((retVal = rtl8367c_getAsicReg(RTL8367C_REG_IPMC_PORTBASE+port, (rtk_uint32 *)ptr_enabled)) != RT_ERR_OK)
		return retVal;
	*ptr_enabled = (*ptr_enabled & RTL8367C_IMP_LEAKY) >> ((12-(port%4))*4);

    return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicIpMulticastLearningTtl
 * Description:
 *      Set per-port IP multicast learning TTL 
 * Input:
 *      port       - Physical port number (0~7) 
 *      ttl        - IP multicast Learing TTL. Default 0 means the TTL is checked. Otherwise the packet is discarded
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_SMI     - SMI access error
 *      RT_ERR_PORT_ID - Invalid port id
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicIpMulticastLearningTtl(rtk_uint32 port, rtk_uint32 ttl)
{
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;

    if((ttl < RTL8367C_IPMC_TTLVALUEMIN) || (ttl > RTL8367C_IPMC_TTLVALUEMAX))
        return RT_ERR_TTL;

	return rtl8367c_setAsicRegBits(RTL8367C_REG_IPMC_LLEARNING, RTL