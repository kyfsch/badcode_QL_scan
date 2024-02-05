// This function is used to get the ability status of a single port..
rtk_api_ret_t rtk_port_macStatus_get(rtk_port_t port, rtk_port_mac_ability_t *pPortstatus)
{
	rtk_api_ret_t retVal;
	rtk_uint32 port_ability;
	char cmd[32];

	/* Check initialization state */
	if(rtk_switch_isNotInit())
		return RT_ERR_NOT_INIT;

    if((port >= RTL8367C_PORTNO))
        return RT_ERR_PORT_ID;

	memset(cmd, 0x00, sizeof(cmd));
	snprintf(cmd, 32, "macport=%d", port);
    if ((retVal = rtk_i2c_read(cmd, &port_ability))!=RT_ERR_OK)
        return retVal;

    pPortstatus->macStatus_1G = (port_ability & 0x1) ? RTK_ENABLED : RTK_DISABLED;
    pPortstatus->macStatus_10M = (port_ability & 0x2) ? RTK_ENABLED : RTK_DISABLED;

    return RT_ERR_OK;
}

/* Function Name:
 *		rtk_port_macStatus_set
 * Description:
 *		Set Port ability
 * Input:
 *		rtk_port_t port	- Physical port number (0-7).
 *		rtk_port_mac_ability_t *pPortstatus
 * Output:
 *		None
 * Return:
 *		RT_ERR_OK		-	Success
 *		RT_ERR_SMI		-	SMI access error
 *		RT_ERR_PORT_ID	-	Invalid port number.
 * Note:
 *		None
 */
rtk_api_ret_t rtk_port_macStatus_set(rtk_port_t port, rtk_port_mac_ability_t *pPortstatus)
{
	rtk_api_ret_t retVal;
	rtk_uint32 port_ability;
	char cmd[32];

	/* Check initialization state */