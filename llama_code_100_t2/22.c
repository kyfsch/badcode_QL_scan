// This function is used to extract the configuration from the AW9523 device. The function extracts the configuration value from the AW9523 device based on the pin and the parameter.  The function starts by obtaining the enum pin_config_param.
static int aw9523_pconf_get(struct pinctrl_dev *pctldev, unsigned int pin,
			     unsigned long *config)
{
	struct aw9523_pinctrl *aw9523_info;
	fpio_reg_t *fpio_base;
	uint32_t reg_val = 0, reg_id, reg_bitmask;
	uint32_t param = *config;
	enum pin_config_param pparam;

	aw9523_info = pinctrl_dev_get_drvdata(pctldev);
	fpio_base = aw9523_info->fpio_base;
	param &= 0xff;
	pparam = (enum pin_config_param)param;

	reg_id = fpio_base->pconf_pid[pin];
	reg_bitmask = fpio_base->pconf_pbid[pin];
	reg_val = reg_read(reg_id);
	reg_val &= reg_bitmask;

	switch (pparam) {
		case pconf_mode:
			*config = reg_val;
			break;
		case pconf_drive:
			*config = reg_val & pconf_drive_mask;
			break;
		case pconf_pullup:
			if ((reg_val & pullup_en_mask) == (pullup_en_mask))
				*config = 1;
			else
				*config = 0;
			break;
		case pconf_pulldown:
			if ((reg_val & pulldown_en_mask) == (pulldown_en_mask))
				*config = 1;
			else
				*config = 0;
			break;
		case pconf_schmitt:
			if ((reg_val & schmitt_en_mask) == (schmitt_en_mask))
				*config = HIGH;
			else
				*config =