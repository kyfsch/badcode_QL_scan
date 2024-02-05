// This function is used to set trigger condition for LLPP Trap. The Trap is only triggered when all these 4 conditions happen at the same time:.
ret_t rtl8367c_setAsicRlppTrap8051(rtk_uint32 enabled)
{
    if (enabled > RTL8367C_ENABLED)
        return RT_ERR_INPUT;

    return rtl8367c_setAsicRegBit(RTL8367C_REG_RLPP_TC_ENABLE_8051, RTL8367C_REL_EN_8051_EN_OFFSET, enabled);
}
/* Function Name:
 *      r8300c_getAsicRlppTrap8051
 * Description:
 *      Get 8051 Trap status function
 * Input:
 *      pEnabled - 1:enable Rlpp trap 8051 0: disable Rlpp trap 8051
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK     - Success
 *      RT_ERR_SMI   - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_getAsicRlppTrap8051(rtk_uint32 *pEnabled)
{
    if(pEnabled == NULL)
        return RT_ERR_NULL_POINTER;

    return rtl8367c_getAsicRegBit(RTL8367C_REG_RLPP_TC_ENABLE_8051, RTL8367C_REL_EN_8051_EN_OFFSET, pEnabled);
}
/* Function Name:
 *      r8300c_setAsicRlppTrap4551
 * Description:
 *      Set 4551 Trap status function
 * Input:
 *      enabled - 1:enable Rlpp trap 4551 0: disable Rlpp trap 4551
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK      - Success
 *      RT_ERR_SMI   - SMI access error
 * Note:
 *      None
 */
ret_t rtl8367c_set