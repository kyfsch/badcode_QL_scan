// This function is used to set the mode of VLAN OAM packet to be processed by the OAM forwarder. The valid mode is CPUFWD, CPUFWD2, CPUFWD3, PARFWDCPU, DSPFWDCPU..
ret_t rtl8367c_setAsicOamParser(rtk_uint32 port, rtk_uint32 parser)
{
	return(rtk_switch_setAsicOamParser(port, parser));
}
/* Function Name:
 *	rtl8367c_getAsicVlanOamAction
 * Description:
 *	Get VLAN OAM action when receiving OAM packet.
 * Input:
 *	port	- Physical port number (0~7)
 *	action	- Action of VLAN OAM
 * Output:
 *	None
 * Return:
 *	Success:	RT_ERR_OK
 *	Failure:	-RT_ERR_PORT_ID - The port id is error.
 *				-RT_ERR_INPUT - Invalid input parameters.
 * Note:
 *	None
 */
ret_t rtl8367c_getAsicVlanOamAction(rtk_uint32 port, rtk_uint32 *action)
{
	return(rtk_switch_getAsicVlanOamAction(port, action));
}
/* Function Name:
 *	rtl8367c_setAsicVlanOamAction
 * Description:
 *	Set VLAN OAM action when receiving OAM packet.
 * Input:
 *	port	- Physical port number (0~7)
 *	action	- Action of VLAN OAM
 * Output:
 *	None
 * Return:
 *	Success:	RT_ERR_OK
 *	Failure:	-RT_ERR_PORT_ID - The port id is error.
 *				-RT_ERR_INPUT - Invalid input parameters.
 * Note:
 *	None
 */
ret_t rtl8367c_setAsicVlanOamAction(rtk_uint32 port, rtk_uint32 action)
{
	return(rtk_switch_setAsicVlanOamAction(port, action));
}
/* Function Name:
 *	rtl8367c_getAsicVlanOamPri
 * Description:
 *	Get VLAN OAM priority when receiving OAM packet.
 * Input:
 *	port