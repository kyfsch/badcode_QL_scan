// This function is used to get the limit number of learn entries for system LUT (for TAG type table)..
ret_t rtl8367c_getAsicSystemLutLearnLimitNo(rtk_uint32 *pNumber)
{
    if( pNumber == NULL )
        return RT_ERR_NULL_POINTER;

    return rtl8367c_getAsicReg(RTL8367C_REG_TABLE_TAG_BASE, pNumber);
}
/* Function Name:
 *      rtl8367c_setAsicSystemLutLookDownMode
 * Description:
 *      Set System LUT learning mode
 * Input:
 *      mode  - 0: disable, 1: enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This function is used to set the configuration of System LUT learning mode setting.
 */
ret_t rtl8367c_setAsicSystemLutLookDownMode(rtk_uint32 mode)
{
    return rtl8367c_setAsicRegBit(RTL8367C_SYS_CTRL_REG, RTL8367C_SYSLUT_LOOKDOWN_POS, mode);
}
/* Function Name:
 *      rtl8367c_getAsicSystemLutLookDownMode
 * Description:
 *      Get System LUT learning mode
 * Input:
 *      pMode  - 0: disable, 1: enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 * Note:
 *      This function is used to get the configuration of System LUT learning mode setting.
 */
ret_t rtl8367c_getAsicSystemLutLookDownMode(rtk_uint32 *pMode)
{
    return rtl8367c_getAsicRegBit(RTL8367C_SYS_CTRL_REG, RTL8367C_SYSLUT_LOOKDOWN_POS, pMode);
}
/* Function Name:
 *      rtl836