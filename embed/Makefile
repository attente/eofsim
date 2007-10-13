CC = avr-gcc
LDFLAGS = -mmcu=atmega168
CFLAGS = -mmcu=atmega168 -Wall -std=gnu99 -Os

all: embed.install

%.elf: %.o runtime.o
	$(CC) $(LDFLAGS) -o $@ $^

%.hex: %.elf
	objcopy -O ihex -R .eeprom $< $@

%.install: %.hex
	avrdude -F -p atmega168 -P /dev/ttyUSB0 \
	  -c stk500 -b 19200 -U flash:w:$^

clean:
	rm -f *.o *.hex *.elf
