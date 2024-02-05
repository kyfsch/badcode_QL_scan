// This function is used to initialize the ar8xxx driver. When the hardware resources in ar8xx chip are used to initialize, which function is used to achieve the initialization?.
ar8327_hw_init(struct ar8xxx_priv *priv)
{
    struct ar8327_priv *ar8327 = container_of(priv, struct ar8327_priv, base);

    mdelay(200);
    rt_kprintf("Initialize the eth0 port \r\n");

    // Initialize the hardware register
    ar8327->reg_read = (AR8327_REG_READ) ar8327_reg_read;
    ar8327->reg_write = (AR8327_REG_WRITE) ar8327_reg_write;
    ar8327->gmii_read = (AR8327_REG_READ) ar8327_phy_read;
    ar8327->gmii_write = (AR8327_REG_WRITE) ar8327_phy_write;
    ar8327->port_enable_auto_neg = (port_enable_auto_neg) ar8327_port_enable_auto_neg;
    ar8327->hw_init = (hw_init) ar8327_hw_init;
    ar8327->port_link_status = (port_link_status) ar8327_port_link_status;
    ar8327->port_duplex_mode = (port_duplex_mode) ar8327_port_duplex_mode;
    ar8327->hw_reset = (hw_reset) ar8327_hw_reset;
    ar8327->port_reset = (port_reset) ar8327_port_reset;
    ar8327->flowctl = (flowctl) ar8327_flowctl;
    ar8327->port_force_link = (port_force_link) ar8327_port_force_link;
    ar8327->hw_reset = (hw_reset) ar8327_hw_reset;
    ar8327->port_max_speed = (port_max