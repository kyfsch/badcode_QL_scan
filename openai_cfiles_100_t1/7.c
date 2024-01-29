
#define NL_MSG_TYPE_SWITCH_LINK_SPEED  0x01

typedef struct {
    uint8_t portNumber;
    uint32_t linkSpeed;
} SWITCH_LINK_SPEED;

void encode_switch_link_speed_nl_message(const SWITCH_LINK_SPEED *data, uint8_t *buffer, size_t buffer_size) {
    if (buffer_size < sizeof(uint8_t) + sizeof(uint32_t)) {
        // Buffer size insufficient
        return;
    }
  
    // Set NL message type to SWITCH_LINK_SPEED
    buffer[0] = NL_MSG_TYPE_SWITCH_LINK_SPEED;
  
    // Copy port number to buffer
    buffer[1] = data->portNumber;
  
    // Copy link speed to buffer (big endian)
    buffer[2] = (data->linkSpeed >> 24) & 0xFF;
    buffer[3] = (data->linkSpeed >> 16) & 0xFF;
    buffer[4] = (data->linkSpeed >> 8) & 0xFF;
    buffer[5] = data->linkSpeed & 0xFF;
}


In this code, we first define the NL message type for SWITCH_LINK_SPEED as 0x01. Then, we define the structure of SWITCH_LINK_SPEED, which consists of a `portNumber` (8-bit) and `linkSpeed` (32-bit).

The `encode_switch_link_speed_nl_message` function takes the `data` structure, `buffer` to store the encoded message, and `buffer_size` as input parameters. It checks if the buffer size is sufficient to hold the entire encoded message.

If the buffer size is sufficient, it encodes the structure as follows: sets the first byte of the buffer to the NL message type, copies the port number to the buffer, and then copies the link speed to the buffer in big-endian byte order (most significant byte first).