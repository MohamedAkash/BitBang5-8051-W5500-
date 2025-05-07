# Makefile for STC89/STC12 with W5500 project

# Compiler settings
CC = sdcc
CFLAGS = -mmcs51 --model-small --opt-code-size

# Source files
SRC = main.c spi.c w5500.c
OBJ = $(SRC:.c=.rel)

# Target
TARGET = main.ihx

# Build target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.rel: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.rel *.lst *.asm *.sym *.rst *.lnk *.map *.mem *.ihx

flash: $(TARGET)
	stcgal -p /dev/ttyUSB0 -P stc89 -a $(TARGET)

.PHONY: all clean flash
