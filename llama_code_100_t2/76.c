// This function is used to get the ability status of a single port..
rtk_api_ret_t rtk_port_macStatus_get(rtk_port_t port, rtk_port_mac_ability_t *pPortstatus)
{
    rtk_api_ret_t retVal;
    rtk_uint32 portidx;
    rtk_uint32 portPhyIdx;
    rtk_uint32 pg, macEn, macType, speed;

    /* Check initialization status */
    RTK_CHK_INIT_STATE();

    if(port >= RTL8367B_PORTNO)
        return RT_ERR_PORT_ID;

    if (NULL == pPortstatus)
        return RT_ERR_INPUT;


    portidx = rtl8367b_port_Linux_to_PHY( port );

    if(portidx > RTL8367B_PORTIDMAX)
        return RT_ERR_PORT_ID;

    rtl8367b_setAsicPhyReg(portidx, PHY_MAC_CONTROL_1,0x8000); /*disable autoneg*/

    /*Read the current status to get type*/
    rtl8367b_getAsicPhyReg(portidx,PHY_MAC_CONTROL_2,&speed);

    if(speed&PHY_CAP_10HALF)
        macType = 0x2;
    else if(speed&PHY_CAP_10FULL)
        macType = 0x1;
    else if(speed&PHY_CAP_100HALF)
        macType = 0x4;
    else
        macType = 0x8;

    rtl8367b_setAsicPhyReg(portidx, PHY_MAC_CONTROL_1, macType);

    /*read back to get full duplex status*/
    rtl8367b_getAsicPhyReg(portidx,PHY_MAC_CONTROL_1,&macType);

    if(macType&(0x4))
    {
        speed = 100;
        speed |= (