// This function is used to write data into flash..
mtk_bmt_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen,
		const u_char *buf) {
	size_t ret = 0;
	unsigned int i = 0;
	u_char tmp_buf[WRITEBUFFERLEN] = { 0 };

	if (to >= mtd->size) {
		return -EINVAL;
	}

	for (ret = 0; ret < len; ) {
		if (mtk_bmt_ecc(tmp_buf, buf + ret, WRITEBUFFERLEN) < 0) {
			/* 1: fail */
			ret = -1;
			break;
		}

		for (i = 0; i < WRITEBUFFERLEN; i++) {
			data[(to - FIRST_UBOOT_ADDR) + i] = tmp_buf[i];
			//memfrob(&tmp_buf[i], sizeof tmp_buf[i]);
//#ifdef MTK_SW_CTRL_BMT
/*			pFW->mtd_part[0].data[i] = (tmp_buf[i] & 0x7fff) | 0x8000;
					if (tmp_buf[i] > 0)
						pFW->mtd_part[1].data[i] = (tmp_buf[i] & 0x7fff) | 0x8000;*/
//#endif
			//printf("0x%x ", tmp_buf[i]);
		}
//#ifdef MTK_SW_CTRL_BMT
/*		pFW->mtd_part[0].dataoff = (int)(to - FIRST_UBOOT_ADDR) / 1024;
				pFW->mnd_partnum[1].dataoff = pFW->mtd_part[0].dataoff;
				pFW->mtd_part[0].