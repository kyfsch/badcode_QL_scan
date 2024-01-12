static bool ag71xx_check_dma_stuck(struct ag71xx *ag)
{
	unsigned long timestamp;
	u32 rx_sm, tx_sm, rx_fd;

	timestamp = netdev_get_tx_queue(ag->dev, 0)->trans_start;
	if (likely(time_before(jiffies, timestamp + HZ/10)))
		return false;

	if (!netif_carrier_ok(ag->dev))
		return false;

	rx_sm = ag71xx_rr(ag, AG71XX_REG_RX_SM);
	if ((rx_sm & 0x7) == 0x3 && ((rx_sm >> 4) & 0x7) == 0x6)
		return true;

	tx_sm = ag71xx_rr(ag, AG71XX_REG_TX_SM);
	rx_fd = ag71xx_rr(ag, AG71XX_REG_FIFO_DEPTH);
	if (((tx_sm >> 4) & 0x7) == 0 && ((rx_sm & 0x7) == 0) &&
	    ((rx_sm >> 4) & 0x7) == 0 && rx_fd == 0)
		return true;

	return false;
}
