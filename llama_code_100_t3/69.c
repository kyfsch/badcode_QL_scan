// This function is used to set Storm filter bypass enable for the specified Storm Bypass type.
rtk_api_ret_t rtk_storm_bypass_set(rtk_storm_bypass_t type, rtk_enable_t enable)
{
    rtk_api_ret_t retVal;

    // Check initialization state
    RTK_CHK_INIT_STATE();

    if(type>=MAX_BYPASS)
    {
        return RT_ERR_INPUT;
    }

    if(rtk_switch_getEnable_IPv6PimSpt_Protocol() == DISABLED && type == BYPASS_FRAME_IPV6_PIMSPT)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_PortBasedVlanTranslation_Protocol() == DISABLED && type == BYPASS_PORT_BASE_VLAN)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_PortBasedExtendedVlanTranslation_Protocol() == DISABLED && type == BYPASS_PORT_BASE_EXT_VLAN)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_Ipv6_Protocol() == DISABLED && type == BYPASS_FRAME_IPV4_OSPFv6)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_Ipv6_Protocol() == DISABLED && type == BYPASS_IPv6_MPLS)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_Ethernet_Protocol() == DISABLED && type == BYPASS_FRAME_LLC_SNAP)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_IP_PPPoE_Protocol() == DISABLED && type == BYPASS_FRAME_PPPOE_IPV6)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_IP_OAM_Protocol() == DISABLED && type == BYPASS_FRAME_IPV4_OAM)
        return RT_ERR_INPUT;

    if(rtk_switch_getEnable_F