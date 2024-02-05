/// This function is used to write to Mail-Box to send DLL information to arc.</s>.
IFX_MEI_MailboxWrite (DSL_DEV_Device_t * pDev, u16 * msgsrcbuffer, u32 *pWrite)
{
   DSL_ERROR_CHECK (pDev->pCtrlStructure->nMailboxWriteIndex ==
                                       (pDev->pCtrlStructure->nCurrentMailboxMessage + 2));
   pWrite[0] = msgsrcbuffer[0];
   pWrite[1] = msgsrcbuffer[1];
   DSL_DEBUG(DSL_DBG_WRN,"MEI Message[0], Length : %d - %d","",msgsrcbuffer[0]);
   DSL_DEBUG(DSL_DBG_WRN,"MEI Message[1], Value : %08lX - %08lX","",msgsrcbuffer[1]);
   DSL_DEBUG(DSL_DBG_WRN,"MEI Message[2], Value : %08lX - %08lX","",msgsrcbuffer[2]);
   DSL_DEBUG(DSL_DBG_WRN,"MEI Message[3], Value : %08lX - %08lX","",msgsrcbuffer[3]);
   if (MEI_DRV_DMA_Access (pDev, REG_OAM_FW_MAILBOX_INDEX_0,
                           reinterpret_cast < u8 * > (&msgsrcbuffer[0]),
                           sizeof(msgsrcbuffer), 0) != MESA_RC_OK)
   {
      DSL_ERROR_MSG("MEI_DRV_DMA_Access has failed!");
      return DSL_ERR_MAILBOX_ACCESS;
   }
   pDev->pCtrlStructure->nCurrentMailboxMessage = pDev->pCtrlStructure->nMailboxWriteIndex++;

   pWrite[0] = msgsrcbuffer[2];
   pWrite[1] = msgsrcbuffer[3];
   DSL_DEBUG(DSL_DBG_WRN,"MEI Message[4], Value : %08lX - %08lX","",msgsrcbuffer[2]);
   DSL_DEBUG(DSL_DBG_WRN