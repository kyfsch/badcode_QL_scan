/// This function is used to get trap action of RUNTIME, which will be used by some functions in the upper layer. For example, some applications that support trap function need to judge action of pUcast_action and then make some decision of applications.</s>.
rtk_api_ret_t rtk_trap_unknownMacPktAction_get(rtk_trap_ucast_action_t *pUcast_action)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pUcast_action)
        return RT_ERR_NULL_POINTER;

    if((retVal = rtl8367c_getAsicCtrl(ASIC_CTRL_TRAP_UNKNOWN_MAC, pUcast_action)) != RT_ERR_OK )
        return retVal;

    return RT_ERR_OK;
}

/****************************************************************
*
* ucast_action_set - set trap UCAST action
*
* PARAMETERS: - pUcast_action: trap action(ucast_action_get)
*
* RETURNS: rtk_api_ret_t
*
* NOTE: None
*
****************************************************************/
rtk_api_ret_t rtk_trap_unknownMacPktAction_set(rtk_trap_ucast_action_t ucast_action)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if((retVal = rtl8367c_setAsicCtrl(ASIC_CTRL_TRAP_UNKNOWN_MAC, ucast_action)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/****************************************************************
*
* rtk_trap_ipV4Ttl0PktAction_get - get trap IPv4 TTL=0 action
*
* PARAMETERS: - pUcast_action: trap action(ucast_action_get)
*
* RETURNS: rtk_api_ret_t
*
* NOTE: None
*
****************************************************************/
rtk_api_ret_t rtk_trap_ipV4Ttl0PktAction_get(rtk_trap_ucast_action_t