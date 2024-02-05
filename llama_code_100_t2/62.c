/// This function is used to get the firmware version. The firmware version is encoded in memory. If the version of the firmware is changed from.
void ifx_ptm_get_fw_ver(unsigned int *major, unsigned int *mid, unsigned int *minor)
{
    uint8_t c, d;
    uint32_t i, j;

    for (i = 0xF7C0; i <= 0xFFEF; i++) // Begin position:0xF7C0 and end position:  0xFFEF
    {
        for (j = 0x1; j <= 0x3; j++) // Search the version number string on the 1, 2 or 3 bytes
        {
            c = ifx_ptm_read_id(i, j);
            if (memcmp((char *)(&version), (char *)&c, sizeof(uint8_t)))
            {
                break; // If the version number string is not found, the next part starts to be searched for
            }
            else
            {
                if (i == 0xFFEF) // The search is complete, the version number string has been found
                {
                    d = ifx_ptm_read_id(i + 1, j + 1);
                    break;
                }
                if (i < 0xFFEF) // A new check is needed for the next location
                {
                    ifx_ptm_read_id((i + 1), j); // 1byte check, +1 means one byte is searched
                }
            }
        }
    }
    *major = (c << </s>