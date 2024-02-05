// This function is used to disable/enable Asic's port mirroring functionality..
ret_t rtl8367c_setAsicPortMirrorRxFunction(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_MONITOR_CTRL2, RTL8367C_RXMIRROR_ENABLED, enabled);
}
/* Function Name:
 *      rtl8367c_getAsicPortMirrorRxFunction
 * Description:
 *      Get Asic's port mirroring in/out function switch
 * Input:
 *      pEnabled       - 1: Enabled, 0: Disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK         - Success
 *      RT_ERR_SMI        - SMI access error
 *      RT_ERR_INPUT     - Invalid input parameters
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicPortMirrorRxFunction(rtk_uint32 *pEnabled)
{
    return rtl8367c_getAsicRegBit(RTL8367C_REG_MONITOR_CTRL2, RTL8367C_RXMIRROR_ENABLED, pEnabled);
}
/* Function Name:
 *      rtl8367c_setAsicPortMirrorTxFunction
 * Description:
 *      Set Asic's port mirror Rx function switch
 * Input:
 *      enabled       - 1: Enabled, 0: Disabled
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT       - Invalid input parameters
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicPortMirrorTxFunction(rtk_uint32 enabled)
{
    return rtl8367c_setAsicRegBit(RTL8367C_REG_MONITOR_CTRL2, RTL8367C_TXMIRROR_ENABLED,