
void setMldv2Operation(int port, int operation) {
    // Enable the specified MLDv2 operation function
    switch(operation) {
        case 0:
            // Enable Operation 0
            // ...
            break;
        case 1:
            // Enable Operation 1
            // ...
            break;
        case 2:
            // Enable Operation 2
            // ...
            break;
        // Add more cases for other supported MLDv2 operations
        default:
            // Invalid operation
            // Handle the error if necessary
            break;
    }
}
