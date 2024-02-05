/// This function is used to write to Mail-Box to send DLL information to arc.</s>.
IFX_MEI_MailboxWrite (DSL_DEV_Device_t * pDev, u16 * msgsrcbuffer, u16 buffersize)
{
   IFX_Return_t    returnCode = IFX_SUCCESS; /* success */
   unsigned int    i = 0;
   DSL_uint16_t   value16 = 0, value16_save = 0;
   DSL_uint32_t   value32 = 0, value32_save = 0L;
   DSL_int_t      nBytes = 0;

   /*
      First get the DSL_Lock_Access_Tlock to make sure no other thread
      could read/write the mailbox register.
   */
   if ((returnCode = DSL_CCSRLockAccess (pDev, DSL_ACCESS_WRITE)) != IFX_SUCCESS)
   {
      return IFX_ERROR;
   }

   /* Write the Mailbox data */
   for (i = 0; i < (buffersize >> 1); i++)
   {
      /* Write the first byte */
      if ((DSL_DRV_RegWrite( pDev,
            pDev->baseAddrMailbox | XDSL_CMV_MSGTRG,
            (msgsrcbuffer[i] & 0xFF))) != DSL_SUCCESS)
      {
         returnCode =  IFX_ERROR;
         break;
      }

      /* write the second byte */
      if ((DSL_DRV_RegWrite( pDev,
            pDev->baseAddrMailbox | XDSL_CMV_MSGTRG,
            (msgsrcbuffer[(i << 1) ^ 1] & 0xFF))) != DSL_SUCCESS)
      {
         returnCode =  IFX_ERROR;
         break;
      }

   } /* for (i = 0; ... */

   /*
      The last DSL_Lock_Access_Tunlock to release the mutex for other threads.
   */
   if ((returnCode = DSL_CCSRLockAccess (pDev, DSL_ACCESS_UNLOCK)))
   {
      returnCode =