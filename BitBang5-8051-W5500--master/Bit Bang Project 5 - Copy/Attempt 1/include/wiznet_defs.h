#ifndef WIZNET_DEFS_H
#define WIZNET_DEFS_H

#define CR 0x00 //common register

#define S0_R 0b00001000 //select socket 0 register
#define S0_TX 0b00010000 //select socket 0 tx buffer
#define S0_RX 0b00011000 //select socket 0 rx buffer

#define S1_R 0b00101000 //select socket 1 register 
#define S1_TX 0b00110000 //select socket 2 tx buffer
#define S1_RX 0b00111000 //select socket 2 rx buffer

#define S2_R 0b01001000 //select socket 2 register
#define S2_TX 0b01010000 //select socket 2 tx buffer
#define S2_RX 0b01011000 //select socket 2 rx buffer

#define S3_R 0b01101000 //select socket 3 register
#define S3_TX 0b01110000 //select socket 3 tx buffer
#define S3_RX 0b01111000 //select socket 3 rx buffer

#define S4_R 0b10001000 //select socket 4 register
#define S4_TX 0b10010000 //select socket 4 tx buffer
#define S4_RX 0b10011000 //select socket 4 rx buffer

#define S5_R 0b10101000 //select socket 5 register
#define S5_TX 0b10110000 //select socket 5 tx buffer
#define S5_RX 0b10111000 //select socket 5 rx buffer

#define S6_R 0b11001000 //select socket 6 register
#define S6_TX 0b11010000 //select socket 6 tx buffer
#define S6_RX 0b11011000 //select socket 6 rx buffer

#define S7_R 0b11101000 //select socket 7 register
#define S7_TX 0b11110000 //select socket 7 tx buffer
#define S7_RX 0b11111000 //select socket 7 rx buffer

// Other below ----------------------------

#define MOSI P1_0 // pin 10
#define MISO P1_1 // pin 11
#define SCK  P1_2 // pin 12
#define SS   P1_3 // pin 13
#define RXD P3_0 // pin 30
#define TXD P3_1 // pin 31

#define OUT P1_4 //pin 14
#define PININT P1_5 //pin 15

#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE  0x0F

#define CR 0x00 //common register

#define S0_R 0b00001000 //select socket 0 register
#define S0_TX 0b00010000 //select socket 0 tx buffer
#define S0_RX 0b00011000 //select socket 0 rx buffer

#define S1_R 0b00101000 //select socket 1 register 
#define S1_TX 0b00110000 //select socket 1 tx buffer
#define S1_RX 0b00111000 //select socket 1 rx buffer

#define Sn_PC 0b00000000 //socket n protocol closed
#define Sn_PTCP 0b00000001 //socket n protocol TCP
#define Sn_PUDP 0b00000010 //socket n protocol UDP

#define MR 0x0000 //mode register
#define SIPR 0x000F //source ip address
#define SHAR 0x0009 //source mac address
#define SUBR 0x0005 //subnet mask
#define GAR 0x0001 //gateway address

#define Sn_MR 0x0000 //socket n mode register
#define Sn_CR 0x0001 //socket n command register
#define Sn_IR 0x0002 //socket n interrupt register
#define Sn_SR 0x0003 //socket n status register
#define Sn_PORT0 0x0004 //socket n port register
#define Sn_PORT1 0x0005 //socket n destination port register
#define Sn_DPORT0 0x0010 //socket n destination port register
#define Sn_DPORT1 0x0011 //socket n destination port register
#define IMR 0x0016
#define SIR 0x0017 
#define SIMR 0x0018
#define Sn_RXBUF_SIZE 0x001E //socket n rx buffer size register
#define Sn_TX_RD0 0x0022 //socket n tx read pointer register
#define Sn_TX_RD1 0x0023 //socket n tx read pointer register
#define Sn_TX_WR0 0x0024 //socket n tx write pointer register
#define Sn_TX_WR1 0x0025 //socket n tx write pointer register
#define Sn_RX_RSR0 0x0026 //socket n rx received size register
#define Sn_RX_RSR1 0x0027 //socket n rx received size register
#define Sn_RX_RD0 0x0028 //socket n rx read pointer register
#define Sn_RX_RD1 0x0029 //socket n rx read pointer register
#define Sn_RX_WR0 0x002A //socket n rx write pointer register
#define Sn_RX_WR1 0x002B //socket n rx write pointer register
#define Sn_IMR 0x002C //socket n interrupt mask register

#define MAX_IP_LENGTH 16 //max length of ip address
#define MAX_MAX_LENGTH 18 //max length of mac address

//spi functions
void SPI_Init(void);
void SPI_Write(unsigned char data);
void SPI_WriteShort(unsigned short data);
unsigned char SPI_Read(void);

void WIZnet_Write(unsigned short address, unsigned char modeRegister, unsigned char data);
unsigned char WIZnet_Read(unsigned short address, unsigned char modeRegister);
void WIZnet_Init(void);
void WIZnet_SetIP(unsigned char *ip);
void WIZnet_SetMAC(unsigned char *mac);
void WIZnet_SetSubnetMask(unsigned char *subnet);
void WIZnet_SetGateway(unsigned char *gateway);
void WIZnet_SetSocketMode(unsigned char mode, unsigned char sock);
void WIZnet_SetSocketPort(unsigned char sock, int port);
void WIZnet_OpenSocket(unsigned char sock);
void WIZnet_CloseSocket(unsigned char sock);
void WIZnet_SetDestinationPort(unsigned char sock, int destPort);
void WIZnet_SetDestinationIP(unsigned char *ip, unsigned char sock);
void Wiznet_SendPacket(unsigned char sock);
void setRxBufferSize(unsigned char sock);
unsigned short getRxReadPointer(unsigned char sock);
unsigned short getRxWritePointer(unsigned char sock);
unsigned short getTxReadPointer(unsigned char sock);
unsigned short getTxWritePointer(unsigned char sock);
void writeToTXBufferUDP(unsigned char sock, unsigned char socktx);
void readFromRXBufferUDP(unsigned char sock, unsigned char sockrx);
void tcpListen(unsigned char sock);
void tcpConnect(unsigned char sock,unsigned char ip[],int destPort);
void readFromRXBufferTCP(unsigned char sock, unsigned char sockrx);
void writeToTxBufferTCP(unsigned char sock, unsigned char socktx);

//uart functions
void UART_Init(void);  // Function to initialize UART
void UART_TxChar(char c);  // Function to transmit a character
char UART_RxChar(void);  // Function to receive a character
void UART_PrintString(char* str); // Function to print a string using UART
void UART_PrintIP(unsigned char* ip); // Function to print an IP address using UART
void UART_PrintNumber(unsigned char num); // Function to print a number using UART
void UART_PrintMAC(unsigned char* mac); // Function to print a MAC address using UART
void UART_PrintHex(unsigned char num); // Function to print a number in hexadecimal format using UART
void UART_PrintCharArr(char str[]); // Function to print a character array using UART

//helper functions
void delay(unsigned int milliseconds);
unsigned char combineHexChars(char high, char low);

#endif // MYHEADER_H
