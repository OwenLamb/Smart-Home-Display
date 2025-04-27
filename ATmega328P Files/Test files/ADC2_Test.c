#include <avr/io.h>

int main(void) {
    // Set reference voltage to AVcc with external capacitor at AREF pin
    ADMUX = (1 << REFS0); // REFS1=0, REFS0=1, MUX[3:0]=0000 for ADC0

    // Enable ADC, enable auto trigger, start conversion, set prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Set ADC Auto Trigger Source to Free Running mode
    ADCSRB &= ~(1 << ADTS2) & ~(1 << ADTS1) & ~(1 << ADTS0);

    // Set PB5 (digital pin 13 on Arduino Uno) as output
    DDRB |= (1 << PB5);

    while (1) {
        // Read ADC value
        uint16_t value = ADC; // ADC is a 16-bit macro combining ADCL and ADCH

        if (value >= 500) {
            PORTB |= (1 << PB5);  // Turn LED on
        } else {
            PORTB &= ~(1 << PB5); // Turn LED off
        }
    }

    return 0;
}
