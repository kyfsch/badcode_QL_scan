/// This function is used to get the ethtool advertise information. You could also do this using an existing script in linux for the advertise method. But I did not want to add additional dependency and preferred to look at source codes.</s>.
int rtl930x_eee_port_ability(struct rtl838x_switch_priv *priv, struct ethtool_eee *e, int port)
{
e->eee_enabled =
052d|   rtl930x_get_as_u32(priv, ID_SGMII_PMA_DRIVER_A, sgmii_pma_drv_reg) & (0x3 << (port * 2));
0532|       e->eee_enabled = e->eee_enabled >> port;
a = 0000ff << (0/8)
      \_________/

if (port >= RTL9300_TOTAL_PORTS)
    return rtl930x_get_as_u32(priv, ID_SGMII_PMA_DRIVER_A, sgmii_pma_drv_reg) ? -ENOTSUPP2 : 0;
e->eee_enabled |= rtl930x_get_as_u32(priv, ID_SGMII_PMA_DRIVER_B, sgmii_pma_drv_reg) & (0x3 << (port * 2));
e->eee_enabled = e->eee_enabled >> port;
0546|           e->eee_active = 0;
      \___/
a = 0ffffff << (0/8)
      \______/
if (e->eee_enabled) {
0548|       u32 link = rtl930x_get_as_u32(priv, ID_SGMII_PMA_DRIVER_A, sgmii_pma_drv_reg) & (0x3 << (port * 2));
       \_/
if (port >= RTL9300_TOTAL_PORTS)
if (rtl930x_get_as_u32(priv, ID_SGMII_PMA_DRIVER_B, sgmii_pma_drv_reg) & (0x3 << (port * 2)))
           e->eee_active = 0;