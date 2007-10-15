LD = avr-ld
CC = avr-gcc
LDFLAGS = -mmcu=atmega168
CFLAGS = -mmcu=atmega168 -Wall -std=gnu99 -Os -Wmissing-prototypes

all: embed.hex
install: embed.install

embed.o: serial.o softserial.o pwmdecode.o main.o timer.o
	$(LD) -r -o $@ $^

%.elf: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.hex: %.elf
	objcopy -O ihex -R .eeprom $< $@

%.install: %.hex
	avrdude -F -p atmega168 -P /dev/ttyUSB0 \
	  -c stk500 -b 19200 -U flash:w:$^

clean:
	rm -f *.o *.hex *.elf
