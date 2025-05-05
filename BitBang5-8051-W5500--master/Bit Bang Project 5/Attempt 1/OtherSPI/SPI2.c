#include <stdint.h>

// Replace these with your MCU’s GPIO register definitions
#define MOSI_HIGH()   (/* set MOSI pin high */)
#define MOSI_LOW()    (/* set MOSI pin low  */)
#define MISO_READ()   (/* read and return MISO pin state */)
#define SCLK_HIGH()   (/* set SCLK pin high */)
#define SCLK_LOW()    (/* set SCLK pin low  */)
#define CS_ENABLE()   do { /* pull CS low */ } while(0)
#define CS_DISABLE()  do { /* pull CS high*/ } while(0)

// Tiny delay to meet setup/hold timing (tunable)
static inline void spi_delay(void) {
    for (volatile int i = 0; i < 10; i++);  // ~tunable nop-loop
}

// Initialize GPIOs: MOSI, SCLK, CS as outputs; MISO as input
void spi_init(void) {
    CS_DISABLE();
    SCLK_LOW();       // Idle low for CPOL=0
    // configure MOSI, SCLK, CS as outputs and MISO as input here
}

// Transfer one byte over SPI mode 0 (bit-banged)
uint8_t spi_transfer(uint8_t data) {
    uint8_t received = 0;
    CS_ENABLE();
    for (int i = 0; i < 8; i++) {
        // Output MSB first
        if (data & 0x80) MOSI_HIGH();
        else              MOSI_LOW();
        spi_delay();

        // Clock high: sample MOSI on slave, read MISO on master
        SCLK_HIGH();
        spi_delay();

        received <<= 1;
        if (MISO_READ()) received |= 0x01;

        // Clock low: finish the cycle
        SCLK_LOW();
        spi_delay();

        data <<= 1;
    }
    CS_DISABLE();
    return received;
}
