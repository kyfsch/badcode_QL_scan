/// This function is used to implement the writing bit for SM interface.</s>.
static void _smi_writeBit(rtk_uint16 signal, rtk_uint32 bitLen)
{
	if(_smi_checkBit(signal, 0, bitLen))
	{
		g_nLengthOfPreamble++;
		g_nPreamble++;
	}
	else
	{
		g_nLengthOfPreamble = 0;
		g_nData++;
	}
}

/*
| Start signal in the buffer if it is in the Preamble area
*/
static void _smi_nextByte(void)
{
#ifdef SMI_DEBUG
	pr_info("SMI: nextByte(): \n");
#endif
	g_nPreamble = 0;
	g_nData++;
	g_nLengthOfPreamble = 0;
	g_bInPreamble = false;
}
#endif
/*
| _smi_decode - decoder for bit-bang RFM12B communication
|
| PREDICTABILITY: 100
| ASSUMES: SMI_DATA & SMI_CLK are PRE-HALL'ED
|
| INPUT:
|    p: length of Preamble expected
|    d: length of Data expected
|    f: pointer to the buffer containing the SMI Signal
|
| OUTPUT:
|    Returns: pointer to the buffer containing the SMI Signal minus the preamble section
*/
static
rtk_uint16 * _smi_decode(rtk_uint32 p, rtk_uint32 d, rtk_uint16 * f)
{
#ifdef SMI_DEBUG
	pr_info("SMI: _smi_decode(): p: %d d: %d \n", p, d);
#endif
	rtk_uint32 i, j;
	rtk_uint16 n;
	rtk_uint16 nPreamble = 0;
	rtk_uint16 nData = 0;
#ifdef SMI_DEBUG
	pr_info("SMI: _smi_decode(): *f: %04X \n", *