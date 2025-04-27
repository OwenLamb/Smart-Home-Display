#include <avr/io.h>

int main(void) {
    // Set I2C slave address to 0x08 (shifted left by 1)
    TWAR = 0x08 << 1;

    // Enable TWI, ACK, and clear TWINT to be ready
    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);

    // Set PB5 (digital pin 13 on Arduino Uno) as output for debuggingsss
    DDRB |= (1 << PB5);

    uint8_t data = 50;

    while (1) {
        // Wait until TWINT is set (meaning we've been addressed or sent a byte)
        if (TWCR & (1 << TWINT)) {
            switch (TWSR & 0xF8) {
                case 0xA8:  // SLA+R received, ACK returned
                case 0xB8:  // Data byte transmitted, ACK received
                    TWDR = data++;  // Load next byte to send
                    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);  // Clear TWINT, enable ACK
                    break;

                case 0xC0:  // Data byte transmitted, NACK received
                case 0xC8:  // Last data byte transmitted, ACK received (should be rare)
                    PORTB ^= (1 << PB5);  // Toggle LED for debug
                    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);  // Re-arm TWI
                    break;

                case 0xB0:  // SLA+R received, NACK returned (shouldn't happen normally)
                    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);  // Reset and wait
                    break;

                default:
                    // Catch-all: re-arm just in case
                    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
                    break;
            }
        }
    }

    return 0;
}
