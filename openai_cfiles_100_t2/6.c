
void processPendingEvents(int *queueSize) {
    if (*queueSize > 0) {
        // Process pending events on the queue
        // ...

        (*queueSize)++; // Increment queue size
    }
}


In this function, `queueSize` is passed as a pointer, allowing the function to modify its value. The function first checks if there are pending events on the queue (i.e., if `queueSize` is greater than 0). If there are events to process, the function performs the necessary processing and increments the queue size by dereferencing the pointer using the `(*queueSize)++` operation.