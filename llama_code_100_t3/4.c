// This function is used to modify IGR ACL GPIO POLARITY. It can be modified by user, but need to be reset by system..
rtk_api_ret_t rtk_filter_igrAclPolarity_set(rtk_uint32 polarity) 
{
	rtk_filter_igrAclPolarity_s pigInfo;
	rtk_api_ret_t retVal;
	uint32_t u32Tmp;

	if(pigInfo.polarity != polarity)
	{
		retVal = rtk_filter_igrAclPolarity_get(&pigInfo);
		if(RTK_ERR_OK != retVal) return retVal;
	
		// Check input validity.
		u32Tmp = polarity;
		if (u32Tmp == 0xFFFFFFFF)
		{
			rtk_trace(RTK_TRACE_ERR, ("%s: Invalid polarity.\n",__FUNCTION__));
			return RT_ERR_INPUT;
		}
	
		reg_pAdvAclPolarity = polarity;

		rtk_filter_igrAclPolarity_set(&pigInfo);
	}
	return RTK_ERR_OK;
}
/* Function Name:
 *      rtk_filter_igrAclSrcPort_set
 * Description:
 *      Configure the src port of MAC IPG to be the source port for IPG filtering
 * Input:
 *      srcport - Source Port 1-7 for IPG filtering
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 **/
rtk_api_ret_t rtk_filter_igrAclSrcPort_set(rtk_mac_port_t srcport)
{
    rtk_filter_igrAclSrcPortSelect_s pigSrcPortInfo;
    rtk_api_ret_t retVal;
    uint32_t u32Tmp;

    if(srcport != (srcport & 0x07))
    {
        return RT_ERR_MAC_PORT;
    }
				
    retVal = rtk_filter_igrAclSrcPortSelect_get(&