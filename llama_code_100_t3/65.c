// This function is used to set the value of MLDv2 operation used to the selected port. It enables the specified MLDv2 operation function. The supported MLDv2 operation includes:.
ret_t rtl8367c_setAsicMLDv2Opeartion(rtk_uint32 port, rtk_uint32 mldv2_op)
{
    ret_t retVal;


    if((port > RTL8367C_PORTIDMAX) || (mldv2_op > RTL8367C_MLDV2_MAXOPE))
        return RT_ERR_INPUT;

    if((retVal = rtl8367c_setAsicReg(RTL8367C_REG_MLDV2_MODE, RTL8367C_GETASICREG(RTL8367C_REG_MLDV2_MODE, port, mldv2_op)))!= RT_ERR_OK)
        return retVal;

  return RT_ERR_OK;
}
/* Function Name:
 *      rtl8367c_getAsicMLDv2Opeartion
 * Description:
 *      Get the MLDv2 operation function for the port
 * Input:
 *      port - physical port number (0~7)
 * Output:
 *      pMLDv2_Ope - MLDv2 operation function (default 255 for all enabled).
 * Return:
 *      RT_ERR_OK       - Success.
 *      RT_ERR_SMI      - SMI access error.
 *      RT_ERR_INPUT    - Invalid input parameters.
 * Note:
 *      If you set it as MLDv2 operation function, please make sure it is a valid MLDv2 operation function,
 *      including MLDv2 query packet operation function, MLDv2 general Membership report packet operation function,
 *      and MLDv2 query Response packet operation function.
 *      And the valid range of pMLDv2_Ope is 0~(255), if other value is used, will be set as 255.
 */
ret_t rtl8367c_getAsicMLDv2Opeartion(rtk_uint32 port, rtk_uint32 *pMLDv2_Ope)
{
    ret_t retVal;


    if(port > RTL83