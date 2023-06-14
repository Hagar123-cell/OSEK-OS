/******************************************************************************
 *
 * Module: Interrupts
 *
 * File Name: OsInterrupts.h
 *
 * Description: Header File for interrupts services for OSEK OS
 *
 * Author: Nora Nagdi
 *
 *******************************************************************************/

#ifndef INTERRUPT_HW_H_
#define INTERRUPT_HW_H_


/*******************************************************************************
 *                                   PLIC                                      *
 *******************************************************************************/

#define PLIC_BASE_ADDR              0xC000000

/* Pointer to PLIC base address*/
#define PLIC ((PLIC_Type *)PLIC_BASE_ADDR)


/* Structure for PLIC */
typedef struct {                                /*!< (@ 0x0C000000) PLIC Structure*/
	union {
		volatile uint32  reg;                   /*!< (@ 0x0C000000) Interrupt Priority Register*/

		struct {
			volatile uint32  priority   :  3;   /*!< [0..2] (null)*/
		} bit;                                  /*!< [3] BitSize*/
	} priority[53];
	volatile uint32  RESERVED[971];
	volatile uint32  pending[2];                /*!< (@ 0x0C001000) Interrupt Pending Register*/
	volatile uint32  RESERVED1[1022];
	volatile uint32  enable[2];                 /*!< (@ 0x0C002000) Interrupt Enable Register*/
	volatile uint32  RESERVED2[522238];

	union {
		volatile uint32  reg;                   /*!< (@ 0x0C200000) Priority Threshold Register*/

		struct {
			volatile uint32  priority   :  3;   /*!< [0..2] (null)*/
		} bit;                                  /*!< [3] BitSize*/
	} threshold;
	volatile uint32  claim;                     /*!< (@ 0x0C200004) Claim/Complete Register*/
} PLIC_Type;


#endif /* INTERRUPT_HW_H_ */
