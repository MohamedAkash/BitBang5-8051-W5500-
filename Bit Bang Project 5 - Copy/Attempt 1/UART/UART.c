#include <stdint.h>
#include <8051.h>
#include "../include/periphs.h"
#include "../include/typedefs.h"

// SPI pin defines
#define MISO P1_0 // pin 10
#define MOSI P1_1 // pin 11
#define SS   P1_2 // pin 12
#define SCK  P1_3 // pin 13

// UART pins (hardware fixed)
#define RXD  P3_0  // pin 30
#define TXD  P3_1  // pin 31

// Choose baud rate
#define UART_BAUD 9600 // 9600 or 19200

void uart_init(void) {
    uint8_t reload;
    
    // Compute TH1 reload for 6T mode:
    // Baud = Fosc / (6 * (256 - TH1) * 32)
    // For Fosc = 11.0592MHz:
    // 19200 → TH1 = 256 - (11059200/(6*19200*32)) ≈ 253 = 0xFD
    //  9600 → TH1 = 256 - (11059200/(6* 9600*32)) ≈ 250 = 0xFA
    #if UART_BAUD == 19200
        reload = 0xFD;
    #elif UART_BAUD == 9600
        reload = 0xFA;
    #else
        #error "UART_BAUD must be 9600 or 19200"
    #endif

    TMOD   |= 0x20;    // Timer1, mode 2 (8-bit auto-reload)
    TH1     = reload;  // set reload for desired baud
    TL1     = reload;  // initialize TL1 to the same
    TR1     = 1;       // start Timer1
    SCON    = 0x50;    // UART mode 1 (8-bit), REN=1
    TI      = 0;       // clear transmit flag
    RI      = 0;       // clear receive flag
}

void uart_write(uint8_t c) {
    SBUF = c;
    while (!TI);  // wait for transmit complete
    TI = 0;
}

uint8_t uart_read(void) {
    while (!RI);  // wait for receive complete
    RI = 0;
    return SBUF;
}

void send_string(const char *s) {
    while (*s) uart_write(*s++);
}

void main(void) {
    uint8_t ch;

    uart_init();

    // Banner on startup
    send_string("\r\n[UART READY at ");
    #if UART_BAUD == 19200
        send_string("19200");
    #else
        send_string("9600");
    #endif
    send_string(" bps]\r\n");

    // Echo loop
    while (1) {
        ch = uart_read();
        uart_write('[');
        uart_write(ch);
        uart_write(']');
    }
}
