#ifndef W5500_H
#define W5500_H

// W5500 Register Addresses
#define W5500_MR      0x0000  // Mode Register
#define W5500_GAR     0x0001  // Gateway Address
#define W5500_SUBR    0x0005  // Subnet Mask
#define W5500_SHAR    0x0009  // Source Hardware Address (MAC)
#define W5500_SIPR    0x000F  // Source IP Address
#define W5500_PHYCFGR 0x002E  // PHY Configuration

// Socket Registers
#define W5500_Sn_MR    0x0000  // Socket n Mode Register
#define W5500_Sn_CR    0x0001  // Socket n Command Register
#define W5500_Sn_IR    0x0002  // Socket n Interrupt Register
#define W5500_Sn_PORT  0x0004  // Socket n Source Port
#define W5500_Sn_DHAR  0x0006  // Destination MAC Address
#define W5500_Sn_DIPR  0x000C  // Destination IP Address
#define W5500_Sn_DPORT 0x0010  // Destination Port
#define W5500_Sn_SR    0x0003  // Socket Status Register

// Socket Modes
#define W5500_MR_CLOSE 0x00
#define W5500_MR_TCP   0x01
#define W5500_MR_UDP   0x02

// Socket Commands
#define W5500_CR_OPEN     0x01
#define W5500_CR_LISTEN   0x02
#define W5500_CR_CONNECT  0x04
#define W5500_CR_DISCON   0x08
#define W5500_CR_CLOSE    0x10
#define W5500_CR_SEND     0x20
#define W5500_CR_SEND_MAC 0x21
#define W5500_CR_SEND_KEEP 0x22
#define W5500_CR_RECV     0x40

// Common Register Operations
#define W5500_CR_READ  0x00
#define W5500_CR_WRITE 0x04

// Function prototypes
void w5500_init(void);
void w5500_write(uint16_t address, uint8_t data);
uint8_t w5500_read(uint16_t address);
void w5500_set_ip(uint8_t *ip);
void w5500_set_mac(uint8_t *mac);
void w5500_udp_init(uint8_t socket, uint16_t port);
void w5500_udp_send(uint8_t socket, uint8_t *buf, uint16_t len, uint8_t *dest_ip, uint16_t dest_port);
int16_t w5500_udp_recv(uint8_t socket, uint8_t *buf, uint16_t len, uint8_t *src_ip, uint16_t *src_port);

#endif
