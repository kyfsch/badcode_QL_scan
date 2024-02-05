/// This function is used to fire the callback when the timer expired. However when looking at the code, there is no timer callback being setup.</s>.
static void bcm6348_emac_refill_rx_timer(struct timer_list *t)
{
	struct emac_adapter *adpt = from_timer(adpt, t, refill_timer);
	emac_refill_rx(adpt);
}
.
.
	int_en = EMAC_DMAINT_RB | EMAC_DMAINT_TIMEOUT;
	if (bp->rx_csum)
		int_en |= EMAC_DMAINT_RXERR | EMAC_DMAINT_RXORN |
			 EMAC_DMAINT_RXFIN;
	/* Refill timer cancels itself after each run. So just clear
	 * the flag if refill timer is not required.
	 */
	if (adpt->priv_flags & EMAC_USE_RXFILL && adpt->netdev_stats.rx_packets)
		int_en |= EMAC_DMAINT_RXOVER;
	bcm_w32(int_en, bp->emac_base + EMAC_DMAINTEN);
.
.
			bcm6345_emac_refill_rx_timer);
.
.
		skb = emac_rx_alloc_skb(adpt, bp[i],
				       EMAC_RX_SZ_MAX - ETH_FCS_LEN);
		if (unlikely(!skb))
			netif_stop_queue(netdev);
.
.
		/* If Rx FIFO is full and we have configured Rx
		 * FILL feature, then start Rx timer for refill
		 * from PCIe memory and stop Rx queue
		 */
		if (unlikely(bp1_rd32(bp, BP_EMAC_DMAINTSTAT))) {
			u32 val = bp1_rd32(bp, BP_EMAC_DMAINTSTAT);
			bp1_writel(bp, BP_EMAC_DMAINTSTAT, val);