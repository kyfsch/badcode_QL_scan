// This function is used to set the tx link (DSL) and rx link (ATM) rates..
static ssize_t IFX_MEI_Write (DSL_DRV_file_t *, const char *, size_t, loff_t *);

DSL_Error_t
IFX_vx274_FW_ControlSend(
   DSL_Context_t *pContext,
   DSL_uint32_t bDeviceStatus,
   DSL_uint8_t *pData,
   DSL_uint32_t nSize)
{

   DSL_Error_t nErrCode = DSL_SUCCESS;
   MEI_DEV_T *MEI_pMeiDev = (MEI_DEV_T *)(pContext->pDynamicDev);

   /* PRQA S 3377 1 */
   /* check for correct device control */
   if (bDeviceStatus == 1)
   {
      DSL_CTX_READ_SCALAR(pContext, nErrCode, *pData);
      MEI_pMeiDev->devCtl.nMeiCntlState = *pData;

      if (!MEI_pMeiDev->bDeviceReady)
      {
         CMD_ResetDevice_s cmd;

         DSL_DEBUG(DSL_DBG_WRN,
            (pContext, SYS_DBG_WRN"[ifX_01_PollFW] device reset requested ...\n"));

         DSL_CTX_READ_SCALAR(pContext, nErrCode, nResetTimeout);

         /* perform RESET procedure */
         cmd.Length = CMD_RESET_DEVICE_LEN;
         memset(cmd.DeviceType, 0, 3);/* to identify device */
         cmd.DeviceType[0] = MEI_DEV_IDENTITY;
         cmd.ResetTimeout = nResetTimeout;

         /* call the internal reset function */
         nErrCode = MEI_VrxDevReset(pContext);

         /* Reset all device parameters */
         if (nErrCode == DSL_SUCCESS)
         {
            DSL_CTX_READ(pContext, nErrCode, LineState, nLsState);
            CMD_ResetDeviceConfirm_sA