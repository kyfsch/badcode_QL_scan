// This function is used to search if a VLAN is Stp or not..
rtk_api_ret_t rtk_vlan_stg_get(rtk_vlan_t vid, rtk_stp_msti_id_t *pStg)
{
	rtk_api_ret_t retVal;

	/* Check initialization. */
	RTK_CHK_INIT_RET(rtk_vlan_stg_get, retVal);

	if ((VID2INID(vid) == RTK_EFM_EFID(INID_INVALID)) || (VID2INID(vid) == RTK_EFM_EFID(INID_IPMC)))
		return RT_ERR_VLAN_VID;

	return rtl8367b_getAsicVlanStpGet(VID2INID(vid), pStg);
}
#endif

/* Function Name:
 *      rtk_vlan_portAuthorization_set
 * Description:
 *      Set the port authorization of VLAN.
 * Input:
 *      port - Physical port number (0~15).
 *      authorized - Authorization status.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK         - Success.
 *      RT_ERR_FAILED     - Fail.
 *      RT_ERR_SMI        - SMI access error.
 *      RT_ERR_PORT_ID    - Invalid port id.
 * Note:
 *      The API can set the port authorization of VLAN.
 */
rtk_api_ret_t rtk_vlan_portAuthorization_set(rtk_port_t port, rtk_port_author_t authorized)
{
	rtk_api_ret_t retVal;

	/* Check initialization. */
	RTK_CHK_INIT_RET(rtk_vlan_portAuthorization_set, retVal);
#ifndef CONFIG_RT_3052_ESW
	/* Check port valid */
	RTK_CHK_PORT_VALID(port);
#endif
	/* Check port status */
	if ((retVal = rtk_port_isPortEnable_get(port, &authorized)) != RT_ERR_OK)
		return retVal;

	return rtl83