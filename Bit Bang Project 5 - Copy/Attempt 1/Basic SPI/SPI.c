#include <stdint.h>
#include <8051.h>
#include "../include/periphs.h"
#include "../include/typedefs.h"
#include "../include/pinmap.h"
#include "../include/wiznet_defs.h"
#include "../include/uart_config.h"

void delay_us(unsigned int us) {
    while (us--) {
        _nop_(); _nop_(); _nop_(); _nop_(); 
    }
}

unsigned char SPI_Transfer(unsigned char data_out) {
    unsigned char data_in = 0;
    for (char i = 0; i < 8; i++) {
        if (data_out & 0x80) MOSI = 1;
        else MOSI = 0;
        
        SCK = 1;
        delay_us(2);

        data_in <<= 1;
        if (MISO) data_in |= 0x01;

        SCK = 0;
        delay_us(2);

        data_out <<= 1;
    }
    return data_in;
}
// data example 0b0040001101001122334455 
void main(void) {
    uart_init();
    
    MISO = 0; // Set MISO as input
    MOSI = 0; // Set MOSI as output
    SCK  = 0; // Set SCK as output
    SS   = 1; // Set SS high (inactive)

    unsigned char data_out = 0xAB;
    unsigned char data_in = SPI_Transfer(data_out);

   
    uart_write(data_in);
    
    while (1) {
        
    }
}