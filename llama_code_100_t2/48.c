// This function is used to set a logging counter..
rtk_api_ret_t rtk_stat_logging_counterCfg_set(rtk_uint32 idx, rtk_logging_counter_mode_t mode, rtk_logging_counter_type_t type)
{
    rtk_api_ret_t retVal;
    rtl8367c_stm_counterIdx_t     rtl8367Idx;
    rtl8367c_stm_counterMode_t    rtl8367Mode;
    rtl8367c_stm_counterType_t    rtl8367Type;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    rtl8367Idx = idx;
    rtl8367Mode = mode;
    rtl8367Type = type;

    if((rtl8367Idx > RTL8367C_STM_COUNTERIDX_MAX) || (rtl8367Mode >= RTL8367C_STM_COUNTERMODEMAX))
        return RT_ERR_OUT_OF_RANGE;

    retVal = rtl8367c_setAsicStmCounterOperMode((rtl8367c_stm_counterIdx_t)idx, (rtl8367c_stm_counterMode_t)mode, (rtl8367c_stm_counterType_t)type);
    if(retVal!=RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_stat_logging_counterCfg_get
 * Description:
 *      Get the configuration of logging counters.
 * Input:
 *      idx - Index
 *      pMode - Action on packet.
 *      pType - Action on byte.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 *      RT_ERR_OS_ID        - Invalid ID in mask.
 * Note: