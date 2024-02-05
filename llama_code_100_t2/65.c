// This function is used to set the value of MLDv2 operation used to the selected port. It enables the specified MLDv2 operation function. The supported MLDv2 operation includes:.
ret_t rtl8367c_setAsicMLDv2Opeartion(rtk_uint32 port, rtk_uint32 mldv2_op)
{
    rtk_api_ret_t retVal;
    
    /* Check argument validation */
    if(port > RTL8367C_PORTIDMAX)
        return RT_ERR_PORT_ID;
    if((mldv2_op != RTK_ENABLED) && (mldv2_op != RTK_DISABLED))
        return RT_ERR_INPUT;

    if( port >= 8 )
    {
         retVal = rtl8367c_setAsicReg(RTL8367C_REG_MAC_MANAGEMENT1, RTL8367C_MAS5DMASK, 3<<8);

         if(RT_ERR_OK != retVal )
             return retVal;

         if(mldv2_op == RTK_ENABLED)
             retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_MAC_MANAGEMENT1, 11, 1);
         else
             retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_MAC_MANAGEMENT1, 11, 0);

         if(RT_ERR_OK != retVal )
             return retVal;
    }
    else
    {
        retVal = rtl8367c_setAsicReg(RTL8367C_REG_MAC_MANAGEMENT0, RTL8367C_MAS0DMASK, 3<<RTL8367C_MAS0D_OFFSET);

        if(RT_ERR_OK != retVal )
            return retVal;

        if(mldv2_op == RTK_ENABLED)
            retVal = rtl8367c_setAsicRegBit(RTL8367C_REG_MAC_MANAGEMENT0, 9, 1);
        else
            retVal = rtl83