#include "w5500.h"
#include "spi.h"
#include <stdint.h>

void w5500_init(void) {
    // Initialize SPI interface
    spi_init();
    
    // Reset W5500
    w5500_write(W5500_MR, 0x80);
    
    // Configure W5500 registers
    uint8_t mac[6] = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56};
    uint8_t ip[4] = {192, 168, 1, 100};
    uint8_t subnet[4] = {255, 255, 255, 0};
    uint8_t gateway[4] = {192, 168, 1, 1};
    
    w5500_set_mac(mac);
    w5500_set_ip(ip);
    w5500_set_subnet(subnet);
    w5500_set_gateway(gateway);
}

void w5500_write(uint16_t addr, uint8_t data) {
    spi_select();
    spi_transfer((addr >> 8) & 0xFF);
    spi_transfer(addr & 0xFF);
    spi_transfer(0x04); // Write command
    spi_transfer(data);
    spi_deselect();
}

uint8_t w5500_read(uint16_t addr) {
    spi_select();
    spi_transfer((addr >> 8) & 0xFF);
    spi_transfer(addr & 0xFF);
    spi_transfer(0x00); // Read command
    uint8_t data = spi_transfer(0x00);
    spi_deselect();
    return data;
}

void w5500_set_ip(uint8_t *ip) {
    for (int i = 0; i < 4; i++) {
        w5500_write(W5500_SIPR + i, ip[i]);
    }
}

void w5500_set_mac(uint8_t *mac) {
    for (int i = 0; i < 6; i++) {
        w5500_write(W5500_SHAR + i, mac[i]);
    }
}

void w5500_set_subnet(uint8_t *subnet) {
    for (int i = 0; i < 4; i++) {
        w5500_write(W5500_SUBR + i, subnet[i]);
    }
}

void w5500_set_gateway(uint8_t *gateway) {
    for (int i = 0; i < 4; i++) {
        w5500_write(W5500_GAR + i, gateway[i]);
    }
}

// Configure socket with port and protocol
void w5500_socket_init(uint8_t socket, uint8_t protocol, uint16_t port) {
    // Set socket mode (TCP/UDP)
    w5500_write(W5500_Sn_MR + (socket * 0x100), protocol);
    
    // Set port number
    w5500_write(W5500_Sn_PORT + (socket * 0x100), port >> 8);
    w5500_write(W5500_Sn_PORT + (socket * 0x100) + 1, port & 0xFF);
    
    // Open socket
    w5500_write(W5500_Sn_CR + (socket * 0x100), W5500_CR_OPEN);
}

// Set destination IP and port for socket
void w5500_set_dest(uint8_t socket, uint8_t *ip, uint16_t port) {
    // Set destination IP
    for (int i = 0; i < 4; i++) {
        w5500_write(W5500_Sn_DIPR + (socket * 0x100) + i, ip[i]);
    }
    
    // Set destination port
    w5500_write(W5500_Sn_DPORT + (socket * 0x100), port >> 8);
    w5500_write(W5500_Sn_DPORT + (socket * 0x100) + 1, port & 0xFF);
}

// Send socket command
void w5500_socket_cmd(uint8_t socket, uint8_t cmd) {
    w5500_write(W5500_Sn_CR + (socket * 0x100), cmd);
}

// Get socket status
uint8_t w5500_socket_status(uint8_t socket) {
    return w5500_read(W5500_Sn_SR + (socket * 0x100));
}
