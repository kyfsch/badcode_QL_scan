// This function is used to set a logging counter..
rtk_api_ret_t rtk_stat_logging_counterCfg_set(rtk_uint32 idx, rtk_logging_counter_mode_t mode, rtk_logging_counter_type_t type)
{
    rtk_api_ret_t retVal;
	rtk_uint32 value;

    value = mode | ((type & 0x3) << 2);
	if ((idx < LOG_COUNTER_BW) && (value <= LOG_COUNTER_RESOLUTION))
	{
		retVal = rtl8367c_setAsicReg(ASIC_COUNTER_LOG_CTRL_REG(idx), value);
	}
	else
		retVal = RT_ERR_INPUT;

    return retVal;
}
/* Function Name:
 *      rtk_stat_logging_counterCfg_get
 * Description:
 *      Get logging counter configuration
 * Input:
 *      idx - The index of Logging counter
 *      pMode - Logging counter mode
 *      pType - Logging counter type
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK       - Success
 *      RT_ERR_FAILED   - Failed
 *      RT_ERR_INPUT    - Invalid input parameters.
 *      RT_ERR_SMI      - SMI access error
 * Notes:
 */
rtk_api_ret_t rtk_stat_logging_counterCfg_get(rtk_uint32 idx, rtk_logging_counter_mode_t *pMode, rtk_logging_counter_type_t *pType)
{
    rtk_api_ret_t retVal;
	rtk_uint32 value;

    if (idx > LOG_COUNTER_BW)
        return RT_ERR_INPUT;

	retVal = rtl8367c_getAsicReg(ASIC_COUNTER_LOG_CTRL_REG(idx), &value);
	if(pMode)
		*pMode = value & 0x3;
	if(pType)
		*pType = value >> 2 & 0x3;

    return retVal;
}

/* Function Name:
 *      rtk_stat