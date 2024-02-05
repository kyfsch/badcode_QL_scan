// This function is used to set Storm filter bypass enable for the specified Storm Bypass type.
rtk_api_ret_t rtk_storm_bypass_set(rtk_storm_bypass_t type, rtk_enable_t enable)
{
    rtk_api_ret_t retVal;

    // input validation
    if ((type > END_STORM_BYPASS) && (-1 != enable))
        return RT_ERR_INPUT;

    if (-1 == enable)
        enable = ENABLED;

    //check storm type range
    if(type >= END_STORM_BYPASS)
    {
        return RT_ERR_INPUT;
    }

    rtl8367s_setAsicStormFilterBypass(type, enable);
    return RT_ERR_OK;
};

/* Function Name:
 *      rtk_storm_bypass_get
 * Description:
 *      Get Storm filter bypass enable status of the specified Storm Bypass type.
 * Input:
 *      type        - Storm bypass port (see rtk_storm_bypass_t)
 * Output:
 *      pEnable     - Storm filter bypass enable
 * Return:
 *      RT_ERR_OK   - OK
 *      RT_ERR_FAILED - Failed
 *      RT_ERR_SMI   - SMI access error
 * Note:
 */
rtk_api_ret_t rtk_storm_bypass_get(rtk_storm_bypass_t type, rtk_enable_t *pEnable)
{
    rtk_api_ret_t retVal;

    // input validation
    if ((type > END_STORM_BYPASS) || (NULL == pEnable))
        return RT_ERR_INPUT;

    //check storm type range
    if(type >= END_STORM_BYPASS)
    {
        return RT_ERR_INPUT;
    }

    retVal = rtl8367s_getAsicStormFilterBypass(type, pEnable);

    if( retVal != RT_ERR_OK )
    {
        return retVal;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_