// This function is used to call rtl9300_i2c_write() and it is the only function which i2c_write is called. rtl9300_i2c_write has its own implementation. According to the source.
static int rtl9300_i2c_write(struct rtl9300_i2c *i2c, u8 *buf, int len)
{
    if (strstr(i2c->dev->driver->name, "i2cbus")) {
        int buf_len = 0;
        struct i2c_client *i2cdev = i2c->i2c;

        buf_len = len - 1;

        while (buf_len > 255) {
            if (strstr(i2cdev->adapter->name, "i2c-mt9303")) {
                if (i2c_write(i2cdev, buf, 255))
                    return 0;
            } else {
                if (i2c_write(i2cdev, buf, 32))
                    return 0;
            }
            buf_len -= 255;
            buf += 255;
        }
        if (i2c_write(i2cdev, buf, 0xFF & buf_len))
            return 0;
    } else {
        int buf_len = 0;
        const struct rtl930x_i2c_data *data = &rtl930x_i2c_data[i2c->data_index];
        u32 offset = i2c->index * 0x100 + data->i2c_reg;
        struct rtl838x_soc_priv *priv = dev_get_priv(i2c->dev);
        u32 i = 0;

        //buf_len = len-1;

        buf_len = len;
        if (!(buf_len % 4))
            buf_len--;
        for (i=0; i < buf_len; i++) {
            if (i%4 == 0 ) {
                write_reg(priv->mac_dev, offset+i, buf[i] << 24);
                printk("i2c_write_mac buf[%d] = %x\n", i, (buf[i] << 24));
            } else if (i%4 == 1 ) {