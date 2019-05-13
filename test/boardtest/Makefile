PORT = /dev/ttyACM0
DEVICE = atmega328
SPEED = 16000000
PROGRAMMER = arduino
MAIN = shiftregtest

CC = avr-gcc
O ?= -Os

all: clean $(MAIN)

%.o: %.c
	$(CC) $(O) $(CFLAGS) $(LIBS) -DF_CPU=$(SPEED) -mmcu=$(DEVICE) -c $<

%.elf: %.o
	$(CC) -DF_CPU=$(SPEED) -mmcu=$(DEVICE) -o $@ $<

%.hex: %.elf
	avr-objcopy -O ihex $< $@

%.s: %.c
	$(CC) $(O) $(CFLAGS) $(LIBS) -DF_CPU=$(SPEED) -mmcu=$(DEVICE) -S $<

asm: $(MAIN).s ;

flash: $(MAIN).hex
	avrdude -c $(PROGRAMMER) -p $(DEVICE) -P $(PORT) -U flash:w:$(MAIN).hex

$(MAIN): $(MAIN).hex ;

clean:
	rm -f *.o *.elf *.hex *.s

.PRECIOUS: %.o %.elf
.PHONY: clean
