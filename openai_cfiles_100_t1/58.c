#include <phy_drv.h>

int psb6970_phy_init(void)
{
    // Reset the PHY
    phy_drv_reset();

    // Set the PHY mode
    phy_drv_set_mode(PHY_MODE_ETH);

    // Enable auto-negotiation
    phy_drv_enable_auto_neg();

    // Wait for auto-negotiation to complete
    while (!phy_drv_auto_neg_complete())
    {
        // Add delay or other code as needed
    }

    // Read and configure PHY status
    uint16_t status = phy_drv_get_status();

    // Configure PHY settings based on status

    // Register the PHY driver
    phy_drv_register(PHY_MODEL_PSB6970, psb6970_phy_ops);

    return 0;
}
