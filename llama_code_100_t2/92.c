// This function is used to set the tx link (DSL) and rx link (ATM) rates..
static ssize_t IFX_MEI_Write (DSL_DRV_file_t *, const char *, size_t, loff_t *);

/**
   This function is used to get the tx link (DSL) and rx link (ATM) rates..
 */
static ssize_t IFX_MEI_Read (DSL_DRV_file_t *, char *, size_t, loff_t*);

/***********************************************************************/

static const char *const MEI_mode_name[] =
{
    "UNDEFINED",
    "DTE",
    "DCE",
    "DTE_ON_DCE"
};

/********** MEI_DRV_data structure *************************************/
/**
   The MEI_DRV_data data structure is used to provide all info which has changed
   during the current transaction.
 */
typedef struct
{
    /** Current mode of operation. */
    DSL_MEI_operationMode_t operationMode;

    /** Current mode of operation. */
    DSL_MEI_InitMode_t initMode;

    /** Max num. of messages to be returned during the current transaction. */
    DSL_uint8_t maxReturnMessages;

    /** DSL_TRUE = no ME-EOC */
    DSL_boolean_t bNoMeEoc;

    /** DSL_TRUE = no ME-NAK */
    DSL_boolean_t bNoMeNak;

    DSL_uint8_t nRxMsgBufferSize;
    DSL_uint8_t nTxMsgBufferSize;

    /** DSL_TRUE = don't write FW message */
    DSL_boolean_t bFwNoDump;

    /** Counter to return only X ME-OK messages */
    DSL_uint32_t nMsgCnt;

    /** DSL_TRUE = return X data bytes (msgLen) */
    DSL_boolean_t  bRetDataBytes;

    /** Current message buffer pointer */
    DSL_uint8_t *pMsg;

    /** Current message length */
    DSL_uint32_t msgLength;

    DSL_Me