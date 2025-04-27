// DDRB controls what ports are input and output
// unsigned char = 8 bits
#define DDRB (*(volatile unsigned char*)0x24)

// PORTB dictactes which pins are turned on for either reading or writing
#define PORTB (*(volatile unsigned char*)0x25)

// PB5 is the pin that the internal LED is hooked up to
#define PB5 (1 << 5)

// __asm__ declares an assembly command
// nop = no-operation, it utilizes exactly one clock cycle
// Currently blinks way too much so looking into timers...
void delay(unsigned int ms) {
    for (unsigned int i = 0; i < ms * 1000; i++) {
        __asm__ __volatile__("nop");
    }
}

int main() {
    // Turn on PB5 pin
    // DDRB probably = 0000 0000 and PB5 = 0010 0000
    DDRB |= PB5;

    while(1) {
        // Toggle pin 5
        PORTB ^= PB5;
        delay(500);
    }
    
    return 0;
}