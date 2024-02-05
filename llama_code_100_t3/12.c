// This function is used to obtain the port mirror state. When calling the function, port mirroring is enabled. If it returns 1 and port mirroring is enabled means to send packets to the set port. If it returns 0 and port mirroring is.
ret_t rtl8367c_getAsicPortMirrorTxFunction(rtk_uint32* pEnabled)
{
    if (pEnabled == NULL)
        return RT_ERR_NULL_POINTER;

    return rtl8367c_getAsicRegBit(RTL8367C_REG_PORTMIRRORING_CFG, RTL8367C_TXPINGEN_OFFSET, pEnabled);
}
/*
@func ret_t | rtl8367c_setAsicPortMirrorRxFunction | This function is used to set the port mirror state. When port mirroring is enabled, enable mirror packet transmitting to the set port.
@parm pEnabled | rtk_uint32* | Mirror state, 1 enable mirroring, 0 disable mirroring.
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error.
@rvalue RT_ERR_INPUT | Invalid input parameters.
@comm
*/

ret_t rtl8367c_setAsicPortMirrorRxFunction(rtk_uint32 mirrorRxPort)
{

    return rtl8367c_setAsicRegBits(RTL8367C_REG_PORTMIRRORING_CFG, RTL8367C_RXPINGEN_MASK, mirrorRxPort);
}
/*
@func ret_t | rtl8367c_getAsicPortMirrorRxFunction | This function is used to obtain the port mirror state. When calling the function, port mirroring is enabled. If it returns 1 and port mirroring is enabled means to send packets to the set port. If it returns 0 and port mirroring is enabled.
@parm mirrorRxPort | rtk_uint32* | Mirror state , 1 enable mirroring, 0 disable mirroring.
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error.
@rvalue RT_ERR_NULL_POINTER | Invalid input "pEnabled".
@comm
*/
ret_t rtl836