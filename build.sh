#! /bin/sh

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -std=c99 -lc -c -o $1\.o $1\.c
avr-gcc -mmcu=atmega328p $1\.o -o $1
avr-objcopy -O ihex -R .eeprom $1 $1\.hex
