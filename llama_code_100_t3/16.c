// This function is used to set trigger condition for LLPP Trap. The Trap is only triggered when all these 4 conditions happen at the same time:.
ret_t rtl8367c_setAsicRlppTrap8051(rtk_uint32 enabled)
{

	if ((enabled & 0x8000) == 0x8000)
	{
		if (enabled & 0x7fff)
			return RT_ERR_INPUT;
		else
			return rtl8367c_setAsicRegBit(RTL8367C_RLPP_TRAP_CTRL_REG, RTL8367C_RLPP_TRAP_ENABLE_POS, 1);
	}

	if (enabled > 0x8000)
		return RT_ERR_INPUT;
	else
		return rtl8367c_setAsicRegBit(RTL8367C_RLPP_TRAP_CTRL_REG, RTL8367C_RLPP_TRAP_ENABLE_POS, 0);
}
/* Function Name:
 *      rtl8367c_getAsicRlppTrap8051
 * Description:
 *      Get RLB Trigger Condition for 8051 Cause
 * Input:
 *      enabled - 0: Trigger Condition is disable, 0x8001~0x8007: Trigger Condition is different for each bit in bit15~bit8
 * Output:
 *      pEnabled - 0: Trigger Condition is disable, 0x8001~0x8007: Trigger Condition is different for each bit in bit15~bit8
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      This function is used to get trigger condition for LLPP Trap. The Trap is only triggered when all these 5 conditions happen at the same time:.
 *      Trap8 8051 Trigger Condition (RLPP_TRAP_CTRL_REG[3:0]) = Trap_En + Ethernet_Type + Length_