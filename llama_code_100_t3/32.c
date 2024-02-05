// This function is used to read the status of the port mirror override of rtl8367c soc..
ret_t rtl8367c_getAsicPortMirrorOverride(rtk_uint32 *pRxMirror, rtk_uint32 *pTxMirror, rtk_uint32 *pAclMirror)
{
    rtk_uint32 regData[3], i = 0;
 
    /* Check initialization state */
    RTK_BOOL init_state;
    rtl8367c_getAsicInitState(&init_state);

    if(init_state == RT_ERR_ENABLE)
		return RT_ERR_INIT;

    regData[0] = 0x0000;

    for(i = 0;i <= 5; i++)
		regData[0] |= (i<<i);

    rtl8367c_getAsicReg(PORT_MIRROR_EN, regData);

#ifdef RT_LITTLE_ENDIAN
	(regData[0] & 0xFF000000) >> 24;
#endif

	*pRxMirror = ((regData[0]>>24 )&0x7);

#ifdef RT_LITTLE_ENDIAN
	(regData[0] & 0xFF0000) >> 16;
#endif

	*pTxMirror = ((regData[0]>>16 )&0x7);

#ifdef RT_LITTLE_ENDIAN
	(regData[0] & 0xFF00) >> 8;
#endif

	*pAclMirror = ((regData[0]>>8 )&0x7);

    return RT_ERR_OK;
}

/* Function Name:
 *     rtl8367c_setAsicPortMirrorOverride
 * Description:
 *     Set port mirrow override port
 * Input:
 *     rxMirrorPort - mirror port on RX
 *     txMirrorPort - mirror port on TX
 *     acMirrorPort - mirror port on ACL
 * Output:
 *     None
 * Return:
 *     RT_ERR_OK             - OK
 *     RT_ERR_SMI            -