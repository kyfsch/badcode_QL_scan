
void i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t data) {
    rtl9300_i2c_write(slave_addr, reg_addr, data);
}
