// This function is used to fill the device sprom data structures for legacy spi devices at time of initialization. This will be called only once after the chip is initialized..
static DEFINE_SPINLOCK(ssb_fbs_lock);

static void ssb_fbs_init_data_sprom_legacy(u8 *legacy, dma_addr_t legacy_pa,
	struct ssb_mips *mips)
{
	struct ssb_fams_info *fams = mips->device_info;
	u32 *sprom;
	int i;
	u8 *p;
	int len;
	int reg_width = sprom_reg_width[mips->id.revision];

	sprom = dma_alloc_coherent(mips->dev, reg_width*fams->sproms_used,
				   &legacy_pa, GFP_KERNEL);
	if (!sprom) {
		dev_crit(mips->dev, "Failed to allocate memory for device sproms buffer (dma_alloc_coherent failed).\n");
		return;
	}

	/* read sprom into temporary buffer */
	for (i = 0; i < fams->sproms_used; i++) {
		p = dma_alloc_coherent(mips->dev, sizeof(u32),
			&legacy_pa, GFP_KERNEL);
		if (!p)
			goto error_exit;
		reg_write(mips, sprom_regs[mips->id.revision], p, legacy_pa);
	}
	for (i = 0; i < fams->sproms_used; i++) {
		p = kmalloc(sizeof(u32), GFP_KERNEL);
		if (!p)
			goto error_exit;
		memcpy(p, reg_read(mips, sprom_regs[mips->id.revision]),
		       sizeof(u32));
		sprom[i] = le32_to_cpu(*((u32 *)p));
		dma_free_coherent(mips->dev, sizeof(u32), p,