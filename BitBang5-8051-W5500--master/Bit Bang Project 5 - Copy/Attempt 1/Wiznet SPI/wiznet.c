#include <stdint.h>
#include <8051.h>
#include "../include/periphs.h"
#include "../include/typedefs.h"
#include "../include/pinmap.h"
#include "../include/wiznet_defs.h"
#include "../include/uart_config.h"

// Write to a WIZnet register uses the Address, Mode Register and data to write to the register
void WIZnet_Write(unsigned short address, unsigned char modeRegister, unsigned char data) {
    SS = 0;  // Select WIZnet
    SPI_WriteShort(address); //sending the address
    SPI_Write(modeRegister + 0x04); //where you put registers + 0x04 to indicate write operation
    SPI_Write(data); // Send data
    SS = 1;  // Deselect WIZnet
}

// Read from a WIZnet register
unsigned char WIZnet_Read(unsigned short address, unsigned char modeRegister) {
    unsigned char data;
    SS = 0;  // Select WIZnet
    SPI_WriteShort(address);
    SPI_Write(modeRegister); //where you put registers
    data = SPI_Read();                   // Read data
    SS = 1;  // Deselect WIZnet
    return data;
}

//Initialize the WIZnet chip
void WIZnet_Init(void) {
    // Reset WIZnet chip (if applicable)
    SS = 0; 
    SPI_WriteShort(MR);
    SPI_Write(0b10000000);// MR register: Reset command
    SS = 1;
    delay(10);                   // Wait for reset to complete
}


//Set the IP of the wiznet chip Common Register from 0x000F to 0x0012
void WIZnet_SetIP(unsigned char *ip) {
    // Set IP address (4 bytes)
    for (unsigned char i = 0; i < 4; i++) {
        WIZnet_Write(SIPR + i,CR, ip[i]); // SIPR register starts at 0x000F
    }
}

//Set the Mac address of the wiznet chip Common Register from 0x0009 to 0x000E
void WIZnet_SetMAC(unsigned char *mac) {
    // Set MAC address (6 bytes)
    for (unsigned char i = 0; i < 6; i++) {
        WIZnet_Write(SHAR + i,CR, mac[i]); // SHAR register starts at 0x0009
    }
}

//Set the Subnet Mask of the wiznet chip Common Register from 0x0005 to 0x0008
void WIZnet_SetSubnetMask(unsigned char *subnet) {
    // Set Subnet Mask (4 bytes)
    for (unsigned char i = 0; i < 4; i++) {
        WIZnet_Write(SUBR + i,CR, subnet[i]); // SUBR register starts at 0x0005
    }
}

//Set the Gateway Address of the wiznet chip Common Register from 0x0001 to 0x0004
void WIZnet_SetGateway(unsigned char *gateway) {
    // Set Gateway Address (4 bytes)
    for (unsigned char i = 0; i < 4; i++) {
        WIZnet_Write(GAR + i,CR, gateway[i]); // GAR register starts at 0x0001
    }
}

//Set the socket mode for Socket 0 
void WIZnet_SetSocketMode(unsigned char mode, unsigned char sock) {
    // Set the mode for the socket (TCP or UDP)
    WIZnet_Write(MR,sock,mode); // Sn_MR register
}

// Set the socket port for Socket n
void WIZnet_SetSocketPort(unsigned char sock, int port) {
    // Set the source port for the socket

    unsigned char highByte = (port >> 8) & 0xFF; // Get the high byte
    unsigned char lowByte = port & 0xFF; 

    WIZnet_Write(Sn_PORT0,sock, highByte); // Set port high byte (5000 = 0x1388)
    WIZnet_Write(Sn_PORT1, sock, lowByte);  // Set port low byte
}

// Send the open socket command for socket n
void WIZnet_OpenSocket(unsigned char sock) {
    // Open the socket
    WIZnet_Write(Sn_CR,sock, 0x01); // Sn_CR register: OPEN command
}

// Send the close socket command for socket n
void WIZnet_CloseSocket(unsigned char sock) {
    // Close the socket
    WIZnet_Write(Sn_CR,sock, 0x10); // Sn_CR register: CLOSE command
}

// Set the destination port for socket n
void WIZnet_SetDestinationPort(unsigned char sock, int destPort) {
    // Set the source port for the socket

    unsigned char highByte = (destPort >> 8) & 0xFF; // Get the high byte
    unsigned char lowByte = destPort & 0xFF; 

    WIZnet_Write(Sn_DPORT0,sock, highByte); // Set port high byte (5000 = 0x1388)
    WIZnet_Write(Sn_DPORT1, sock, lowByte);  // Set port low byte
}

//Set the destination IP of socket n
void WIZnet_SetDestinationIP(unsigned char *ip, unsigned char sock) {
    
    // Set IP address (4 bytes) memory efficient
    WIZnet_Write(0x000C,sock, ip[0]);
    WIZnet_Write(0x000D,sock, ip[1]);
    WIZnet_Write(0x000E,sock, ip[2]);
    WIZnet_Write(0x000F,sock, ip[3]);


}

//Helper function to set the packet ready to send for socket n
void Wiznet_SendPacket(unsigned char sock)
{
    WIZnet_Write(Sn_CR, sock, 0x20); // Send the data in the TX buffer
    while(WIZnet_Read(Sn_CR, sock) != 0x00) // Wait until the socket is ready to send data
    {
        // This loop will wait until the socket is ready to send data
    }
}