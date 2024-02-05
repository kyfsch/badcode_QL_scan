// This function is used to call rtl9300_i2c_write() and it is the only function which i2c_write is called. rtl9300_i2c_write has its own implementation. According to the source.
static int rtl9300_i2c_write(struct rtl9300_i2c *i2c, u8 *buf, int len)
{
	struct rtl9300_i2c *i2c = dev_get_priv(dev);
	writel(buf, i2c->i2c_reg + rtl930x_i2c_data_off(i2c->bus));
	writel(len, i2c->i2c_reg + rtl930x_i2c_ctrl_off(i2c->bus));
	return 0;
}

// This function is used to call rtl9300_i2c_read() and it is the only function which i2c_read is called. rtl9300_i2c_read has its own implementation. According to the source.
static int rtl9300_i2c_read(struct rtl9300_i2c *i2c, u8 *buf, int len)
{
	struct rtl9300_i2c *i2c = dev_get_priv(dev);
	writel(buf, i2c->i2c_reg + rtl930x_i2c_data_off(i2c->bus));
	writel(len, i2c->i2c_reg + rtl930x_i2c_ctrl_off(i2c->bus));
	return 0;
}
};

module rtl9300_vsc_i2c_impl {
struct rtl9300_i2c_driver {
	int (*probe)(struct i2c_client *adapter);
	int (*remove)(struct i2c_client *adapter);
	int (*scan)(struct i2c_adapter *i2c);
	int (*xfer)(struct i2c_adapter *i2c, struct i2c_msg *msg, int nmsgs);
};

// This is used to call rtl9300_i2c_read() and rtl9300_i2c_write()
struct rtl9300_i2c *rtl9300_i2c_