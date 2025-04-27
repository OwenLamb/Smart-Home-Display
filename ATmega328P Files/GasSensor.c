#include <avr/io.h>

int main(void) {
    // Set I2C slave address to 0x08 (shifted left by 1)
    TWAR = 0x09 << 1;

    // Enable TWI, ACK, and clear TWINT to be ready
    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);

    // Set PB5 (digital pin 13 on Arduino Uno) as output for debugging
    DDRB |= (1 << PB5);

    // Set reference voltage to AVcc with external capacitor at AREF pin
    ADMUX = (1 << REFS0); // REFS1=0, REFS0=1, MUX[3:0]=0000 for ADC0
    
    uint16_t value = 0;
    
    // Enable ADC, enable auto trigger, start conversion, set prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Set ADC Auto Trigger Source to Free Running mode
    ADCSRB &= ~(1 << ADTS2) & ~(1 << ADTS1) & ~(1 << ADTS0);

    // Set PB5 (digital pin 13 on Arduino Uno) as output
    DDRB |= (1 << PB5);

    while (1) {
        // Wait until TWINT is set (meaning we've been addressed or sent a byte)
        value = ADC; // ADC is a 16-bit macro combining ADCL and ADCH
        if (TWCR & (1 << TWINT)) {
            switch (TWSR & 0xF8) {
                case 0xA8:  // SLA+R received, ACK returned
                case 0xB8:  // Data byte transmitted, ACK received
                    if (value >= 500) {
                        TWDR = 1;  // Load next byte to send
                        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);  // Clear TWINT, enable ACK
                        PORTB |= (1 << PB5);  // Turn LED on
                    } else {
                        TWDR = 0;  // Load next byte to send
                        TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);  // Clear TWINT, enable ACK
                        PORTB &= ~(1 << PB5); // Turn LED off
                    }
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
