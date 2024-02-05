// This function is used to convert logical port to physical port. If logical port mask is valid, the corresponding physical port mask will be returned. Otherwise, the physical mask will be returned as logical mask is NULL pointer..
rtk_api_ret_t rtk_switch_portmask_P2L_get(rtk_uint32 physicalPortmask, rtk_portmask_t *pLogicalPmask)
{
    rtk_api_ret_t retVal;
	rtk_uint32 i;
	rtk_uint32 phyPortmask;
	rtk_uint32 pmaskLtoP[PORT_TOTAL_NUM];
	rtk_uint32 value;
	rtk_uint32 phyPortmap[PORT_TOTAL_NUM/32];
	
    /* Check initialization state */
    RTK_CHK_INIT_STATE();

   mtkmac_ReadPortMapTable(pmacPortmask);
   for(i=0;i<PORT_TOTAL_NUM;i++)
   {
        if(MACPHY_GET_BIT(i))
        {
            phyPortmap[i/32] |= 0x1<<(i%32);
        }
   }

    if(logicalPortmask != NULL) {
        for(i=0;i<RTK_SWITCH_PORT_MAX;i++)
        {
            *logicalPortmask &= ~(1<<i);

            //logical port 6 to 15 (PHY 6..15)
            if((i>=6)&&(i<=15))
            {
                if (phyPortmap[i>>5] & (0x1<<(i&0x1f)))
                {
                    *logicalPortmask|=1<<i;
                }
            }
            else {
                if(pmacPortmask[i>>5] & (0x1<<(i&0x1f)))
                {
                    *logicalPortmask|=1<<i;
                }
            }
        }
   }
   else
   {
        physicalPortmask=0XFFFFFFFF;
        for(i=0;i<RTK_SWITCH_PORT_MAX;i++)
        {

            //logical port 6 to 15 (PHY 6..15)
            if((i>=6)&&(i<=15))
            {
                if (phyPortmap[i