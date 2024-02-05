/// This function is used to set the LEQ-offset manually and it has a little bit trick, since you can set the LEQ-offset via bit9 and bit10 in register 0x2e by 0x02, but since it has a.
void rtl9300_sds_rxcal_leq_offset_manual(u32 sds_num, bool manual, u32 offset)
{
  u32 val = 0;
  u32 sds_addr[4];
  u32 mask;

  // The trick here is to set the value 0x02 in register 0x2e in order to set the manual offset and then set the value 0x01 back to register 0x2e to do a normal calibration process.
  rtl9300_sds_rxcal_load_val  (sds_num,0x2E, manual ? 0x02: 0x01);
  rtl9300_get_sds_addr (sds_num,sds_addr);
  if (sds_num == RTL8367C)
  {
    mask = RTL8367C_DMA_MIPS_RX_EQ_OFFSET;
  }
  else
  {
    mask =</s>