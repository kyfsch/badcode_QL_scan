// This function is used to clean the DMA buffers and TX queues after.
static void fe_free_dma(struct fe_priv *priv)
{
	int i;

	for (i = 0; i < FE_DMAS; i++) {
		struct fe_dma *dma = &priv->fe_dmas[i];

		skb_queue_purge(&dma->tx_queue);
		dma_free_coherent(&priv->pci_dev->dev,
				  FE_NUM_RX_BUFFERS * DMA_BUFFER_SIZE,
				  dma->rx_buffers, dma->buffer_area);
	}
}

// Allocate and initialize the DMA buffers.
static int fe_init_dma(struct fe_priv *priv)
{
	struct net_device *dev = priv->dev;
	struct fe_ring *ring;
	struct fe_dma *dma;
	struct fe_tx_dma_desc *cd;
	int i, j;

	// Allocate buffer for skb ring pointers.
	dma = kzalloc(sizeof(*dma), GFP_KERNEL);
	if (!dma)
		return -ENOMEM;
	priv->fe_dmas[0] = *dma;	// Just in case.

	// Allocate RX descriptors and the buffer area
	for (i = 0; i < FE_DMAS; i++) {
		dma = &priv->fe_dmas[i];

		// Clear the descriptor rings.
		for (j = 0; j < FE_NUM_RX_BUFFERS; j++) {
			ring = &dma->rx_ring[j];
			memset(ring, 0, sizeof(*ring));
		}
		// Allocate the buffer area, and fill in the skb ring pointers.
		dma->buffer_area = dma_alloc_coherent(&priv->pci_dev->dev,
						      FE_NUM_RX_BUFFERS * D