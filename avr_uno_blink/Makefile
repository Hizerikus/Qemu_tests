MCU      = atmega328p
CC       = avr-gcc
OBJCOPY  = avr-objcopy
QEMU     = qemu-system-avr
MACHINE  = uno
HEX      = blink.hex
ELF      = blink.elf

CFLAGS   = -mmcu=$(MCU) -Os -g -Wall -Wextra -std=c11 -DF_CPU=16000000UL
LDFLAGS  = -mmcu=$(MCU)

.PHONY: all hex run debug clean

all: hex

hex: $(HEX)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): blink.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

run: $(ELF)
	$(QEMU) -M $(MACHINE) -bios $(ELF) -nographic -serial mon:stdio -no-reboot

debug: $(ELF)
	$(QEMU) -M $(MACHINE) -bios $(ELF) -display none -serial stdio -no-reboot -d int,cpu_reset -D trace.log

clean:
	rm -f $(ELF) $(HEX) *.log *.txt