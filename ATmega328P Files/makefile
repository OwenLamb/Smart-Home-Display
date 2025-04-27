# Microcontroller
MCU=atmega328p

# Compiler and Programmer
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

# Compilation flags
CFLAGS=-mmcu=$(MCU) -Os -std=c99

# Source and output files
SRC=TempSensor.c
OUT=TempSensor

# Default rule: compile and flash
all: $(OUT).hex

# Compile to ELF
$(OUT).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Convert ELF to HEX
$(OUT).hex: $(OUT).elf
	$(OBJCOPY) -O ihex $< $@

# Flash to Arduino Nano (adjust port if needed)
flash: $(OUT).hex
	$(AVRDUDE) -c arduino -p m328p -P COM5 -b 57600 -U flash:w:$(OUT).hex:i

# Clean build files
clean:
	rm -f $(OUT).elf $(OUT).hex
