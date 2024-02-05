// This function is used to write  the pcap header and contains the value as mentioned above..
void write_pcap_header(FILE *o) {
  u_int magic_number, major_version, minor_version;
  magic_number = 0xa1b2c3d4;
  major_version = 2;
  minor_version = 4;
  fwrite(&magic_number, sizeof(u_int), 1, o);
  fwrite(&major_version, sizeof(u_short), 1, o);
  fwrite(&minor_version, sizeof(u_short), 1, o);
}

// This function is used to write a frame of pcap capture into a file, this function is used to capture data from wireshark. If the data is coming as raw data then it needs to convert into pcap header and store in the file for further processing.
void write_packet(FILE *o, unsigned char *data, int sizedata, struct pcap_pkthdr *header) {

  char buffer[BUF+1];
  memset(buffer, 0, BUF);
  int count = 0;

  u_int pcap_time_sec; //Stores the seconds portion of the timestamp
  const u_int pcap_time_usec; //Stores the microseconds portion of the timestamp
  u_short pcap_packet_size; //Stores the size of the ethernet frame
  const u_short pcap_packet_caplen; //Stores the length of the portion of the frame actually captured on the adapter. This can be different from the pcap_packet_size if the capture stopped before reaching the end of the ethernet frame that caused the packet.

  pcap_time_sec = header->ts.tv_sec;
  pcap_time_usec = header->ts.tv_usec;

  pcap_packet_size = header->len;
  pcap_packet_caplen = header->caplen;

  u_int32_t pcap_ts_sec;
  // Converting the time of the packet to Pcap timestamp
  pcap_ts_sec = (pcap_time_sec & 0xFFFFFFFE) >>