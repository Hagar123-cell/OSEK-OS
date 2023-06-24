
#ifndef RISCV_CONTXT_H
#define RISCV_CONTXT_H
.extern RISCV_CONTEXT_SWITCH

#define RV32

#ifdef RV32
	#define STORE_REG sw
        #define LOAD_REG lw
        #define portWORD_SIZE 4  
	#define CONTEXT_SIZE  120    /* 4*30=120 */
	
	#define PC_STACK_OFFSET   0
	#define MSTATUS_STACK_OFFSET  4   /* 4*1=4 */
	#define X1_STACK_OFFSET  8        /* 4*2=8 */
	#define X5_STACK_OFFSET  12	  /* 4*3=12 */
	#define X6_STACK_OFFSET  16	  /* 4*4=16 */
	#define X7_STACK_OFFSET  20	  /* 4*5=20 */
	#define X8_STACK_OFFSET  24	  /* 4*6=24 */
	#define X9_STACK_OFFSET  28       /* 4*7=28 */
	#define X10_STACK_OFFSET  32      /* 4*8=32 */
	#define X11_STACK_OFFSET  36      /* 4*9=36 */
	#define X12_STACK_OFFSET  40      /* 4*10=40 */
	#define X13_STACK_OFFSET  44      /* 4*11=44 */
	#define X14_STACK_OFFSET  48
	#define X15_STACK_OFFSET  52
	#define X16_STACK_OFFSET  56
	#define X17_STACK_OFFSET  60
	#define X18_STACK_OFFSET  64
	#define X19_STACK_OFFSET  68
	#define X20_STACK_OFFSET  72
	#define X21_STACK_OFFSET  76
	#define X22_STACK_OFFSET  80
	#define X23_STACK_OFFSET  84
	#define X24_STACK_OFFSET  88
	#define X25_STACK_OFFSET  92
	#define X26_STACK_OFFSET  96
	#define X27_STACK_OFFSET  100
	#define X28_STACK_OFFSET  104
	#define X29_STACK_OFFSET  108
	#define X30_STACK_OFFSET  112
	#define X31_STACK_OFFSET  116
	
#else		/* RV64 */
        #define STORE_REG sd
        #define LOAD_REG ld
	#define portWORD_SIZE 8
	#define CONTEXT_SIZE  240 
	
        #define PC_STACK_OFFSET   0
	#define MSTATUS_STACK_OFFSET  8
	#define X1_STACK_OFFSET  16
	#define X5_STACK_OFFSET  24
	#define X6_STACK_OFFSET  32
	#define X7_STACK_OFFSET  40
	#define X8_STACK_OFFSET  48
	#define X9_STACK_OFFSET  56
	#define X10_STACK_OFFSET  64
	#define X11_STACK_OFFSET  72
	#define X12_STACK_OFFSET  80
	#define X13_STACK_OFFSET  88
	#define X14_STACK_OFFSET  96
	#define X15_STACK_OFFSET  104
	#define X16_STACK_OFFSET  112
	#define X17_STACK_OFFSET  120
	#define X18_STACK_OFFSET  128
	#define X19_STACK_OFFSET  136
	#define X20_STACK_OFFSET  144
	#define X21_STACK_OFFSET  152
	#define X22_STACK_OFFSET  160
	#define X23_STACK_OFFSET  168
	#define X24_STACK_OFFSET  176
	#define X25_STACK_OFFSET  184
	#define X26_STACK_OFFSET  192
	#define X27_STACK_OFFSET  200
	#define X28_STACK_OFFSET  208
	#define X29_STACK_OFFSET  216
	#define X30_STACK_OFFSET  224
	#define X31_STACK_OFFSET  232
#endif



#endif /* RISCV_CONTXT_H */

