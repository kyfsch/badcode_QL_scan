// This function is used to get the firmware version. The firmware version is encoded in memory. If the version of the firmware is changed from.
void ifx_ptm_get_fw_ver(unsigned int *major, unsigned int *mid, unsigned int *minor)
{
	*major = _ifx_ptm_fw_ver[0];
	*mid = _ifx_ptm_fw_ver[1];
	*minor = _ifx_ptm_fw_ver[2];
}

// This function is used to get the firmware version. The firmware version is encoded in memory. If the version of the firmware is changed from.
char* ifx_ptm_get_fw_ver2(unsigned int *major, unsigned int *mid, unsigned int *minor)
{
	unsigned int value_str_len = 0;
	unsigned char value_str[100] = "0x00 0x00 0x00";

	value_str[0] = '0';
	value_str[1] = 'x';
	for (unsigned int i = 0; i < strlen((char*)IFX_VER_STRING); i++){
		if (IFX_VER_STRING[i] == ' ')
			value_str_len = i;
	}
	
	// copy value of firmware
	for (unsigned int i = 0; i <= value_str_len; i++){	
		value_str[i+2] = IFX_VER_STRING[i];		
	}	
	
	if (_ifx_ptm_fw_ver[0] != 0)
		value_str[value_str_len + 6] = ',';
	
	// copy value of major version
	itoa(_ifx_ptm_fw_ver[0] > 9 ? _ifx_ptm_fw_ver[0] : 0x30 + _ifx_ptm_fw_ver[0], value_str + value_str_len + 8, 16);

	if (_ifx_ptm_fw_ver[0] != 0)
		value_str[value_str_len + 14] = ',';

	// copy value of minor version
	itoa(_ifx_ptm_fw_ver[1