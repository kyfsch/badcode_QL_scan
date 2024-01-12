static void aca_dma_ch_init(struct dc_ep_priv *priv, u32 cid,
	u32 dbase, u32 dlen)
{
	/* Select channel */
	wr32(cid, ADMA_CS);

	/* Reset Channel */
	wr32_mask(0, BIT(CCTRL_RST), ADMA_CCTRL);
	while ((rd32(ADMA_CCTRL) & BIT(CCTRL_RST)))
		;

	/* Set descriptor list base and length */
	wr32(dbase, ADMA_CDBA);
	wr32(dlen, ADMA_CDLEN);

	/*Clear Intr */
	wr32(ADMA_CI_ALL, ADMA_CIS);
	/* Enable Intr */
	wr32(ADMA_CI_ALL, ADMA_CIE);

	/* Enable Channel */
	wr32_mask(0, BIT(CCTRL_ONOFF), ADMA_CCTRL);
	mb();
}
