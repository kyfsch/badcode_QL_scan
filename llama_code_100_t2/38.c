// This function is used to disable/enable Asic's port mirroring functionality..
ret_t rtl8367c_setAsicPortMirrorRxFunction(rtk_uint32 enabled)
{
	return rtl8367c_setAsicRegBit(RTL8367C_AGCCTRL_REG(0), RTL8367C_PORTMIRRORENABLE_OFFSET, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorRxFunction
 * Description:
 *      Get Asic's port Rx mirror function enabled/disabled
 * Input:
 *      pEnabled    - 1: enabled  0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_TUNNEL_INNER - Invalid inner header type.
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorRxFunction(rtk_uint32 *pEnabled)
{
	return rtl8367c_getAsicRegBit(RTL8367C_AGCCTRL_REG(0), RTL8367C_PORTMIRRORENABLE_OFFSET, pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicPortMirrorTxFunction
 * Description:
 *      Set Asic's port Tx mirror function enabled/disabled
 * Input:
 *      enabled    - 1: enabled  0: disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_TUNNEL_INNER - Invalid inner header type.
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorTxFunction(rtk_uint32 enabled)
{
	return rtl8367c_setAsicRegBit(RTL8367C_AGCCTRL_REG(0), RTL8367C_PORTMIRROR