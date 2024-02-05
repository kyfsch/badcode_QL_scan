// This function is used to get the limit number of learn entries for system LUT (for TAG type table)..
ret_t rtl8367c_getAsicSystemLutLearnLimitNo(rtk_uint32 *pNumber)
{
	rtk_uint32 retVal;
	rtk_uint32 regData;

	if(pNumber == NULL)
		return RT_ERR_NULL_POINTER;

	if((retVal = rtl8367c_getAsicReg(RTL8367C_CAPASITY_CONTROL_REG, &regData))!=RT_ERR_OK)
		return retVal;

	*pNumber = regData&RTL8367C_LUT_LEARN_NO_MASK;

	return RT_ERR_OK;
}

/* Function Name:
 *      rtl8367c_setAsicSystemLutLearnEnable
 * Description:
 *      Set system LUT enable or not, and also assign the learning limit number.
 * Input:
 *      bLearnEnable - Whether learn the system LUT
 *      learnLimit - The maximum number of entries to learn
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - Success
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_FAILED       - Failed
 * Note:
 *      None
 */
ret_t rtl8367c_setAsicSystemLutLearnEnable(rtk_uint32 bLearnEnable, rtk_uint32 learnLimit)
{
	rtk_uint32 entry;
	rtk_uint32 data;
	rtl8367c_lut_learn_cfg_t pLutLearnCfg;
	rtk_uint32 enable;

	/* Invalid input parameters */
	if(learnLimit > RTL8367C_LUT_LEARN_NO_MAX)
		return RT_ERR_OUT_OF_RANGE;

	entry = RTL8367C_CAPASITY_CONTROL_REG;
	enable = bLearnEnable;
	learnLimit &= RTL8367C_LUT_LEARN_