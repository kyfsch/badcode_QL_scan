// This function is used to get the DSCP Remark enable status of whole system, where the port value is RTK_WHOLE_SYSTEM..
rtk_api_ret_t rtk_qos_dscpRemarkEnable_get(rtk_port_t port, rtk_enable_t *pEnable)
{
    if(port >= RTK_MAX_PORT_ID) return RT_ERR_PORT_ID;

    return rtl8367c_getDsCpRemark(port,pEnable);
}

/* Function Name:
 *      rtk_qos_dscpRemark_set
 * Description:
 *      Set DSCP remark function of specified ports.
 * Input:
 *      port - Port id.
 *      pRemark_conf - DSCP remark configuration.
 * Output:
 *      None.
 * Return:
 *      RT_ERR_OK                  - OK
 *      RT_ERR_SMI                 - SMI access error
 *      RT_ERR_QOS_INVALID_ACTION - Invalid Action
 *      RT_ERR_PORT_ID            - Invalid port id.
 *      RT_ERR_QOS_REMARK_FAILED  - Failed to set DSCP remark configuraion.
 * Note:
 *      None
 */
rtk_api_ret_t rtk_qos_dscpRemark_set(rtk_port_t port, rtk_qos_dscpRemarkConf_t *pRemark_conf)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /*
     * Only check DST field on WHOLE_SYSTEM,
     * otherwise, should check src_priority, dst_priority, drop_priority
     */
    if(port == RTK_WHOLE_SYSTEM)
    {
        if(pRemark_conf->action >= DSCP_REMARK_MAX_ACTION)
            return RT_ERR_QOS_INVALID_ACTION;
    }
    else
    {
        if((pRemark_conf->src_priority >= DSCP_PRIO_MAX_VALUE) ||
            (pRemark_conf->dst_priority >= DSCP_PRIO_MAX_VALUE) ||
            (