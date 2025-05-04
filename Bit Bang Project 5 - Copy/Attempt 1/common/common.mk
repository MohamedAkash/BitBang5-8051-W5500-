CC=sdcc
CFLAGS=-mmcs51 --model-medium # change to --model-small later
ARCH=stc89
INCLUDES=-I../include
LIBS=
PORT=COM6
OPTIONS=cpu_6t_enabled=true

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
		stcgal -p $(PORT) -o $(OPTIONS) $<
else
		stcgal -P $(ARCH) -p $(PORT) -o $(OPTIONS) $<
endif

clean:
		rm -f *.{asm,sym,lst,rel,rst,sym,lk,map,mem,ihx,ibn}


