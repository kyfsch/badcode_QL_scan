// This function is used to convert logical port to physical port. If logical port mask is valid, the corresponding physical port mask will be returned. Otherwise, the physical mask will be returned as logical mask is NULL pointer..
rtk_api_ret_t rtk_switch_portmask_P2L_get(rtk_uint32 physicalPortmask, rtk_portmask_t *pLogicalPmask)
{

    char phyPortmask[64];
    char *tmp;

    /* Check validation of argument */
    RTK_CHK_PORT_VALID(physicalPortmask);

    if (pLogicalPmask)
    {
        rtk_lports_mask_P2L_get(physicalPortmask, pLogicalPmask);
        /* coverity[resource_leak] */
        tmp = strtok(phyPortmask, " ");
        if (tmp == NULL)
            return RT_ERR_NULL_POINTER;

    }

    return RT_ERR_OK;
}

/* Function Name:
 *      rtk_switch_portmask_L2P_get
 * Description:
 *      This function is used to convert logical port to physical port. If logical port mask is valid, the corresponding physical port mask will be returned. Otherwise, the physical mask will be returned as logical mask is NULL pointer..
 * Input:
 *      logicalPortmask      - logical mask
 *      pPhysicalPmask       - physical mask
 * Output:
 *      None
 * Return:
 *      RT_ERR_OK           - OK
 *      RT_ERR_SMI          - SMI access error
 *      RT_ERR_NULL_POINTER - NULL point
 *      RT_ERR_INPUT       - Invalid input parameter.
 * Note:
 *      None.
 */
rtk_api_ret_t rtk_switch_portmask_L2P_get(rtk_portmask_t logicalPortmask, rtk_uint32 *pPhysicalmask)
{

    char logPortmask[64];
    char *tmp;

    /* Check validation of argument */
    RTK_CHK_PORTMASK_VALID(logicalPortmask);

    if (pPhysicalmask)
    {
        if ((logicalPortmask.bits[1] == 0) && (logicalPortmask.bits[2] == 0))
        {
            *pPhysicalmask = logicalPortmask.bits[0];
            return RT_ERR_OK