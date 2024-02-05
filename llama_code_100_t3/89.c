// This function is used to process all incoming packets that have the protocol 0x86DD(PAE) or 0x88CC(ERSPAN) on them. When a frame like this is received the function will strip the Ethertype checksum.
rx_handler_result_t trelay_handle_frame(struct sk_buff **pskb)
{
	// Create a pointer for the packet to be manipulated
	struct sk_buff *skb = *pskb;
	struct ethhdr *eth;
	
	// Check to make sure there actually is a packet received
	if (unlikely(!skb)) {
		trelay_log( LOGLEVEL_WARNING, "trelay_handle_frame: Warning - A packet has no data!\n");
		return TX_DROP;
	}
	
	// Get a pointer to the Ethernet header for the packet
	eth = (struct ethhdr *) skb->data;

	// Use eth->h_proto to get the current protocol value
	// eth->h_proto is always going to be little endian
	__be16 proto_type = eth->h_proto;
	
	if(proto_type == htons(0x86DD))	// Ethernet Protocol Address Encapsulation(PAE)
	{
		skb = strip_8021q_header(skb);
		if (unlikely(!skb)) {
			return TX_DROP;
		}
		eth = (struct ethhdr *) skb->data;
		if(trelay_log_level >= LOGLEVEL_VERBOSE)
		{
			trelay_log( LOGLEVEL_VERBOSE, "Trelay received a PAE packet\n");
			trelay_log_ethernet_address("Incoming PAE TID/RID:",
									eth->h_dest,
									eth->h_source);
			trelay_log_ethernet_address("Outgoing PAE TID/RID:",
									eth->h_dest,
									trelay_local_hardware_address);
		}
	}
	else if(proto_type == htons(ETH_P_ERSPAN_TYPE6))	// Ether