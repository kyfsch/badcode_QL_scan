// This function is used to initialize the.
static void rtl839x_setup_notify_ring_buffer(struct rtl838x_eth_priv *priv)
{
	if (rtl839x_check_asic_rev(priv, CHECK_REVISION_NO_MINIMUM))
		return;

	// Initialize 7-bit vector to notify receive buffers with interrupt
	rtl838x_writel(priv, RTL838X_PPE_QOS_NOTIFY_REG, 0x7F);
}

// This function is used to initialize all the interrupts
static void rtl839x_setup_interrupt_masks(struct rtl838x_eth_priv *priv,
				       u32 p_int_mask,
				       u32 d_int_mask,
				       u32 m_int_mask,
				       u32 dsch_int_mask,
				       u32 sch_int_mask,
				       u32 pppe_int_mask,
				       u32 tlv_int_mask,
				       u32 msh_int_mask)
{
	rtl839x_writel_masked(priv, RTL838X_REG_FH_INT_MASK_RX,
		p_int_mask, 0xFFFFFFFF);
	rtl839x_writel_masked(priv, RTL838X_REG_FH_INT_MASK_MDIO,
		p_int_mask, 0xFFFFFFFF);
	rtl839x_writel_masked(priv, RTL838X_REG_FH_INT_MASK_DMA,
		d_int_mask, 0xFFFFFFFF);
	rtl839x_writel_masked(priv, RTL838X_REG_FH_INT_MASK_MAC,
		m_int_mask, 0xFFFFFFFF);
	rtl839x_writel_masked(priv, RTL838X