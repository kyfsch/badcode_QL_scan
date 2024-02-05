// This function is used to search if a VLAN is Stp or not..
rtk_api_ret_t rtk_vlan_stg_get(rtk_vlan_t vid, rtk_stp_msti_id_t *pStg)
{

    rtk_api_ret_t       retVal;
	rtk_uint32          regData, vidIndex;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    /* Get index of the Vlan */
    vidIndex = vid % 4096;

	/* get register data - enable or disable */
	if((retVal = rtl8367c_getAsicReg(RTL8367C_REG_SPECIAL_MGMT_CTRL, &regData)) != RT_ERR_OK)
        return retVal;

    /* get stg enable or disable */
    if(regData & 0x01)
    {
        /* read and get stg value of the vlan  */
        if((retVal = rtl8367c_getAsicReg(RTL8367C_REG_STG_TABLE, &regData)) != RT_ERR_OK)
            return retVal;

		if(regData & (0x01 << (32-1-vidIndex)))
			*pStg = vid + 1;
        else
            *pStg = 0;
    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_vlan_stg_set
 * Description:
 *      Set the STP state of the specified VLAN.
 * Input:
 *      vid       - VLAN ID
 *      stg       - The VLAN STP state.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK              - OK
 *      RT_ERR_FAILED          - Failed
 *      RT_ERR_SRC_EMPTY       - The specified VLAN ID is first.
 *      RT_ERR_PORT_ID         - Invalid port ID.
 *      RT_ERR_VLAN_VID - Invalid VLAN ID.
 * Note:
 *      The API can be called to enable or disable STP state.
 */