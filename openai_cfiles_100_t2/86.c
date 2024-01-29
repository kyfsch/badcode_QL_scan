
void writeBit(unsigned char bitValue) {
  // Set the port pin as an output
  // Replace PORT_NAME and PIN_NUMBER with the appropriate values
  DDR_PORT_NAME |= (1 << DDR_PIN_NUMBER);

  // Set the bit value on the output pin
  if (bitValue) {
    // Set the pin high
    PORT_PORT_NAME |= (1 << PORT_PIN_NUMBER);
  } else {
    // Set the pin low
    PORT_PORT_NAME &= ~(1 << PORT_PIN_NUMBER);
  }

  // Delay for the required time to write the bit
  // Replace DELAY_TIME_US with the appropriate value in microseconds
  _delay_us(DELAY_TIME_US);
}
