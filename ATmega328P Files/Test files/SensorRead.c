/*
ADC Control and Status register B
Bit 7 - Null
Bit 6 - ACME enable bit
Bit 5,4,3 - Null
Bit 2 - ADTS2
Bit 1 - ADTS1
Bit 0 - ADTS0

Select bits are for selecting which ADC input goes into the ADC
*/

#define ADCSRB (*(volatile unsigned char*)0x7B)
#define ADC0 0b01000000

/*
Analog Comparator Control and Status Register
Bit 7,6 - REFS1,REFS0: Select voltage reference for ADC. 0b01 sets it to onboard power supply
Bit 5 - ADLAR: affects the presentation of the ADC conversion result
Bit 4 - Null
Bit 3,2,1,0 - Mux Select bits, ADC0 = 0000
*/
#define ADMUX (*(volatile unsigned char*)0x7C)
#define ADC0 0b01000000