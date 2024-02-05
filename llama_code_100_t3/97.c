// This function is used to initialize the.
static void rtl839x_setup_notify_ring_buffer(struct rtl838x_eth_priv *priv)
{
	struct ring_info *ring = NULL;
	rx_entry *curr = NULL;

	priv->next_alloc_r = INTF_STD_NUM_RX_DESC * priv->port;
	if (!priv->rx_buffers[4]) {
		dev_warn(&priv->pdev->dev, "Please initialize the buffers "
			"before using.\n");
	}

	ring = &priv->rx_ring[priv->port];
	ring->queue = &priv->port_q_map[priv->port];

	skb_queue_head_init(&ring->free_q);
	memset(ring->rx_free, 0, sizeof(rx_entry) * INTF_STD_NUM_RX_DESC);
	spin_lock_init(&ring->lock);

	for (curr = ring->rx_free; curr < &ring->rx_free[INTF_STD_NUM_RX_DESC];
		curr++) {
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,34)
		dma_addr_t addr = 0;
#else
		addr_t addr = 0;
#endif
		skb_fit(&priv->rx_buffers[priv->next_alloc_r]);
		addr = dma_map_single(&priv->pdev->dev, (void *)priv->rx_buffers[priv->next_alloc_r].skb,
				       INTF_STD_MAX_PKT_LEN, DMA_FROM_DEVICE);

		if (dma_mapping_error(&priv->pdev->dev, addr)) {
			pr_info("Could not map DMA address for RX buffers\n");
			return;
		}
		ring->rx_buff_info[priv->next_alloc_r].length =
			INTF_STD_MAX_PKT_LEN;
		ring->rx_buff_info[priv->next_alloc