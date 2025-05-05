CC=sdcc
CFLAGS=-mmcs51
ARCH=stc89
INCLUDES=-I../include
LIBS=
PORT=COM3

%.asm:		%.c
		$(CC) $(CFLAGS) $(INCLUDES) -S $<

%.rel:		%.c
		$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $(<:.c=.rel)

%.ihx:		%.rel
		$(CC) $(CFLAGS) -o $@ $<

%.ibn:		%.ihx
		hex2bin -e ibn $<

%.flash:	%.ihx
ifndef ARCH
		stcgal -p $(PORT) $<
else
		stcgal -P $(ARCH) -p $(PORT) $<
endif

clean:
		rm -f *.{asm,sym,lst,rel,rst,sym,lk,map,mem,ihx,ibn}
