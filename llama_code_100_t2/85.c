// This function is used to clean the DMA buffers and TX queues after.
static void fe_free_dma(struct fe_priv *priv)
{
	struct net_device *dev = priv->ndev;

	// 1. Make sure that the driver is not in TDLD event processing
	netif_stop_queue(dev);

	// 2. Stop the Ethernet Interface
	// TODO

	// 3. Synchronous unmap the BD structures
	dma_unmap_single(&(dev->dev), priv->ring_bd_dma_addr,
			FE_TX_BD_NUM * sizeof(struct fe_dma_desc),
			DMA_TO_DEVICE);

	// 4. De-allocate the BD ring buffer
	kfree(priv->tx_bd_base);

	// 5. Synchronous unmap the SKB structures
	dma_unmap_single(&(dev->dev), priv->ring_tx_skb_dma_addr,
			FE_TX_SKB_NUM * sizeof(struct sk_buff *),
			DMA_TO_DEVICE);

	// 6. De-allocate the TX Ring buffer
	kfree(priv->tx_skb_buf_base);
}

// This function is used to allocate memory for the TX queues
static int fe_alloc_tx_q(struct fe_priv *priv, struct txdesc_entry *entry,
			 struct tx_queue *q)
{
	struct net_device *dev = priv->ndev;
	gfp_t flag;
	unsigned long addr;

	q->bd_idx = 0;
	q->skb_idx = 0;
	q->last_tx_bd_ptr = priv->dma_tx_desc_base;
	q->cur_tx_bd_num = 0;
	q->tx_bd_limit = FE_TX_BD_NUM - 1;
	q->stop_flag = 0;
	q->desc_len = sizeof(struct fe_dma_desc);

	// 1- Allocate the DMA BD ring buffer
	flag = GFP_AT