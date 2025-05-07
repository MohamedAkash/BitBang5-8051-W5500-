#include <8051.h>
#include <stdio.h>
#include "w5500.h"
#include "spi.h"

// Serial communication functions
void serial_init(unsigned int baud) {
    SCON = 0x50;    // Mode 1: 8-bit UART, enable receiver
    TMOD |= 0x20;   // Timer 1 in mode 2 (8-bit auto-reload)
    TH1 = 256 - (11059200UL/12/32)/baud; // Set baud rate
    TR1 = 1;        // Start timer 1
    TI = 1;         // Set TI to send first char
}

void serial_write(char c) {
    SBUF = c;
    while(!TI);
    TI = 0;
}

char serial_read() {
    while(!RI);
    RI = 0;
    return SBUF;
}

// Main program
void main() {
    // Initialize communication interfaces
    serial_init(9600);
    spi_init();
    w5500_init();

    printf("System initialized\r\n");

    while(1) {
        // Main program loop
        if(RI) {
            char c = serial_read();
            serial_write(c); // Echo back
        }
    }
}
