
void flushPacketBuffers(struct PacketBuffers *a) {
    // Assume struct PacketBuffers has an array of buffers called 'buffers'
    // and a variable 'bufferCount' indicating the number of buffers

    for (int i = 0; i < a->bufferCount; i++) {
        // Assume 'flushBuffer' is a function that flushes a single buffer
        flushBuffer(&(a->buffers[i]));
    }
}
