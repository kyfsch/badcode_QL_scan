static void aca_basic_init(struct dc_ep_priv *priv)
{
	u32 addr, mask;

	/* Low 32 is RX, High 32 is TX */
	wr32(0x1, UMT_ORDER_CFG);
	/* TXIN/TXOUT/RXIN/RXOUT All Controlled by Genrisc */
	wr32(0xF, HOST_TYPE);
	/* Enable Host Gate CLK */
	wr32(0x4000, HT_GCLK_ENABLE);
	/* Host Page/MASK */
	mask = ~priv->memsize + 1;
	addr = mask | ((priv->phymem & mask) >> 16);
	wr32(addr, AHB_ARB_HP_REG);
	wr32(addr, OCP_ARB_ACC_PAGE_REG);
	/* Stop all functions first */
	wr32(0, GNRC_EN_TASK_BITMAP);

	/* Enable XBAR */
	aca_xbar_ia_reject_clr(priv, ACA_ACC_IA04);
	aca_xbar_ia_reject_clr(priv, ACA_M_IA06);

	dev_dbg(priv->dev, "aca basic config done\n");
}
