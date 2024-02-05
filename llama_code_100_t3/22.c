// This function is used to extract the configuration from the AW9523 device. The function extracts the configuration value from the AW9523 device based on the pin and the parameter.  The function starts by obtaining the enum pin_config_param.
static int aw9523_pconf_get(struct pinctrl_dev *pctldev, unsigned int pin,
				unsigned long *config);
// The function returns one of the possible modes that can be assigned to the specified pin. 
// pin_config_param, and then checks if an alternative mode can be returned. The function checks the 
// pin configuration parameter and the mode parameter of the driver. If the configuration data does NOT match the 
// configuration parameter, it gets the alternative mode, and saves. 
static int aw9523_get_config_param(struct pinctrl_dev *pctldev,
				const char *conffile,
				unsigned long *configparam,
				struct pinctrl_map **map,
				unsigned int *map_cnt);

/* The below mentioned functions are used to define the driver function for AW9523 device. */
// This function maps the pin names passed in the user mode to the hardware pin number. 
static const struct pinctrl_pin_desc aw9523_pins[] = {
	AW_PIN(0, "GPIO_0"),
	AW_PIN(1, "GPIO_1"),
	AW_PIN(2, "GPIO_2"),
	AW_PIN(3, "GPIO_3"),
	AW_PIN(4, "GPIO_4"),
	AW_PIN(5, "GPIO_5"),
	AW_PIN(6, "GPIO_6"),
	AW_PIN(7, "GPIO_7"),
	AW_PIN(8, "GPIO_8"),
	AW_PIN(9, "GPIO_9"),
	AW_PIN(10, "GPIO_10"),
	AW_PIN(11, "GPIO_11"),
	AW_PIN(12, "GPIO_12"),
	AW_PIN(13, "GPIO_13"),
	AW_PIN(14, "GPIO_14"),
	AW_PIN(15, "GPIO_15"),