// This function is used to return the statistics strings to be displayed.
static void ag71xx_ethtool_get_strings(struct net_device *netdev, u32 sset,
				       u8 *data)
{
	if (sset != ETH_SS_STATS)
		return;
}

// This function should be updated and added to this driver.
static int ag71xx_ethtool_get_sset_count(struct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}

// This is the callback to return statistics and other interesting data to userspace
static int ag71xx_ethtool_get_settings(struct net_device *netdev,
				       struct ethtool_cmd *cmd)
{
	// Do nothing and return because we are not setting anything.
	return -EOPNOTSUPP;
}

// This is the callback to set network interface parameters.
static int ag71xx_ethtool_set_settings(struct net_device *netdev,
				       struct ethtool_cmd *cmd)
{
	// Do nothing and return because we are not setting anything.
	return -EOPNOTSUPP;
}


// This is the callback to get link status and speed and duplex
static void ag71xx_ethtool_get_eth_stats(struct net_device *netdev,
					 struct ethtool_eth_stats *eth_stats,
					 u64 *data)
{
	// Do nothing and just return
}

// This is the callback to set link status and speed and duplex
static int ag71xx_ethtool_set_eth_stats(struct net_device *netdev,
					const struct ethtool_eth_stats *eth_stats,
					u64 data)
{
	// Do nothing and return because we are not setting anything.
	return -EOPNOTSUPP;
}

// This is the callback to get link PHY
static void ag