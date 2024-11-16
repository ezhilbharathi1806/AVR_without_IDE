build:
	avr-gcc -mmcu=atmega328p -Wall -Os -o led.elf main.c
	avr-objcopy -j .text -j .data -O ihex led.elf led.hex