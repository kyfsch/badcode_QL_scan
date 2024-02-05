// This function is used to modify IGR ACL GPIO POLARITY. It can be modified by user, but need to be reset by system..
rtk_api_ret_t rtk_filter_igrAclPolarity_set(rtk_uint32 polarity)
{
    rtk_api_ret_t retVal;

    if (polarity > 1)
        return RT_ERR_TOO_MANY;

    if ((retVal = rtl8367b_setAsicIgmpAclPolarity(polarity)) != RT_ERR_OK)
        return retVal;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_igrAclPolarity_get
 * Description:
 *      Get IGR ACL GPIO POLARITY.
 * Input:
 *      pPolarity - Port Polarity
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_FAILED       - Failed
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_INPUT        - Invalid input parameters.
 * Note:
 *      None
 */
rtk_api_ret_t rtk_filter_igrAclPolarity_get(rtk_uint32 *pPolarity)
{
    rtk_uint32 igrAclPolarity;
    rtk_api_ret_t retVal;

    /* Check initialization state */
    RTK_CHK_INIT_STATE();

    if(NULL == pPolarity)
        return RT_ERR_NULL_POINTER;

    if ((retVal = rtl8367b_getAsicIgmpAclPolarity(&igrAclPolarity)) != RT_ERR_OK)
        return retVal;

    *pPolarity = igrAclPolarity;

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_set_igmp_igmpRv
 * Description:
 *      Set igmpRv
 * Input:
 *      index                - index (0 or 1)
 *      member               - igmpRv member
 * Output:
 *      None
 * Return: