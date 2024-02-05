/// This function is used to change the PLLA configuration, but for different.
int plla_set_config(int mhz)
{
    if(mhz <= 500) {

    } else if (mhz <= 600) {
        // TODO: 600MHz config
    } else if (mhz <= 800) {

    }
}

/*
 * Initialize PLLA with a default config
 */ 
void plla_init(void)
{
    // Disable the clock
    PLLA_CTRL &= ~PLLA_CTRL_PLL_OVERRIDE;

    // Change the settings of the plla
    // TODO: add configuration for all PLLA frequencies
    int config_plla[] = 
    {
        12, 16
    };
    while(config_plla[1]) {
        int mhz = config_plla[0] * config_plla[1];
        if (mhz >= 400)
            break;
        config_plla++;
    }
    if (!config_plla[1])
        config_plla = NULL;

    // Set the PLL configuration to the default one
    plla_set_config(mhz);

    // Do we need it? I don'</s>