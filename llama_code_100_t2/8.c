// This function is used to insert an SFP module into the port. It will perform.
static int qca807x_sfp_insert(void *upstream, const struct sfp_eeprom_id *id)
{
	// Check that the specified port is QCA807x's first internal port
	struct rte_eth_dev *eth_dev = (uintptr_t)upstream;
	struct qca807x_port *priv;

	priv = eth_dev->data->dev_private;
	// If SFP port is connected to RGMII/SGMII port
	if (!((eth_dev->data->port_id >= QCA807X_RGMII_PORT_START) &&
		(eth_dev->data->port_id <= QCA807X_RGMII_PORT_END)))
		return -1;

	// If SFP is not inserted.
	if (!eth_dev->data->dev_started)
		return 0;


	// First set this port to disabled mode (1), if it is enabled.
	qca807x_rte_port_dev_stop(eth_dev);

	// Write the specified sfp's information into private variable.
	memcpy(&(priv->sfp_eeprom), id, sizeof(struct sfp_eeprom_id));
	// And then start this port.
	qca807x_rte_port_dev_start(eth_dev);

	return 0;
}

int qca807x_sfp_eject(struct rte_eth_dev *eth_dev)
{
	int port_idx = eth_dev->data->port_id;
	qca8k_phy_device_t port = port_idx - 1;
	struct qca807x_cfg_priv *priv = eth_dev->data->dev_private;
	struct qca8k_reg_mmd_data data;
	struct rte_sfp_eeprom *sfp_eeprom;
	static struct sfp_eeprom_id id;
	int status, err, retry = 0;

	qca807x_phy_debug_addr_read(port, SFP_E