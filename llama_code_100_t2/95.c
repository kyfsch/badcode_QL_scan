// This function is used to configure the outer and inner TPID..
rtk_api_ret_t rtk_ptp_tpid_set(rtk_ptp_tpid_t outerId, rtk_ptp_tpid_t innerId)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check PTP support and PTP enabled. */
    if ((retVal = rtk_switch_ptp_check())!= RT_ERR_OK)
        return retVal;

    if (pPtp->ts_ctrl.en == 0)
        return RT_ERR_ENABLE;


    if (innerId >= RTL8367B_PTIME_MAXPORT)
        return RT_ERR_INPUT;
    if (outerId >= RTL8367B_PTIME_MAXPORT)
        return RT_ERR_INPUT;

    if ((retVal = rtl8367b_setAsicVlanTpid(innerId, outerId))!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_ptp_feature_get
 * Description:
 *      Get PTP Feature status.
 * Input:
 *      pStatus -  The status of PTP feature.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_PORT_ID      - Error Untag Port-ID input parameter.
 *      RT_ERR_FAILED       - Failed
 * Note:
 */
rtk_api_ret_t rtk_ptp_feature_get(rtk_enable_t *pStatus)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Check Port-ID Value */
    if ((retVal = rtk_switch_ptp_check()) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtl8367b_getAsicPtpEnable(pStatus)) != RT_ERR_OK)
        return retVal;

    return R