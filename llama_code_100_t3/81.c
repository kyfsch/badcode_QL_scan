// This function is used to determine whether the board is PANDA..
static int __init panda_probe(void)
{
    int board_id;
    
    board_id = PANDA_ID_G2;

    if(system_is_panda() && !system_is_release())
    {
        if(device_board_id() == PANDA)
        {
            board_id = (panda_id_read(2) <= 0X6);
        }
    }
    return board_id;

}

// GPIO init for PANDA
// For PANDA, both GPIOA and GPIOB set the same configuration..
static int k_gpio_config_init(void)
{
    // GPIO configuration
    panda_pin_config_output(GPIO_A, GPIO_FN_AIN1, -1);
    panda_pin_config_output(GPIO_A, GPIO_FN_AIN2, -1);


    panda_pin_config_output(GPIO_A, GPIO_FN_AOUT1, -1);
    panda_pin_config_output(GPIO_A, GPIO_FN_AOUT2, -1);

    panda_pin_config_input(GPIO_B, GPIO_FN_BAT_LVL_WARN, -1);

    panda_pin_config_output(GPIO_A, GPIO_FN_EIN_1, -1);
    panda_pin_config_output(GPIO_A, GPIO_FN_EIN_0, -1);

    panda_pin_config_output(GPIO_A, GPIO_FN_AOUT_1, -1);
    panda_pin_config_output(GPIO_A, GPIO_FN_AOUT_2, -1);

    panda_pin_config_input(GPIO_B, GPIO_FN_EOUT_1, -1);
    panda_pin_config_input(GPI