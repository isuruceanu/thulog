# WinAVR cross-compiler toolchain is used here
CC = avr-gcc
OBJCOPY = avr-objcopy
DUDE = avrdude
MCU=attiny2313
SIZE = avr-size
F_CPU = 12000000


# If you are not using ATtiny2313 and the USBtiny programmer, 
# update the lines below to match your configuration
CFLAGS = -Wall -Os -funsigned-char -Iusbdrv -mmcu=$(MCU)
CFLAGS += -DF_CPU=$(F_CPU)
#CFLAGS += -fwhole-program
#CFLAGS += -fno-inline-small-functions
#CFLAGS += -ffunction-sections
#CFLAGS += -fdata-sections 
#CFLAGS += -fno-split-wide-types
#CFLAGS += -Wundef

OBJFLAGS = -j .text -j .data -O ihex
DUDEFLAGS = -p $(MCU) -c usbasp -P usb -v -D

# Object files for the firmware (usbdrv/oddebug.o not strictly needed I think)
OBJECTS = dht.o usbdrv/usbdrv.o usbdrv/usbdrvasm.o main.o

# By default, build the firmware and command-line client, but do not flash
all: main.hex sizeafter

# With this, you can flash the firmware by just typing "make flash" on command-line
program: main.hex
	$(DUDE) $(DUDEFLAGS) -U flash:w:$<

# Housekeeping if you want it
clean:
	#$(RM) *.o *.hex *.elf usbdrv/*.o
	

# From .elf file to .hex
%.hex: %.elf
	$(OBJCOPY) $(OBJFLAGS) $< $@

# Main.elf requires additional objects to the firmware, not just main.o
main.elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Without this dependance, .o files will not be recompiled if you change 
# the config! I spent a few hours debugging because of this...
$(OBJECTS): usbdrv/usbconfig.h

# From C source to .o object file
%.o: %.c	
	$(CC) $(CFLAGS) -c $< -o $@

# From assembler source to .o object file
%.o: %.S
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

ELFSIZE = $(SIZE) --mcu=$(MCU) --format=avr main.elf

sizeafter:
	@if test -f main.elf; then echo; echo Size after; $(ELFSIZE); \
	2>/dev/null; echo; fi

