/* 
Bit 7 - REFS1 set to 0 1 for AVcc
Bit 6 - REFS0
Bit 5 - ADLAR
Bit 4 - NULL
Bit 3-0 - Mux select - 0000 for A0
*/
#define ADMUX (*(volatile unsigned char*) 0x7C)

/* ADC Control and Status Register A
Bit 7 - ADEN ADC enable
Bit 6 - ADSC start conversion
Bit 5 - ADATE ADC auto trigger enable
Bit 4 - ADIF ADC Interrupt flag
Bit 3 - ADIE ADC interrupt enable
Bit 2-0 - ADC Prescaler select bits, i'm setting to 128 aka 0b111
*/
#define ADCSRA (*(volatile unsigned char*) 0x7A)
#define ADSC (1 << 6)

/* ADC Control and Status Register B
Bit 7 - Null
Bit 6 - ACME
Bit 5-3 - Null
Bit 2-0 - ADTS(2-0) ADC Auto Trigger Source, Free running mode = 000
*/
#define ADCSRB (*(volatile unsigned char*) 0x7B)

// Bit 7-0 for reading lower part of the ADC data register
#define ADLAR_Lower (*(volatile unsigned char*) 0x78)
//only is in bits 0 and 1, rest are null
#define ADLAR_Upper (*(volatile unsigned char*) 0x79)


// DDRB controls what ports are input and output
// unsigned char = 8 bits
#define DDRB (*(volatile unsigned char*)0x24)

// PORTB dictactes which pins are turned on for either reading or writing
#define PORTB (*(volatile unsigned char*)0x25)

// PB5 is the pin that the internal LED is hooked up to
#define PB5 (1 << 5)

int main(){

    //initialize ADC
    ADMUX = 0b01000000;
    ADCSRA = 0b11100111;
    ADCSRB = 00000000;

    //initialize LED pin
    DDRB |= PB5;

    while(1){
        int value = ADLAR_Lower;
        value |= (ADLAR_Upper << 8);

        if(value >= 500){
            PORTB |= PB5;
        } else {
            PORTB &= ~PB5;
        }
    }
    return 0;
}