// This function is used to assign the LED_SERIAL output channel to the specified portmask..
rtk_api_ret_t rtk_led_serialModePortmask_get(rtk_led_serialOutput_t *pOutput, rtk_portmask_t *pPortmask)
{
    rtk_api_ret_t retVal;
    rtk_uint32 portmask = 0;
    rtk_uint32 phy_port_idx = 0;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if (phy_port_idx >= RTL8370_CMDRPT_MAX_PORT)
        return RT_ERR_PORT_ID;

    /* Get LED_SERIAL output portmask */
    if ((retVal = rtk_led_serialMode_isPortmaskEnable_get(pOutput, phy_port_idx)) != RT_ERR_OK)
        return retVal;

    if ((retVal = rtk_switch_portmask_P2P_set(phy_port_idx, RTK_CMD_P2P_ETH, &portmask)) != RT_ERR_OK)
        return retVal;

    *pPortmask = portmask;

    return RT_ERR_OK;
}
#endif

/* Function Name:
 *      rtk_led_serialMode_isPortmaskEnable_set
 * Description:
 *      Set per portmask LED_SERIAL output enable.
 * Input:
 *      pType        - LED_SERIAL type
 *      portmask     - Portmask to be enabled/disabled.
 *      enable       - enable status
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK                              - Success
 *      RT_ERR_FAILED                          - Failed
 *      RT_ERR_INPUT                           - Invalid input parameters.
 *      RT_ERR_NOT_INIT                        - The API is not initialized by rtk_init().
 *      RT_ERR_PORT_ID                         - Invalid port number.
 *      RT_ERR_TBL_FULL                        - No free table entry.
 *      RT_ERR_PMD_INVALID_PORTMASK_STATE      - Passed-in invalid portmask state.
 * Note:
 *      The API can be used to disable/enable