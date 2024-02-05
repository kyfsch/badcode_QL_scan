// This function is used to read the status of the port mirror override of rtl8367c soc..
ret_t rtl8367c_getAsicPortMirrorOverride(rtk_uint32 *pRxMirror, rtk_uint32 *pTxMirror, rtk_uint32 *pAclMirror) 
{
	if(pRxMirror == NULL)
		return RT_ERR_NULL_POINTER;
	if(pTxMirror == NULL)
		return RT_ERR_NULL_POINTER;
	if(pAclMirror == NULL)
		return RT_ERR_NULL_POINTER;

	 *pRxMirror = rtl8367c_getAsicReg(RTK_REG_MIRROR_RXENABLE);

	 *pTxMirror = rtl8367c_getAsicReg(RTK_REG_MIRROR_TXENABLE);

	 *pAclMirror = rtl8367c_getAsicReg(RTK_REG_MIRROR_ACLENABLE);

    return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_setAsicPortMirrorEnable
 * Description:
 *      Set Port Mirror function
 * Input:
 *      enabled - FALSE: disable  , TRUE: enable
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK    - Success
 *      RT_ERR_SMI   - SMI access error
 *      RT_ERR_TBL_FULL - Port not existing
 * Note:
 *      None
 */
 rtk_api_ret_t rtl8367c_setAsicPortMirrorEnable(rtk_uint32 enabled)
{
    rtk_uint32 regData;

    if(enabled > RTK_ENABLE_MAX)
        return RT_ERR_ENABLE;

    if ((rtl8367c_getAsicReg(RTK_REG_MIRROR_CONFIG, &regData)) != RT_ERR_OK)
        return RT_ERR_SMI;

    regData |= (REG_MIRROR_CONFIG_TMAC_EN_MASK | REG_MIRROR_CONFIG_RMAC_EN_MA