
void writeToMailbox(char *dllInfo) {
    // Mailbox address
    volatile uint32_t *mailbox = (volatile uint32_t *)0x12345678; // Replace with actual mailbox address
    
    // Write DLL information
    for (int i = 0; dllInfo[i] != '\0'; i++) {
        // Check mailbox status
        while ((*(mailbox + 1) & 0x80000000) != 0) {}
        
        // Write character to mailbox data register
        *mailbox = (uint32_t)dllInfo[i];
    }
}
