/// This function is used to implement the writing bit for SM interface.</s>.
static void _smi_writeBit(rtk_uint16 signal, rtk_uint32 bitLen)
{
	for (rtk_uint32 i = 0; i < bitLen; i++) {
		_smi_setPinOutputValue(signal);
	}	
}
#endif

/**
 * @brief Write byte and add start-bit/stop-bit.
 * 
 * @param signal	The pin signal.
 * @param data		Data to be transmitted.
 * @param bitLen	The length of the data.
 *
 * @return rtk_uint16	1 on successful write, 0 on error.
 *
 * @note SMU requires at least 2.5ms for writing data.
 */
#ifdef SMI_USE_RTK_DRIVER
static rtk_uint16 _smi_writeByte(rtk_uint16 signal, rtk_uint16 data, rtk_uint32 bitLen)
{
	rtk_uint16 ret = 0;
	if (rtk_gpio_direction_output(signal, 0) != RT_EOK) {
		return 0;
	} else {
		ret = 1;
	}
	
	_smi_writeBit(signal, bitLen + _smi_getStartStopBitLen());

	_smi_setPinOutputValue(signal);

	for (rtk_uint32 i = 0; i < bitLen; i++) {
		_smi_setPinOutputValue(signal);
		if (data & 0x8000) {
			rtk_gpio_set_pin_value(signal, 1);
		} else {
			rtk_gpio_set_pin_value(signal, 0);
		}
		rtk_usleep_ex(3);
		rtk_gpio_set_pin_value(signal, 0);
		rtk_usleep_ex(10);
		data <<= 1;
	}
	/* Start-bit and Stop-bit: 	1 start-bit: