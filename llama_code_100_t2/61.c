// This function is used to set the LEQ-offset manually and it has a little bit trick, since you can set the LEQ-offset via bit9 and bit10 in register 0x2e by 0x02, but since it has a.
void rtl9300_sds_rxcal_leq_offset_manual(u32 sds_num, bool manual, u32 offset)
{
	//TODO
	return;
}

/*
 * set the PGA gain of the SDS input
 * @sds_num = 1/0 => right/left channel
 * @pga = 6/7/8 = 1/0.8/1.6
 */
void rtl9300_sds_rxcal_pga_set(u32 sds_num, u32 pga)
{
	pga = (pga > 8)?8:pga;
	rtl9300_write_phy_reg(1, phy_base_adress + ((sds_num)?(0x00b6):(0x00b5)), 0x00c0 | pga);

	return;
}

void rtl9300_sds_rxcal_mode(u32 sds_num, u32 mode)
{
	u32 ena_offset, ena_mask;

	ena_offset = (sds_num)?(0x00b7):(0x00b6);
	ena_mask = (sds_num)?(0x0008):(0x0004);
	//if (mode) {
	//    rtl9300_write_phy_reg(1, phy_base_adress + ena_offset, rtl9300_read_phy_reg(1, phy_base_adress + ena_offset) | ena_mask);
	//} else {
	//    rtl9300_write_phy_reg(1, phy_base_adress + ena_offset, rtl9300_read_phy_reg(1, phy_base_adress + ena_offset) & (~ena_mask));
	//}
#if 0
	#include "common.h"
	u32 reg_value;
	u32 offset=((sds_num)?(0x00b7):(0x00b6));
	if (