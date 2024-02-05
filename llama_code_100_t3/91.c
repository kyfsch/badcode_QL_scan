// This function is used to get the DSCP Remark enable status of whole system, where the port value is RTK_WHOLE_SYSTEM..
rtk_api_ret_t rtk_qos_dscpRemarkEnable_get(rtk_port_t port, rtk_enable_t *pEnable)
{
    rtk_api_ret_t retVal;
    rtk_uint32 regData;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (port >= RTK_MAX_NUM_OF_PORT)
        return RT_ERR_INPUT;

    if (pEnable == NULL)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367c_getAsicReg(DSCP_REMARK_CTRL_REG, &regData)) != RT_ERR_OK)
        return retVal;

    if (port == RTK_WHOLE_SYSTEM)
        *pEnable = (regData&0x1)? ENABLED : DISABLED;
    else
    {
        retVal = rtk_switch_portBitGet(port, &regData);
        if (retVal != RT_ERR_OK)
            return retVal;

        if( regData & (1<<8) )
        {
            *pEnable = ENABLED;
        }
        else
            *pEnable = DISABLED;
    }

    return RT_ERR_OK;
}


/* Function Name:
 *      rtk_qos_dscpRemarkEnCode_set
 * Description:
 *      Set the remark DSCP code.
 * Input:
 *      enCode - Remark code for DSCP
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_BUSY         - Busy
 *      RT_ERR_FAILED       - Configure failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - Null pointer
 * Note:
 *      None
 */
rtk_api_ret_t rtk_qos_dscpRemarkEnCode_set(rtk_qos_remarkCode_t enCode)
{
    rtk_api_