#include <stdint.h>

/* Define a structure for DSL link settings */
typedef struct {
    uint32_t tx_rate; // Transmission rate in Kbps
} DSL_Settings;

/* Define a structure for ATM link settings */
typedef struct {
    uint32_t rx_rate; // Reception rate in Kbps
} ATM_Settings;

/* Function to set the DSL transmission rate */
void setDSLLinkRate(DSL_Settings* dslSettings, uint32_t txRate) {
    if (dslSettings != NULL) {
        dslSettings->tx_rate = txRate;
    }
}

/* Function to set the ATM reception rate */
void setATMLinkRate(ATM_Settings* atmSettings, uint32_t rxRate) {
    if (atmSettings != NULL) {
        atmSettings->rx_rate = rxRate;
    }
}

/* Example usage of the above functions */
int main() {
    DSL_Settings dslSettings;
    ATM_Settings atmSettings;

    setDSLLinkRate(&dslSettings, 2048); // Set DSL tx rate to 2048 Kbps
    setATMLinkRate(&atmSettings, 1024); // Set ATM rx rate to 1024 Kbps
    
    /* Your code that uses dslSettings and atmSettings goes here */
    
    return 0;
}
