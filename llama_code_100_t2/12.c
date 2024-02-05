// This function is used to obtain the port mirror state. When calling the function, port mirroring is enabled. If it returns 1 and port mirroring is enabled means to send packets to the set port. If it returns 0 and port mirroring is.
ret_t rtl8367c_getAsicPortMirrorTxFunction(rtk_uint32* pEnabled)
{
	if(pEnabled == NULL)
		return RT_ERR_NULL_POINTER;

	return rtl8367c_getAsicReg(3,3,pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicPortMirrorEnabled
 * Description:
 *      Set port mirror function enable/disable
 * Input:
 *      port        - physical port number (0~7)
 *      enabled    - 1: enable 0:disable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID         - invalid port id
 * Note:
 *      The port mirroring function is enabled by default.
 */
ret_t rtl8367c_setAsicPortMirrorEnabled(rtk_uint32 port, rtk_uint32 enabled)
{
	if(port > RTL8367C_PORTIDMAX)
		return RT_ERR_PORT_ID;
	
	return rtl8367c_setAsicRegBit(port*2,RTL8367C_PMTR_ENABLE_OFFSET,enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorEnabled
 * Description:
 *      Get port mirror function enable/disable
 * Input:
 *      port        - physical port number (0~7)
 *      pEnabled    - 1: enable 0:disable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_PORT_ID         - invalid port id
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorEnabled(rtk_uint32 port, rtk_uint32* pEnabled)
{
	if(port > RTL836