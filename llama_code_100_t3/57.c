// This function is used to write  the pcap header and contains the value as mentioned above..
void write_pcap_header(FILE *o)
{
printf("Printing Function : ");
	time_t curtime = time(0);
	struct tm tmres = *localtime(&curtime);
	uint32_t seconds = (tmres.tm_hour * 3600) + (tmres.tm_min * 60) + tmres.tm_sec;
	int32_t t_sig = (seconds*1000) + (tmres.tm_mday*100) + (tmres.tm_mon);
	uint32_t  t = htonl(t_sig);
	//fprintf(stdout,"\t%d\t %d: %d\t %d\n",tmres.tm_year,tmres.tm_mon,tmres.tm_mday,t_sig);
	fprintf(o,"\n%d\n%d\n%d\n",sizeof(struct pcap_file_header),1,  PCAP_TIMEOUT);
	uint16_t p_network = PCAP_PACKET_NW;
	uint16_t p_systime = PCAP_PACKET_SYSTEM_TIME;
	fwrite(&p_network,     2,1,o);
	fwrite(&p_systime,     2,1,o);
	fwrite(&npackets,    4,1,o);
	fwrite(&t);
}

// This function is used to write  the pcap packet header and contains the value as mentioned above..
void write_pcap_packet_header(FILE *o)
{

	uint32_t length = (sizeof(struct pcap_packet)+hdr->caplen) + 4;
	fwrite(&length, 4, 1,o);
	fwrite(hdr, sizeof(struct pcap_header),1,o);
	fwrite(buffer,sizeof(u_char),hdr->len,o);
}



int main(int argc, char** argv)
{
    u_char *buffer;
    FILE *save_raw