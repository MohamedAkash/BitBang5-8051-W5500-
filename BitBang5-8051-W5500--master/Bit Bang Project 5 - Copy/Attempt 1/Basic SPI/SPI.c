#include <stdint.h>
#include <8051.h>
#include "../include/periphs.h"
#include "../include/typedefs.h"
#include "../include/pinmap.h"
#include "../include/wiznet_defs.h"
#include "../include/uart_config.h"

// Initialize SPI
void SPI_Init(void) {
    MOSI = 0;  // Set MOSI as output
    MISO = 1; //Set MISO as input
    SCK = 0;   // Set SCK as output
    SS = 1;    // Set SS as output (active low)
}

void SPI_Write(unsigned char data) {

    unsigned char i;
    for (i = 0; i < 8; i++) {
        MOSI = (data & 0x80) ? 1 : 0;  // Send MSB first
        data <<= 1;                    // Shift data left
        SCK = 1;                       // Generate clock pulse
        SCK = 0;
    }
}

void SPI_WriteShort(unsigned short data) {
    unsigned short i;
    for (i = 0; i < 16; i++) {
        MOSI = (data & 0x8000) ? 1 : 0;  // Send MSB first
        data <<= 1;                    // Shift data left
        SCK = 1;                       // Generate clock pulse
        SCK = 0;
    }
}

// Receive a byte via SPI
unsigned char SPI_Read(void) {
    unsigned char i, data = 0;
    for (i = 0; i < 8; i++) {
        data <<= 1;        // Shift data left
        SCK = 1;           // Generate clock pulse
        if (MISO)          // Read MISO
            data |= 0x01;  // Set LSB if MISO is high
        SCK = 0;
    }
    return data;
}
