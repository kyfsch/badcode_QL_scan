static void aca_dma_ch_off(struct dc_ep_priv *priv)
{
	int i;
	struct dc_aca *aca = to_aca(priv);

	/* Shared between OS and ACA FW. Stop ACA first */
	for (i = 0; i < aca->adma_chans; i++) {
		wr32(i, ADMA_CS);
		wr32_mask(BIT(CCTRL_ONOFF), 0, ADMA_CCTRL);
		while (rd32(ADMA_CCTRL) & BIT(CCTRL_ONOFF))
			;
	}
	dev_dbg(priv->dev, "aca dma channel done\n");
}
