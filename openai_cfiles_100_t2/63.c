
void apply_vlan_mapping(int port, int vlan_id)
{
    // Set the VLAN ID for the specified port
    mt7530_set_vlan_id(port, vlan_id);
    
    // Enable VLAN mapping for the specified port
    mt7530_enable_vlan_mapping(port);
}


In this example, the function takes two parameters: `port` (integer) and `vlan_id` (integer). The `port` parameter specifies the port number on the MT7530 chip, and the `vlan_id` parameter specifies the VLAN ID to be set for that port.

Within the function, the `mt7530_set_vlan_id` function is called to set the VLAN ID for the specified port. This function is responsible for configuring the proper register(s) on the MT7530 chip to set the VLAN ID.

After setting the VLAN ID, the `mt7530_enable_vlan_mapping` function is called to enable VLAN mapping for the specified port. This function is responsible for configuring the necessary register(s) on the MT7530 chip to enable VLAN mapping for the specified port.