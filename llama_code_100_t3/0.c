// This function is used to determine whether a given register is readable or not, but its performance is not good enough in my opinion. If it is true, why don't you use the function aw9523_is_reg_hole?.
static bool aw9523_readable_reg(struct device *dev, unsigned int reg)
{
    bool ret = false;
    struct aw9523_dev *aw9523 = dev_get_drvdata(dev);

    if ((reg > AW9523_MAX_REG_NUM) || (reg < AW9523_MIN_REG_NUM) || (AW9523_HOLD1_REGS_NUM > reg))
    {
        return false;
    }


    if ((uint8_t)AW9523_CONTROL1_REGS_NUM <= reg)
    {
        ret = !(IS_FLD_SET_BY_VAL(aw9523->config->pinHoleMask, (0x80 >> (reg - (uint8_t)AW9523_CONTROL1_REGS_NUM))));
    }
    else if ((uint8_t)((AW9523_STATUS_REGS_NUM + AW9523_CONTROL1_REGS_NUM) - 1) > reg)
    {
        ret = !(IS_FLD_SET_BY_VAL(aw9523->config->pinHoleMask, (0x80 >> (reg - (uint8_t)((AW9523_STATUS_REGS_NUM + AW9523_CONTROL1_REGS_NUM) - 1)))));
    }
    else
    {
        switch ((uint32_t)reg)
        {
        case AW9523_STATUS_REGS_NUM:
        case (uint32_t)(AW9523_STATUS_REGS_NUM + 1):
        case (uint32_t)(AW9523_STATUS_REGS_NUM + 2):
        case (uint32_t)(AW9523_STATUS_REGS_NUM + 3):
        case (uint32_t)(AW9523_STATUS_REGS_NUM + 4):
        case (uint32_t)(AW9523_STATUS_REGS_NUM