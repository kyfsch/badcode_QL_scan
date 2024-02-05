// This function is used to change the PLLA configuration, but for different.
int plla_set_config(int mhz)
{
	int32_t i, ret=0, mux=1;
	for (i=0; i<PLLA_TABLE_LEN; i++)
	{
		if (mhz==plla_tbl[i].mhz)
			break;
	}

	if (mhz==plla_tbl[i].mhz)
	{
		mux = (plla_tbl[i].config>>24)&3;
		if (mux < 3)
		{
//			regWrite32(MP_PLLA_PLLA0, 0);
			__REG32(MP_PLLA_PLLA0) = 0;

//			regWrite32(MP_PLLA_PLLA1, 0);
			__REG32(MP_PLLA_PLLA1) = 0;
			if (mux==1)
			{
//				regWrite32(MP_PLLA_PLLA1,(plla_tbl[i].config&MHZ_MASK));
				__REG32(MP_PLLA_PLLA1) = (plla_tbl[i].config&MHZ_MASK);
			}
			else if (mux==2)
			{
//				regWrite32(MP_PLLA_PLLA0,plla_tbl[i].config);
				__REG32(MP_PLLA_PLLA0) = (plla_tbl[i].config);
			}
		}
	}
#if 0
	else
	{
		printf("%s:%d set plla to new config: %d\n", __func__, __LINE__, mhz);
		plla_set_config(g_plla_default);  /* restore to default */
		plla_set_config(20);   /*