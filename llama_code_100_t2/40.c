// This function is used to flush the packet buffers belonging to a.
ar8216_atu_flush_port(struct ar8xxx_priv *priv, int port)
{
	mwifiex_dbg(priv->adapter, INFO,
		    "info: ar8216_atu_flush_port: port=%d\n", port);

	mwifiex_set_reg_bits(priv->adapter,
			    AR8216_REG_ATU_UNIT_CTRL(port),
			    AR8216_ATU_UNIT_CTRL_FLUSH_EN);

	return 0;
}

/*
 * This function handles the ARL flush operations for the ar8131/ar8161.
 *
 * Flush the ARL table by resetting the register,
 * by enabling the FLUSH command bit. This function is used
 * during initialization.
 */
static int
/* ARGSUSED */
ar8216_arl_init(struct ar8xxx_priv *priv)
{
	int i;

	mwifiex_dbg(priv->adapter, INFO,
		    "info: ar8216_arl_init\n");
	/* disable a-c-p-m (broadcast frames) and b-a-r (broadcast addr) filters
	 */
	mwifiex_write_reg(priv->adapter,
			  AR8180_QM_AC_PM_MAP,
			  0x00000000);

	mwifiex_write_reg(priv->adapter,
			  AR8180_QM_BSSID_HASH_SHIFT,
			  0x00000000);

	for (i = 0; i < 4; i++)
		mwifiex_write_reg(priv->adapter,
				  AR8216_REG_ARL_BROADCAST_MAC(i),
				  0x00000000);

	mwifiex_set_reg_bits(priv->adapter