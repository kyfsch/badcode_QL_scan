/// This function is used to get trap action of RUNTIME, which will be used by some functions in the upper layer. For example, some applications that support trap function need to judge action of pUcast_action and then make some decision of applications.</s>.
rtk_api_ret_t rtk_trap_unknownMacPktAction_get(rtk_trap_ucast_action_t *pUcast_action)
{
    rtk_api_ret_t retVal;
    rtl8367c_trapunknownmac_u_actionType uActionType = rtl8367c_trapunknownmac_u_forwarding;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(pUcast_action != NULL)
        retVal = rtl8367c_getAsicTrappingAction_unknown_unicaster(pUcast_action, &uActionType);
    else
        retVal = RT_ERR_INPUT;

    return retVal;
}

/* Function Name:
 *      rtk_trap_reserved_protocol_cmd_set
 * Description:
 *      Set trap action of Reserved protocol packet
 * Input:
 *      action - Trap action
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_TBL_FULL     - Configuration is full
 *      RT_ERR_INPUT        - Invalid input parameter.
 * Note:
 *      if enable protocol checking, the packet will be dropped,
 *      and the trap code will be set to 0x21
 */
rtk_api_ret_t rtk_trap_reserved_protocol_cmd_set(rtk_trap_action_t action)
{
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(action >= RTK_TRAP_ACTION_MAX)
        return RT_ERR_INPUT;

    retVal = rtl8367c_setAsicReservedProtocolTrapingEnable(action);

    return retVal;
}

/* Function Name:
 *      rtk_trap_reserved_protocol_cmd_get
 * Description:
 *      Get trap action of Reserved protocol packet