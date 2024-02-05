// This function is used to dump VLAN profile. The parameter index is a VLAN index. By this function, we can have a look at some information of a VLAN. However, the information are not clear enough. For example, the function can not tell us whether.
void rtl931x_vlan_profile_dump(int index)
{
	u32 vlan_profile0, vlan_profile1;
	rtl931x_clr_bits(0x0328, BIT(0));
	vlan_profile0 = rtl931x_r32(0x032C);
	vlan_profile1 = rtl931x_r32(0x0330);

	printf("VLAN[%d]:\n", index);
	printf("  VID:%d\n", rtl931x_get_field(vlan_profile0, VLAN_PROFILE0_VLAN_VID));
	printf("  PORT_VID:%d\n", rtl931x_get_field(vlan_profile0, VLAN_PROFILE0_PORT_BASED_VID));
	printf("  STAUT_EN: %d\n", rtl931x_get_field(vlan_profile0, VLAN_PROFILE0_STAT_EN));
	printf("  FORWARD_EN: %d\n", rtl931x_get_field(vlan_profile0, VLAN_PROFILE0_FORWARD_EN));
	printf("  STP_STATE: %d\n", rtl931x_get_field(vlan_profile1, VLAN_PROFILE1_STP_STATE));
	printf("  PORT_PRIORITY: %d\n", rtl931x_get_field(vlan_profile1, VLAN_PROFILE1_PORT_PRIORITY));
	printf("  VLAN_TYPE: %d\n", rtl931x_get_field(vlan_profile1, VLAN_PROFILE1_VLAN_TYPE));
	printf("  UNKNOWN_MC_EN: %d\n", rtl931x_get_field(vlan_profile1, VLAN_PROFILE1_UNKN_MC_EN));
	printf("  MC_FWD_ALL: %