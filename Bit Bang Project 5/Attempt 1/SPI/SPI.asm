;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler
; Version 4.5.0 #15242 (MINGW64)
;--------------------------------------------------------
	.module SPI
	
	.optsdcc -mmcs51 --model-small
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _SPI_read
	.globl _SPI_write
	.globl _SPI_transfer
	.globl _SPI_init
	.globl _delay_us
	.globl _CS
	.globl _SCK
	.globl _MISO
	.globl _MOSI
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _P
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _B
	.globl _ACC
	.globl _PSW
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_P2	=	0x00a0
_IE	=	0x00a8
_P3	=	0x00b0
_IP	=	0x00b8
_PSW	=	0x00d0
_ACC	=	0x00e0
_B	=	0x00f0
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_TXD	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
_MOSI::
	.ds 1
_MISO::
	.ds 1
_SCK::
	.ds 1
_CS::
	.ds 1
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
;--------------------------------------------------------
; overlayable items in internal ram
;--------------------------------------------------------
;--------------------------------------------------------
; Stack segment in internal ram
;--------------------------------------------------------
	.area SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; uninitialized external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; initialized external ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
; restartable atomic support routines
	.ds	5
sdcc_atomic_exchange_rollback_start::
	nop
	nop
sdcc_atomic_exchange_pdata_impl:
	movx	a, @r0
	mov	r3, a
	mov	a, r2
	movx	@r0, a
	sjmp	sdcc_atomic_exchange_exit
	nop
	nop
sdcc_atomic_exchange_xdata_impl:
	movx	a, @dptr
	mov	r3, a
	mov	a, r2
	movx	@dptr, a
	sjmp	sdcc_atomic_exchange_exit
sdcc_atomic_compare_exchange_idata_impl:
	mov	a, @r0
	cjne	a, ar2, .+#5
	mov	a, r3
	mov	@r0, a
	ret
	nop
sdcc_atomic_compare_exchange_pdata_impl:
	movx	a, @r0
	cjne	a, ar2, .+#5
	mov	a, r3
	movx	@r0, a
	ret
	nop
sdcc_atomic_compare_exchange_xdata_impl:
	movx	a, @dptr
	cjne	a, ar2, .+#5
	mov	a, r3
	movx	@dptr, a
	ret
sdcc_atomic_exchange_rollback_end::

sdcc_atomic_exchange_gptr_impl::
	jnb	b.6, sdcc_atomic_exchange_xdata_impl
	mov	r0, dpl
	jb	b.5, sdcc_atomic_exchange_pdata_impl
sdcc_atomic_exchange_idata_impl:
	mov	a, r2
	xch	a, @r0
	mov	dpl, a
	ret
sdcc_atomic_exchange_exit:
	mov	dpl, r3
	ret
sdcc_atomic_compare_exchange_gptr_impl::
	jnb	b.6, sdcc_atomic_compare_exchange_xdata_impl
	mov	r0, dpl
	jb	b.5, sdcc_atomic_compare_exchange_pdata_impl
	sjmp	sdcc_atomic_compare_exchange_idata_impl
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
__sdcc_program_startup:
	ljmp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'delay_us'
;------------------------------------------------------------
;us            Allocated to registers 
;------------------------------------------------------------
;	SPI.c:10: void delay_us(unsigned int us) {
;	-----------------------------------------
;	 function delay_us
;	-----------------------------------------
_delay_us:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
	mov	r6, dpl
	mov	r7, dph
;	SPI.c:11: while(us--) {
00101$:
	mov	ar4,r6
	mov	ar5,r7
	dec	r6
	cjne	r6,#0xff,00119$
	dec	r7
00119$:
	mov	a,r4
	orl	a,r5
	jz	00104$
;	SPI.c:12: _nop_(); _nop_(); _nop_(); _nop_(); 
	push	ar7
	push	ar6
	lcall	__nop_
	lcall	__nop_
	lcall	__nop_
	lcall	__nop_
	pop	ar6
	pop	ar7
	sjmp	00101$
00104$:
;	SPI.c:14: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SPI_init'
;------------------------------------------------------------
;	SPI.c:16: void SPI_init(void) {
;	-----------------------------------------
;	 function SPI_init
;	-----------------------------------------
_SPI_init:
;	SPI.c:17: MOSI = 0;
;	assignBit
	clr	_MOSI
;	SPI.c:18: SCK  = 0;
;	assignBit
	clr	_SCK
;	SPI.c:19: CS   = 1; 
;	assignBit
	setb	_CS
;	SPI.c:20: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SPI_transfer'
;------------------------------------------------------------
;data_out      Allocated to registers r7 
;i             Allocated to registers r5 
;data_in       Allocated to registers r6 
;------------------------------------------------------------
;	SPI.c:22: unsigned char SPI_transfer(unsigned char data_out) {
;	-----------------------------------------
;	 function SPI_transfer
;	-----------------------------------------
_SPI_transfer:
	mov	r7, dpl
;	SPI.c:23: unsigned char i, data_in = 0;
	mov	r6,#0x00
;	SPI.c:24: for (i = 0; i < 8; i++) {
	mov	r5,#0x00
00104$:
;	SPI.c:25: MOSI = (data_out & 0x80); 
	mov	a,r7
	rl	a
	anl	a,#0x01
;	assignBit
	add	a,#0xff
	mov	_MOSI,c
;	SPI.c:26: data_out <<= 1;
	mov	a,r7
	add	a,r7
	mov	r7,a
;	SPI.c:28: SCK = 1;
;	assignBit
	setb	_SCK
;	SPI.c:29: delay_us(1);
	mov	dptr,#0x0001
	push	ar7
	push	ar6
	push	ar5
	lcall	_delay_us
	pop	ar5
	pop	ar6
;	SPI.c:31: data_in <<= 1;
;	SPI.c:32: if (MISO) data_in |= 0x01;
	mov	a,r6
	mov	c,_MISO
	addc	a,r6
	mov	r6,a
;	SPI.c:34: SCK = 0;
;	assignBit
	clr	_SCK
;	SPI.c:35: delay_us(1);
	mov	dptr,#0x0001
	push	ar6
	push	ar5
	lcall	_delay_us
	pop	ar5
	pop	ar6
	pop	ar7
;	SPI.c:24: for (i = 0; i < 8; i++) {
	inc	r5
	cjne	r5,#0x08,00128$
00128$:
	jc	00104$
;	SPI.c:37: return data_in;
	mov	dpl, r6
;	SPI.c:38: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SPI_write'
;------------------------------------------------------------
;data          Allocated to registers r7 
;------------------------------------------------------------
;	SPI.c:40: void SPI_write(unsigned char data) {
;	-----------------------------------------
;	 function SPI_write
;	-----------------------------------------
_SPI_write:
	mov	r7, dpl
;	SPI.c:41: CS = 0;
;	assignBit
	clr	_CS
;	SPI.c:42: SPI_transfer(data);
	mov	dpl, r7
	lcall	_SPI_transfer
;	SPI.c:43: CS = 1;
;	assignBit
	setb	_CS
;	SPI.c:44: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'SPI_read'
;------------------------------------------------------------
;data          Allocated to registers 
;------------------------------------------------------------
;	SPI.c:46: unsigned char SPI_read(void) {
;	-----------------------------------------
;	 function SPI_read
;	-----------------------------------------
_SPI_read:
;	SPI.c:47: CS = 0;
;	assignBit
	clr	_CS
;	SPI.c:48: unsigned char data = SPI_transfer(0xFF);
	mov	dpl, #0xff
	lcall	_SPI_transfer
;	SPI.c:49: CS = 1;
;	assignBit
	setb	_CS
;	SPI.c:50: return data;
;	SPI.c:51: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;x             Allocated to registers 
;------------------------------------------------------------
;	SPI.c:53: void main() {
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	SPI.c:54: SPI_init();
	lcall	_SPI_init
;	SPI.c:56: while (1) {
00102$:
;	SPI.c:57: SPI_write(0x9A);                
	mov	dpl, #0x9a
	lcall	_SPI_write
;	SPI.c:58: unsigned char x = SPI_read();   
	lcall	_SPI_read
;	SPI.c:60: }
	sjmp	00102$
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
