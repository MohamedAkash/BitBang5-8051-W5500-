#include <8051.h>
#include "../include/typedefs.h"
#include "../include/periphs.h"

__sbit MOSI = P1^0;
__sbit MISO = P1^1;
__sbit SCK  = P1^2;
__sbit CS   = P1^3;

void delay_us(unsigned int us) {
    while(us--) {
        _nop_(); _nop_(); _nop_(); _nop_(); 
    }
}

void SPI_init(void) {
    MOSI = 0;
    SCK  = 0;
    CS   = 1; 
}

unsigned char SPI_transfer(unsigned char data_out) {
    unsigned char i, data_in = 0;
    for (i = 0; i < 8; i++) {
        MOSI = (data_out & 0x80); 
        data_out <<= 1;

        SCK = 1;
        delay_us(1);

        data_in <<= 1;
        if (MISO) data_in |= 0x01;

        SCK = 0;
        delay_us(1);
    }
    return data_in;
}

void SPI_write(unsigned char data) {
    CS = 0;
    SPI_transfer(data);
    CS = 1;
}

unsigned char SPI_read(void) {
    CS = 0;
    unsigned char data = SPI_transfer(0xFF);
    CS = 1;
    return data;
}

void main() {
    SPI_init();

    while (1) {
        SPI_write(0x9A);                
        unsigned char x = SPI_read();   
    }
}
