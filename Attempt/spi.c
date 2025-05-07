#include "spi.h"
#include <8051.h>

void spi_init(void) {
    // Configure SPI pins
    P1 = 0x00; // Set all P1 pins to output
    P1_0 = 1;  // SCK high
    P1_1 = 1;  // MISO input
    P1_2 = 0;  // MOSI low
    P1_3 = 1;  // SS high
}

void spi_select(void) {
    P1_3 = 0; // SS low
}

void spi_deselect(void) {
    P1_3 = 1; // SS high
}

uint8_t spi_transfer(uint8_t data) {
    uint8_t received = 0;
    for (int i = 0; i < 8; i++) {
        P1_2 = (data & 0x80) ? 1 : 0; // Set MOSI
        P1_0 = 0; // SCK low
        data <<= 1;
        P1_0 = 1; // SCK high
        received <<= 1;
        received |= P1_1; // Read MISO
    }
    return received;
}

void spi_write(uint8_t data) {
    spi_transfer(data);
}

uint8_t spi_read(void) {
    return spi_transfer(0xFF);
}
