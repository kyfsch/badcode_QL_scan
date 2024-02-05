/// This function is used to fire the callback when the timer expired. However when looking at the code, there is no timer callback being setup.</s>.
static void bcm6348_emac_refill_rx_timer(struct timer_list *t)
static int bcm6348_emac_refill_rx_packets(struct bcm6348_emac *emac,
static int bcm6348_emac_refill_rx_descs(struct bcm6348_emac *emac,
static int bcm6338_emac_reset_rx_intr(struct bcm6348_emac *emac,
static int bcm6348_emac_set_link(struct net_device *ndev,
static void bcm6348_emac_reset_tx(struct bcm6348_emac *emac)
static void bcm6348_emac_set_mac_addr(struct net_device *ndev)
static netdev_features_t bcm6348_emac_fix_features(struct net_device *ndev,
const char bcm6348_emac_driver_name[] = "bcm6348_emac"
static int bcm6348_emac_handle_irq(struct bcm6348_emac *emac, u8 emac_idx)
/*
 * Register a PHY with the driver. If possible, the driver will attempt
 * to find out if the PHY is already configured (in particular if it's
 * using the internal PHY) and will change only relevant parameters.
 */
static int bcm6348_emac_mdio_read(struct mii_bus *bus, int phy_id, int reg)
static int bcm6348_emac_mdio_write(struct mii_bus *bus, int phy_id, int reg,
int bcm63xx_reset_gmac(int reg)
static int bcm63xx_emac_mac_reset(struct bcm63xx_enet *enet)
static int bcm63xx_emac_clk_reset(struct bcm63xx_enet *enet)
static void bcm63xx_emac_enable