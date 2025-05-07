#include "w5500.h"
#include <stdint.h>

void w5500_udp_init(uint8_t socket, uint16_t port) {
    // Configure socket in UDP mode
    w5500_write(socket * 0x100 + W5500_Sn_MR, W5500_MR_UDP);
    // Set local port
    w5500_write(socket * 0x100 + W5500_Sn_PORT, port >> 8);
    w5500_write(socket * 0x100 + W5500_Sn_PORT + 1, 0xFF & port);
    // Open socket
    w5500_write(socket * 0x100 + W5500_Sn_CR, W5500_CR_OPEN);
}

void w5500_udp_send(uint8_t socket, uint8_t *buf, uint16_t len, uint8_t *dest_ip, uint16_t dest_port) {
    // Set destination IP
    for (int i = 0; i < 4; i++) {
        w5500_write(socket * 0x100 + W5500_Sn_DIPR + i, dest_ip[i]);
    }
    // Set destination port
    w5500_write(socket * 0x100 + W5500_Sn_DPORT, dest_port >> 8);
    w5500_write(socket * 0x100 + W5500_Sn_DPORT + 1, dest_port & 0xFF);
    // Write data to socket buffer
    for (int i = 0; i < len; i++) {
        w5500_write(socket * 0x100 + 0x200 + i, buf[i]);
    }
    // Send data
    w5500_write(socket * 0x100 + W5500_Sn_CR, W5500_CR_SEND);
}

int16_t w5500_udp_recv(uint8_t socket, uint8_t *buf, uint16_t len, uint8_t *src_ip, uint16_t *src_port) {
    // Check if data available
    uint8_t status = w5500_read(socket * 0x100 + W5500_Sn_SR);
    if (status != 0x42) { // UDP mode
        return -1;
    }
    // Read source IP
    for (int i = 0; i < 4; i++) {
        src_ip[i] = w5500_read(socket * 0x100 + W5500_Sn_DIPR + i);
    }
    // Read source port
    *src_port = (w5500_read(socket * 0x100 + W5500_Sn_DPORT) << 8) | 
                w5500_read(socket * 0x100 + W5500_Sn_DPORT + 1);
    // Read data
    for (int i = 0; i < len; i++) {
        buf[i] = w5500_read(socket * 0x100 + 0x200 + i);
    }
    return len;
}
