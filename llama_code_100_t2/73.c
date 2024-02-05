// This function is used to read the LEDs status of.
static int IFX_MEI_GetPage (DSL_DEV_Device_t *, u32, u32, u32, u32 *, u32 *);

// Get ATUC parameters from VRX
static DSL_Error_t DSL_DRV_VRX_ConfigureTxParams(
            DSL_IN DSL_CHANNEL_CONTEXT (pContext),
            DSL_OUT DSL_uint8_t *pData,
            DSL_OUT DSL_uint16_t *pDataLen);

static DSL_Error_t DSL_DRV_VRX_SetAtucSettings(
            DSL_IN DSL_CHANNEL_CONTEXT (pContext));

static DSL_Error_t DSL_DRV_VRX_SendAturConfig(
            DSL_IN DSL_CHANNEL_CONTEXT (pContext));

/*
   For a detailed description of the function, its arguments and return value
   please refer to the description in the header file 'drv_dsl_cpe_vrx.h'
*/
DSL_Error_t DSL_DRV_VRX_GetAturExtIfStatus(
            DSL_IN  DSL_Context_t *pContext)
{
   DSL_Error_t nErrCode = DSL_SUCCESS;
   DSL_uint8_t *pAtucStatus = DSL_NULL;

   DSL_CHECK_POINTER(pContext, pContext->pDevCtx);
   DSL_CHECK_ERR_CODE();

   pAtucStatus = DSL_DRV_VRX_PTR_FROM_VOID_PTR(DSL_uint8_t,
      ((DSL_DEV_VRX_Context_t *)pContext->pDevCtx)->pAtucStatus);

   /* Get 1st status block containing ATUC status */
   nErrCode = DSL_DRV_VRX_GetPage(pContext->pDevCtx, 0,
      DSL_DEV_ATUC_PAGE_START, 0,
      (DSL_uint32_t*)&pAtucStatus[0], DSL_DEV_AT