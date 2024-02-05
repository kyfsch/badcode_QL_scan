// This function is used to return the statistics strings to be displayed.
static void ag71xx_ethtool_get_strings(struct net_device *netdev, u32 sset, u8 *data)
{
    struct ag71xx *lp = netdev_priv(netdev);
    int index;

    switch (sset) {
	case ETH_SS_STATS:
            // Get the statistics strings with respect to the ag71xx Ethernet controller.
		for(index=0;index<32;index++)
			strcpy(&data[index*ETH_GSTRING_LEN], ag71xx_gstrings_stats[index].stat_string);
		break;

	default:
		WARN_ON(1);
		break;
    }
}

// This function is used to get the statistics value of respective Ethernet controller.
static void ag71xx_ethtool_get_stats(struct net_device *netdev, struct ethtool_stats *stats, u64 *data)
{
	int index;
	struct ag71xx *lp = netdev_priv(netdev);

	// Get all the statistics of particular Ethernet controller.
	for(index=0;index<32;index++)
		data[index] = ag71xx_stats[index].get(lp);
}
// ============================================================================================

STATIC void ag71xx_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	strlcpy(info->driver, DRV_MODULE_NAME, sizeof(info->driver));
	strlcpy(info->version, DRV_MODULE_VERSION, sizeof(info->version));
	//strlcpy(info->fw_version, "N/A", sizeof(info->fw_version));
	strlcpy(info->bus_info, pci_name(lp->pdev), sizeof(info->bus_info));
	info->regdump_len = 0;
	strlcpy(info->name, "ag71xx", sizeof(info->name));
}

STATIC int ag71xx_get_regs_len(struct net_device *dev)