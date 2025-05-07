#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// SPI Pins configuration for 8051
#define SPI_SCK  P1_2
#define SPI_MISO P1_1
#define SPI_MOSI P1_0
#define SPI_SS   P1_3

// Function prototypes
void spi_init(void);
void spi_select(void);
void spi_deselect(void);
uint8_t spi_transfer(uint8_t data);
void spi_write(uint8_t data);
uint8_t spi_read(void);

#endif
