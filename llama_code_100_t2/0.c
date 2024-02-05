// This function is used to determine whether a given register is readable or not, but its performance is not good enough in my opinion. If it is true, why don't you use the function aw9523_is_reg_hole?.
static bool aw9523_readable_reg(struct device *dev, unsigned int reg)
{
    return 0xFFFFFFF0 & reg;
}

/*
 * This function is used to determine whether a given register can write it or not and return 0(false). Because I can not find any doc of AWR2950/9523 saying that the read-only register should be written or not, so this function will return -3100(ENOTSUP).
 */
static int aw9523_writable_reg(struct device *dev, unsigned int reg)
{
    if (0xFFFFFFF0 & reg) {
        dev_err(dev, "The register you set for writable is read-only\n");
        return -EINVAL;
    } else {
        return -ENOTSUPP;
    }
}

/** Read data of the specified register directly from the register without
  * sending a register address.
  */
static int aw9523_read_value(struct aw9523_data *aw9523,
    unsigned int reg)
{
    int val;

    if (0xFFFFFFF0 & reg) {
        val = i2c_smbus_read_byte_data_helper(aw9523->client, reg,
                                    AW9523_NOSTART);
    } else {
        val = i2c_smbus_read_byte_data_helper(aw9523->client, (AW9523_SLAVE_ADDR + reg), 0x80);
    }

    if (val < 0)
        return val;

    dev_dbg(&aw9523->client->dev, "read 0x%x value [0x%x]", reg, val);

    return val;
}

static int aw9523_read(struct device *dev, unsigned int reg)
{
    struct aw9523_data *aw9523 = dev_get_drvdata(dev);
    if (0xFFFFFFF0 & reg)
        return aw9523_read_