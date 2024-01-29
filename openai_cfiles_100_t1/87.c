
void resumeEthernetAdapter(void) {
    // Set hardware to detect wake-up from hibernation
    HW_WAKEUP_DETECT = 1;

    // Enable ethernet transceivers
    ETHERNET_TRANSCEIVERS_ENABLE = 1;
}
