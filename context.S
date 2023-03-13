
#include "context.h"
.extern CurrentTCB

.global RISCV_SAVE_CONTEXT
.global RISCV_RESTORE_CONTEXT

RISCV_SAVE_CONTEXT:
    addi sp, sp, -portCONTEXT_SIZE
    STORE_REG x1,  X1_STACK_OFFSET  ( sp )
    STORE_REG x5,  X5_STACK_OFFSET  ( sp )
    STORE_REG x6,  X6_STACK_OFFSET  ( sp )
    STORE_REG x7,  X7_STACK_OFFSET  ( sp )
    STORE_REG x8,  X8_STACK_OFFSET  ( sp )
    STORE_REG x9,  X9_STACK_OFFSET  ( sp )
    STORE_REG x10, X10_STACK_OFFSET ( sp )
    STORE_REG x11, X11_STACK_OFFSET ( sp )
    STORE_REG x12, X12_STACK_OFFSET ( sp )
    STORE_REG x13, X13_STACK_OFFSET ( sp )
    STORE_REG x14, X14_STACK_OFFSET ( sp )
    STORE_REG x15, X15_STACK_OFFSET ( sp )
    STORE_REG x16, X16_STACK_OFFSET ( sp )
    STORE_REG x17, X17_STACK_OFFSET ( sp )
    STORE_REG x18, X18_STACK_OFFSET ( sp )
    STORE_REG x19, X19_STACK_OFFSET ( sp )
    STORE_REG x20, X20_STACK_OFFSET ( sp )
    STORE_REG x21, X21_STACK_OFFSET ( sp )
    STORE_REG x22, X22_STACK_OFFSET ( sp )
    STORE_REG x23, X23_STACK_OFFSET ( sp )
    STORE_REG x24, X24_STACK_OFFSET ( sp )
    STORE_REG x25, X25_STACK_OFFSET ( sp )
    STORE_REG x26, X26_STACK_OFFSET ( sp )
    STORE_REG x27, X27_STACK_OFFSET ( sp )
    STORE_REG x28, X28_STACK_OFFSET ( sp )
    STORE_REG x29, X29_STACK_OFFSET ( sp )
    STORE_REG x30, X30_STACK_OFFSET ( sp )
    STORE_REG x31, X31_STACK_OFFSET ( sp )

    csrr t0, mstatus                     /* Required for MPIE bit. */
    STORE_REG t0, MSTATUS_STACK_OFFSET ( sp )


    LOAD_REG  t0, CurrentTCB             /* Load CurrentTCB. */
    STORE_REG  sp, 0( t0 )                 /* Write sp to first TCB member. */


    csrr a0, mcause
    csrr a1, mepc
	blt a0, x0, interrupt
    addi a1, a1, 4                      /* Synchronous so update exception return address to the instruction after the instruction that generated the exception. */
interrupt:
    store_x a1, PC_STACK_OFFSET  ( sp )                 /* Save updated exception return address. */

	/* Asynchronous interrupt so save unmodified exception return address. */
    .endm
/*-----------------------------------------------------------*/

RISCV_RESTORE_CONTEXT
    LOAD_REG  t1, CurrentTCB                /* Load CurrentTCB. */
    LOAD_REG  sp, 0( t1 )                 /* Read sp from first TCB member. */

    /* Load mepc with the address of the instruction in the task to run next. */
    LOAD_REG t0,  PC_STACK_OFFSET ( sp )
    csrw mepc, t0


    /* Load mstatus with the interrupt enable bits used by the task. */
    LOAD_REG  t0, MSTATUS_STACK_OFFSET ( sp )
    csrw mstatus, t0                        /* Required for MPIE bit. */

	LOAD_REG x1,  X1_STACK_OFFSET  ( sp )
    LOAD_REG x5,  X5_STACK_OFFSET  ( sp )
    LOAD_REG x6,  X6_STACK_OFFSET  ( sp )
    LOAD_REG x7,  X7_STACK_OFFSET  ( sp )
    LOAD_REG x8,  X8_STACK_OFFSET  ( sp )
    LOAD_REG x9,  X9_STACK_OFFSET  ( sp )
    LOAD_REG x10, X10_STACK_OFFSET ( sp )
    LOAD_REG x11, X11_STACK_OFFSET ( sp )
    LOAD_REG x12, X12_STACK_OFFSET ( sp )
    LOAD_REG x13, X13_STACK_OFFSET ( sp )
    LOAD_REG x14, X14_STACK_OFFSET ( sp )
    LOAD_REG x15, X15_STACK_OFFSET ( sp )
    LOAD_REG x16, X16_STACK_OFFSET ( sp )
    LOAD_REG x17, X17_STACK_OFFSET ( sp )
    LOAD_REG x18, X18_STACK_OFFSET ( sp )
    LOAD_REG x19, X19_STACK_OFFSET ( sp )
    LOAD_REG x20, X20_STACK_OFFSET ( sp )
    LOAD_REG x21, X21_STACK_OFFSET ( sp )
    LOAD_REG x22, X22_STACK_OFFSET ( sp )
    LOAD_REG x23, X23_STACK_OFFSET ( sp )
    LOAD_REG x24, X24_STACK_OFFSET ( sp )
	LOAD_REG x25, X25_STACK_OFFSET ( sp )
    LOAD_REG x26, X26_STACK_OFFSET ( sp )
    LOAD_REG x27, X27_STACK_OFFSET ( sp )
    LOAD_REG x28, X28_STACK_OFFSET ( sp )
    LOAD_REG x29, X29_STACK_OFFSET ( sp )
    LOAD_REG x30, X30_STACK_OFFSET ( sp )
    LOAD_REG x31, X31_STACK_OFFSET ( sp )
    addi sp, sp, portCONTEXT_SIZE

    mret

