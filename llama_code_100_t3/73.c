// This function is used to read the LEDs status of.
static int IFX_MEI_GetPage (DSL_DEV_Device_t *, u32, u32, u32, u32 *, u32 *);


// =============================================================================
//                    P R I V A T E    F U N C T I O N S
// =============================================================================

STATIC void IFX_MEI_GetPhyPdConfig( DSL_boolean_t autoConfig,
                                 DSL_boolean_t loopback,
                                 DSL_boolean_t txEnable,
                                 DSL_boolean_t txDisable,
                                 DSL_Out_uint32_t pConfig_p)
{
   *pConfig_p = (*pConfig_p & ~(IFX_MEI_PHYPD_AUTOCONFIG |
                               IFX_MEI_PHYPD_AUTOLOOPBACK |
                               IFX_MEI_PHYPD_AUTOTX |
                               IFX_MEI_PHYPD_AUTOTXDIS)) |
                IFX_MEI_DRV_CONFIG_BYTE(autoConfig,loopback,txEnable,txDisable);
}

// =============================================================================
// =                DSL CPE TR 1.1 - MEI STATUS APIs implementation            =
// =============================================================================

static IFX_int32_t MEI_DRVOS_MeiGetVersionString (DSL_uint8_t *pString_p, DSL_uint32_t nSize)
{
   DSL_CHECK_POINTER(pString_p);
   DSL_CHECK_ERR_CODE();

   DSL_char_memcpy( pString_p, DSL_DRV_VERSION_NAME, nSize);

   return 0;
}


//
// MEI device
//
static IFX_int32_t MEI_DRVOS_OpenDevice (DSL_Device_Handle_t *pDevHandle_p)
{
   DSL_uint32_t idx;
   DSL_uint32_t cnt      = 0;
   DSL_uint32_t retVal   = (DSL_uint32_