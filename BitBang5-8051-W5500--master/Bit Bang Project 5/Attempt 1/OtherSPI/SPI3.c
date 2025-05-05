#include <8051.h>            // SDCC 8051 SFR definitions
__sbit __at (0x90) MOSI;    // P1.0
__sbit __at (0x91) MISO;    // P1.1
__sbit __at (0x92) SCLK;    // P1.2
__sbit __at (0x93) CS;      // P1.3 (Chip Select)


// Initialize SPI lines (call once)
void SPI_Init(void) {
    SCLK = 0;   // Idle low (CPOL=0)
    CS = 1;     // CS high (deselected)
}

// Send and receive one byte via SPI (mode 0)
unsigned char spi_transfer(unsigned char out) {
    unsigned char i;
    unsigned char in = 0;
    for (i = 0; i < 8; i++) {
        // Output next bit on MOSI (MSB first)
        MOSI = (out & 0x80) ? 1 : 0;
        out <<= 1;
        // Pulse SCLK high (rising edge)
        SCLK = 1;
        // Sample MISO into LSB of 'in'
        in <<= 1;
        if (MISO) in |= 0x01;
        // Bring SCLK low (falling edge, ready for next bit)
        SCLK = 0;
    }
    return in;
}

// Write one byte to W5500 (common register block)
void W5500_WriteReg(unsigned int addr, unsigned char data) {
    unsigned char addr_hi = (addr >> 8) & 0xFF;
    unsigned char addr_lo = addr & 0xFF;
    unsigned char ctrl = (0 << 3) | (0 << 2) | 0x00; 
    // BSB=0x00 (common regs), R/W=0 (write), OM=00 (VDM)
    CS = 0;                            // Select W5500
    spi_transfer(addr_hi);             // Address high byte
    spi_transfer(addr_lo);             // Address low byte
    spi_transfer(ctrl);                // Control byte (write)
    spi_transfer(data);                // Data byte
    CS = 1;                            // Deselect W5500
}

// Read one byte from W5500 (common register block)
unsigned char W5500_ReadReg(unsigned int addr) {
    unsigned char addr_hi = (addr >> 8) & 0xFF;
    unsigned char addr_lo = addr & 0xFF;
    unsigned char ctrl = (0 << 3) | (1 << 2) | 0x00; 
    // BSB=0x00 (common), R/W=1 (read), OM=00
    unsigned char val;
    CS = 0;                            // Select
    spi_transfer(addr_hi);
    spi_transfer(addr_lo);
    spi_transfer(ctrl);
    val = spi_transfer(0x00);          // Dummy byte to receive data
    CS = 1;                            // Deselect
    return val;
}

void UART_Init(void) {
    TMOD |= 0x20;        // Timer1, mode 2 (auto-reload)
    TH1 = 0xFD;          // 9600 bps @11.0592MHz
    SCON = 0x50;         // UART mode 1, REN=1
    TR1 = 1;             // Start Timer1
}

void UART_PutChar(char c) {
    SBUF = c;
    while (!TI);         // Wait for transmit complete
    TI = 0;
}

void print_hex(unsigned char byte) {
    static const char hex[] = "0123456789ABCDEF";
    UART_PutChar(hex[byte >> 4]);
    UART_PutChar(hex[byte & 0x0F]);
}

void main(void) {
    unsigned char version;

    SPI_Init();
    UART_Init();

    // Read W5500 version register (0x0039) and print in hex
    version = W5500_ReadReg(0x0039);
    print_hex(version);
    UART_PutChar('\r');
    UART_PutChar('\n');

    while (1) {
        // Loop forever. In a real app you would proceed to networking code.
    }
}
