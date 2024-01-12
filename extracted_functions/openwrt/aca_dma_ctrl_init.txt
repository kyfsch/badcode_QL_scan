static void aca_dma_ctrl_init(struct dc_ep_priv *priv)
{
	u32 val;
	struct dc_aca *aca = to_aca(priv);

	/* Global software reset CDMA */
	wr32_mask(0, BIT(CTRL_RST), ADMA_CTRL);
	while ((rd32(ADMA_CTRL) & BIT(CTRL_RST)))
		;

	val = rd32(ADMA_ID);
	/* Record max dma channels for later usage */
	aca->adma_chans = MS(val, ADMA_ID_CHNR);
	val = rd32(ADMA_CTRL);
	/*
	 * Enable Packet Arbitration
	 * Enable Meta data copy
	 * Enable Dedicated Descriptor port
	 */
	val |= BIT(CTRL_PKTARB) | BIT(CTRL_MDC) | BIT(CTRL_DSRAM);
	set_mask_bit(val, 1, 1, CTRL_ENBE); /* Enable byte enable */
	set_mask_bit(val, 1, 1, CTRL_DCNF); /* 2DW descriptor format */
	set_mask_bit(val, 1, 1, CTRL_DDBR); /* Descriptor read back */
	set_mask_bit(val, 1, 1, CTRL_DRB); /* Dynamic burst read */
	wr32(val, ADMA_CTRL);

	/* Polling cnt cfg */
	wr32(ADMA_CPOLL_EN | SM(ADMA_DEFAULT_POLL, ADMA_CPOLL_CNT),
		ADMA_CPOLL);
}
