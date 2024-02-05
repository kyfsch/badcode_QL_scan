// This function is used to configure the outer and inner TPID..
rtk_api_ret_t rtk_ptp_tpid_set(rtk_ptp_tpid_t outerId, rtk_ptp_tpid_t innerId)
{
    rtk_api_ret_t retVal;

    /* Check initialization status*/
    RTK_CHK_INIT_STATUS();

    /* check the paraments */
    RTK_CHK_PARAM(outerId >= PTP_ETH_TYPE_MIN);
    if (innerId != PTP_TPID_DISABLE)
        RTK_CHK_PARAM(innerId >= PTP_ETH_TYPE_MIN);

    /* configrue outer and intr TPID */
    if (PMAC_PTP_OUTER_TPID_SET(outerId) != SUCCESS)
        return RT_ERR_FAILED;

    if (PMAC_PTP_INNER_TPID_SET(innerId) != SUCCESS)
        return RT_ERR_FAILED;

    retVal = RT_ERR_OK;

    do
    {
        if (innerId != PTP_TPID_DISABLE)
        {
            if (PMAC_PTP_INTR_INNER_TPID_VALID(TRUE) != SUCCESS)
                retVal = RT_ERR_FAILED;
        }
        else
        {
            if ((PMAC_PTP_INTR_TPID_DEC_INVALID_DIS(NULL)))
                retVal = RT_ERR_FAILED;
        }
    } while(0);

    return retVal;
}

/* Function Name:
 *      rtk_ptp_tpid_get
 * Description:
 *      get the outer and Inner TPID configuration..
 * Input:
 *      pOuterId - pointer of outer Ether TPID.
 *      pInnerId - pointer of inner TPID.
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK               - OK
 *      RT_ERR_FAILED           - Failed
 *      RT_ERR_SMI              - SMI access error
 *      RT_ERR_INPUT           - Invalid input parameters.
 * Note:
 *