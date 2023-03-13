
#ifndef RISCV_CONTXT_H
#define RISCV_CONTXT_H


#ifdef RV32
	#define store_x sw
        #define load_x lw
        #define portWORD_SIZE 4  
	#define portCONTEXT_SIZE  120 
	
	#define PC_STACK_OFFSET   0
	#define MSTATUS_STACK_OFFSET  4
	#define X1_STACK_OFFSET  8
	#define X5_STACK_OFFSET  12
	#define X6_STACK_OFFSET  16
	#define X7_STACK_OFFSET  20
	#define X8_STACK_OFFSET  24
	#define X9_STACK_OFFSET  28
	#define X10_STACK_OFFSET  32
	#define X11_STACK_OFFSET  36
	#define X12_STACK_OFFSET  40
	#define X13_STACK_OFFSET  44
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
        #define store_x sd
        #define load_x ld
	#define portWORD_SIZE 8
	#define portCONTEXT_SIZE  240 
	
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

/*-----------------------------------------------------------*/

.extern pxCurrentTCB

/*-----------------------------------------------------------*/

.macro portcontextSAVE_CONTEXT_INTERNAL
    addi sp, sp, -portCONTEXT_SIZE
    store_x x1,  X1_STACK_OFFSET  ( sp )
    store_x x5,  X5_STACK_OFFSET  ( sp )
    store_x x6,  X6_STACK_OFFSET  ( sp )
    store_x x7,  X7_STACK_OFFSET  ( sp )
    store_x x8,  X8_STACK_OFFSET  ( sp )
    store_x x9,  X9_STACK_OFFSET  ( sp )
    store_x x10, X10_STACK_OFFSET ( sp )
    store_x x11, X11_STACK_OFFSET ( sp )
    store_x x12, X12_STACK_OFFSET ( sp )
    store_x x13, X13_STACK_OFFSET ( sp )
    store_x x14, X14_STACK_OFFSET ( sp )
    store_x x15, X15_STACK_OFFSET ( sp )
    store_x x16, X16_STACK_OFFSET ( sp )
    store_x x17, X17_STACK_OFFSET ( sp )
    store_x x18, X18_STACK_OFFSET ( sp )
    store_x x19, X19_STACK_OFFSET ( sp )
    store_x x20, X20_STACK_OFFSET ( sp )
    store_x x21, X21_STACK_OFFSET ( sp )
    store_x x22, X22_STACK_OFFSET ( sp )
    store_x x23, X23_STACK_OFFSET ( sp )
    store_x x24, X24_STACK_OFFSET ( sp )
    store_x x25, X25_STACK_OFFSET ( sp )
    store_x x26, X26_STACK_OFFSET ( sp )
    store_x x27, X27_STACK_OFFSET ( sp )
    store_x x28, X28_STACK_OFFSET ( sp )
    store_x x29, X29_STACK_OFFSET ( sp )
    store_x x30, X30_STACK_OFFSET ( sp )
    store_x x31, X31_STACK_OFFSET ( sp )

    csrr t0, mstatus                     /* Required for MPIE bit. */
    store_x t0, MSTATUS_STACK_OFFSET ( sp )


    load_x  t0, pxCurrentTCB             /* Load pxCurrentTCB. */
    store_x  sp, 0( t0 )                 /* Write sp to first TCB member. */

    .endm
/*-----------------------------------------------------------*/

.macro portcontextSAVE_EXCEPTION_CONTEXT
    portcontextSAVE_CONTEXT_INTERNAL
    csrr a0, mcause
    csrr a1, mepc
    addi a1, a1, 4                      /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
    store_x a1, PC_STACK_OFFSET  ( sp )                 /* Save updated exception return address. */
    .endm
/*-----------------------------------------------------------*/

.macro portcontextSAVE_INTERRUPT_CONTEXT
    portcontextSAVE_CONTEXT_INTERNAL
    csrr a0, mcause
    csrr a1, mepc
    store_x a1,  PC_STACK_OFFSET ( sp )                 /* Asynchronous interrupt so save unmodified exception return address. */
    .endm
/*-----------------------------------------------------------*/

.macro portcontextRESTORE_CONTEXT
    load_x  t1, pxCurrentTCB                /* Load pxCurrentTCB. */
    load_x  sp, 0( t1 )                 /* Read sp from first TCB member. */

    /* Load mepc with the address of the instruction in the task to run next. */
    load_x t0,  PC_STACK_OFFSET ( sp )
    csrw mepc, t0


    /* Load mstatus with the interrupt enable bits used by the task. */
    load_x  t0, MSTATUS_STACK_OFFSET ( sp )
    csrw mstatus, t0                        /* Required for MPIE bit. */

	load_x x1,  X1_STACK_OFFSET  ( sp )
    load_x x5,  X5_STACK_OFFSET  ( sp )
    load_x x6,  X6_STACK_OFFSET  ( sp )
    load_x x7,  X7_STACK_OFFSET  ( sp )
    load_x x8,  X8_STACK_OFFSET  ( sp )
    load_x x9,  X9_STACK_OFFSET  ( sp )
    load_x x10, X10_STACK_OFFSET ( sp )
    load_x x11, X11_STACK_OFFSET ( sp )
    load_x x12, X12_STACK_OFFSET ( sp )
    load_x x13, X13_STACK_OFFSET ( sp )
    load_x x14, X14_STACK_OFFSET ( sp )
    load_x x15, X15_STACK_OFFSET ( sp )
    load_x x16, X16_STACK_OFFSET ( sp )
    load_x x17, X17_STACK_OFFSET ( sp )
    load_x x18, X18_STACK_OFFSET ( sp )
    load_x x19, X19_STACK_OFFSET ( sp )
    load_x x20, X20_STACK_OFFSET ( sp )
    load_x x21, X21_STACK_OFFSET ( sp )
    load_x x22, X22_STACK_OFFSET ( sp )
    load_x x23, X23_STACK_OFFSET ( sp )
    load_x x24, X24_STACK_OFFSET ( sp )
	load_x x25, X25_STACK_OFFSET ( sp )
    load_x x26, X26_STACK_OFFSET ( sp )
    load_x x27, X27_STACK_OFFSET ( sp )
    load_x x28, X28_STACK_OFFSET ( sp )
    load_x x29, X29_STACK_OFFSET ( sp )
    load_x x30, X30_STACK_OFFSET ( sp )
    load_x x31, X31_STACK_OFFSET ( sp )
    addi sp, sp, portCONTEXT_SIZE

    mret
    .endm
/*-----------------------------------------------------------*/

#endif /* RISCV_CONTXT_H */
