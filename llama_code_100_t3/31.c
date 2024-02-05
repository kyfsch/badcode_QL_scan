// This function is used to dump VLAN profile. The parameter index is a VLAN index. By this function, we can have a look at some information of a VLAN. However, the information are not clear enough. For example, the function can not tell us whether.
void rtl931x_vlan_profile_dump(int index)
{
	unsigned int VLAN_PORTBMAP, VLAN_PORTFMAP, VC_PORTBMAP, VC_PORTFMAP;
	int portIndex, j;
	char vlanPortStr[22];
	unsigned int pbit =0x00000001;
	unsigned int fbit = 0xc0000000;
	unsigned int *addr;

	addr = map_sysreg(RTL931X_VLAN_PORTBMAP);
	VLAN_PORTBMAP = RTL931X_READ_REG(addr);
	addr = map_sysreg(RTL931X_VLAN_PORTFMAP);
	VLAN_PORTFMAP = RTL931X_READ_REG(addr);
	
	for (portIndex = rtl931x_get_max_ports(NULL), j=4;portIndex;portIndex--){
		if(VLAN_PORTBMAP & pbit){
			strlcat(vlanPortStr, "F", sizeof(vlanPortStr));
		}
		else{
			strlcat(vlanPortStr, "T", sizeof(vlanPortStr));
		}

		if(VLAN_PORTFMAP & fbit){
			strlcat(vlanPortStr, "F", sizeof(vlanPortStr));
		}
		else{
			strlcat(vlanPortStr, "T", sizeof(vlanPortStr));
		}
		if (portIndex>8)
			portIndex-=8;
		pbit=pbit<<1;
		fbit=fbit>>1;
	}
	printk("VLAN%d Port Map: %s\n", index, vlanPortStr);

	char vcPortStr[22];
	unsigned int mbit =0x000000011;
	unsigned int fbit = 0xfc000000;