static void aca_dma_init(struct dc_ep_priv *priv)
{
	int i;
	struct aca_fw_info *fw_info = to_fw_info(priv);

	aca_dma_ctrl_init(priv);
	aca_dma_port_init(priv);

	for (i = 0; i < fw_info->chan_num; i++) {
		aca_dma_ch_init(priv, i,
			fw_info->adma_desc_base[i] | priv->phymem,
			DESC_NUM_PER_CH);
	}

	dev_dbg(priv->dev, "aca dma init done\n");
}
