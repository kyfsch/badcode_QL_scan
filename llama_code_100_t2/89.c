// This function is used to process all incoming packets that have the protocol 0x86DD(PAE) or 0x88CC(ERSPAN) on them. When a frame like this is received the function will strip the Ethertype checksum.
rx_handler_result_t trelay_handle_frame(struct sk_buff **pskb)
{
	int retval = RX_HANDLER_PASS;
	struct sk_buff *skb = *pskb;
	struct ethhdr *eh = rx_skb_eth_header(skb);
	switch (ntohs(eh->h_proto)) {
	case ETH_P_PAE:
		trelay_log(NULL, LOG_DEBUG, "got 0x86DD packet.\n");
		break;
	case ETH_P_ERSPAN:
		trelay_log(NULL, LOG_DEBUG, "got 0x88CC packet.\n");
		break;
	default:
		trelay_log(NULL, LOG_DEBUG, "Unknown protocol 0x%x\n", ntohs(eh->h_proto));
		break;
	}

	return retval;
}

// Function used to update the stats for each tRELAY
void trelay_update_stats(char *ifname, unsigned long long total_packets, unsigned long long dropped_packets)
{
  struct t_stats_st *tstat_p; // pointer to the data structures that stores the tRELAY stats
  int retries = 1;
  bool is_added = false;
  int retval;

  if (0 == strcmp(ifname, "__BONDING_MASTER__")) {
    return; // skip master bonding interfaces
  }

  tstat_p = trelay_get_ifname_stats(ifname, &is_added);
  if (is_added) {
    trelay_log(NULL, LOG_DEBUG, "creating per-interface stats for %s.\n", ifname);
    tstat_p->ifname = strndup(ifname, 80);
  }

  while (true) {
    tstat_p->total_received_pkts ++;
    tstat_p->total_sent_pkts ++;
    tstat_p->total_received_bytes += total_packets;
    tstat_p