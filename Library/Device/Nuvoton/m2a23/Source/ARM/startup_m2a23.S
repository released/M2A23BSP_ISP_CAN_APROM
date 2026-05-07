/**************************************************************************//**
 * @file     startup_m2a23.s
 * @version  V3.00
 * @brief    M2A23 Series Startup Source File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


    .section .bss.STACK, "aw", %nobits
    .align 3

    .global __initial_sp
#ifndef Stack_Size
// <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
    .equ    Stack_Size, 0x00000400
#endif
Stack_Mem:
    .space   Stack_Size
__initial_sp:


    .section .bss.HEAP, "aw", %nobits
    .align  3
    .global Heap_Mem
    .global __heap_base
    .global __heap_limit
#ifndef Heap_Size
// <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
    .equ    Heap_Size, 0x00000100
#endif
__heap_base:
Heap_Mem:
    .space  Heap_Size
__heap_limit:

    .eabi_attribute Tag_ABI_align_preserved, 1
    .thumb

//*** <<< end of configuration section >>>    ***


// ; Vector Table Mapped to Address 0 at Reset
    .section RESET, "ax"
    .global     __Vectors
    .global     __Vectors_End
    .global     __Vectors_Size

__Vectors:
    .word     __initial_sp              //; Top of Stack
    .word     Reset_Handler             //; Reset Handler
    .word     NMI_Handler               //; NMI Handler
    .word     HardFault_Handler         //; Hard Fault Handler
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     SVC_Handler               //; SVCall Handler
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     PendSV_Handler            //; PendSV Handler
    .word     SysTick_Handler           //; SysTick Handler

    //; External Interrupts

    .word     BOD_IRQHandler
    .word     IRC_IRQHandler
    .word     PWRWU_IRQHandler
    .word     RAMPE_IRQHandler
    .word     CKFAIL_IRQHandler
    .word     ISP_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     WDT_IRQHandler
    .word     WWDT_IRQHandler
    .word     EINT0_IRQHandler
    .word     EINT1_IRQHandler
    .word     EINT2_IRQHandler
    .word     EINT3_IRQHandler
    .word     EINT4_IRQHandler
    .word     EINT5_IRQHandler
    .word     GPA_IRQHandler
    .word     GPB_IRQHandler
    .word     GPC_IRQHandler
    .word     GPD_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     GPF_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     SPI0_IRQHandler
    .word     BRAKE0_IRQHandler
    .word     PWM0P0_IRQHandler
    .word     PWM0P1_IRQHandler
    .word     PWM0P2_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     TMR0_IRQHandler
    .word     TMR1_IRQHandler
    .word     TMR2_IRQHandler
    .word     TMR3_IRQHandler
    .word     UART0_IRQHandler
    .word     UART1_IRQHandler
    .word     I2C0_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     PDMA0_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     ADC0_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     ACMP01_IRQHandler
    .word     BPWM0_IRQHandler
    .word     LLSI0_IRQHandler
    .word     LLSI1_IRQHandler
    .word     CANFD00_IRQHandler
    .word     CANFD01_IRQHandler
    .word     CANFD10_IRQHandler
    .word     CANFD11_IRQHandler
    .word     CANFD20_IRQHandler
    .word     CANFD21_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     DEFAULT_IRQHandler
    .word     USCI0_IRQHandler
    .word     USCI1_IRQHandler

__Vectors_End:
    .equ    __Vectors_Size, __Vectors_End - __Vectors

    .section .text, "ax"

// ; Reset Handler
    .global Reset_Handler
    .global  SystemInit
    .global  __main
    .type   Reset_Handler, "function"
Reset_Handler:
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__main
        BX      R0


// ; Dummy Exception Handlers (infinite loops which can be modified)
    .weak   NMI_Handler
    .type   NMI_Handler, "function"
NMI_Handler:
        B       .

    .weak   HardFault_Handler
    .type   HardFault_Handler, "function"

HardFault_Handler:
        MOV     R0, LR
        MRS     R1, MSP
        MRS     R2, PSP
        LDR     R3, =ProcessHardFault
        BLX     R3
        BX      R0

    .weak   SVC_Handler, "function"
SVC_Handler:
        B       .

    .weak   PendSV_Handler, "function"
PendSV_Handler:
        B       .

    .weak   SysTick_Handler, "function"
SysTick_Handler:
        B       .


    .weak	BOD_IRQHandler,"function"
    .weak	IRC_IRQHandler,"function"
    .weak	PWRWU_IRQHandler,"function"
    .weak	RAMPE_IRQHandler,"function"
    .weak	CKFAIL_IRQHandler,"function"
    .weak	ISP_IRQHandler,"function"
    .weak	WDT_IRQHandler,"function"
    .weak	WWDT_IRQHandler,"function"
    .weak	EINT0_IRQHandler,"function"
    .weak	EINT1_IRQHandler,"function"
    .weak	EINT2_IRQHandler,"function"
    .weak	EINT3_IRQHandler,"function"
    .weak	EINT4_IRQHandler,"function"
    .weak	EINT5_IRQHandler,"function"
    .weak	GPA_IRQHandler,"function"
    .weak	GPB_IRQHandler,"function"
    .weak	GPC_IRQHandler,"function"
    .weak	GPD_IRQHandler,"function"
    .weak	GPF_IRQHandler,"function"
    .weak	SPI0_IRQHandler,"function"
    .weak	BRAKE0_IRQHandler,"function"
    .weak	PWM0P0_IRQHandler,"function"
    .weak	PWM0P1_IRQHandler,"function"
    .weak	PWM0P2_IRQHandler,"function"
    .weak	TMR0_IRQHandler,"function"
    .weak	TMR1_IRQHandler,"function"
    .weak	TMR2_IRQHandler,"function"
    .weak	TMR3_IRQHandler,"function"
    .weak	UART0_IRQHandler,"function"
    .weak	UART1_IRQHandler,"function"
    .weak	I2C0_IRQHandler,"function"
    .weak	PDMA0_IRQHandler,"function"
    .weak	ADC0_IRQHandler,"function"
    .weak	ACMP01_IRQHandler,"function"
    .weak	BPWM0_IRQHandler,"function"
    .weak	LLSI0_IRQHandler,"function"
    .weak	LLSI1_IRQHandler,"function"
    .weak	CANFD00_IRQHandler,"function"
    .weak	CANFD01_IRQHandler,"function"
    .weak	CANFD10_IRQHandler,"function"
    .weak	CANFD11_IRQHandler,"function"
    .weak	CANFD20_IRQHandler,"function"
    .weak	CANFD21_IRQHandler,"function"
    .weak	USCI0_IRQHandler,"function"
    .weak	USCI1_IRQHandler,"function"
    .weak	DEFAULT_IRQHandler,"function"
Default_Handler:
BOD_IRQHandler:
IRC_IRQHandler:
PWRWU_IRQHandler:
RAMPE_IRQHandler:
CKFAIL_IRQHandler:
ISP_IRQHandler:
WDT_IRQHandler:
WWDT_IRQHandler:
EINT0_IRQHandler:
EINT1_IRQHandler:
EINT2_IRQHandler:
EINT3_IRQHandler:
EINT4_IRQHandler:
EINT5_IRQHandler:
GPA_IRQHandler:
GPB_IRQHandler:
GPC_IRQHandler:
GPD_IRQHandler:
GPF_IRQHandler:
SPI0_IRQHandler:
BRAKE0_IRQHandler:
PWM0P0_IRQHandler:
PWM0P1_IRQHandler:
PWM0P2_IRQHandler:
TMR0_IRQHandler:
TMR1_IRQHandler:
TMR2_IRQHandler:
TMR3_IRQHandler:
UART0_IRQHandler:
UART1_IRQHandler:
I2C0_IRQHandler:
PDMA0_IRQHandler:
ADC0_IRQHandler:
ACMP01_IRQHandler:
BPWM0_IRQHandler:
LLSI0_IRQHandler:
LLSI1_IRQHandler:
CANFD00_IRQHandler:
CANFD01_IRQHandler:
CANFD10_IRQHandler:
CANFD11_IRQHandler:
CANFD20_IRQHandler:
CANFD21_IRQHandler:
USCI0_IRQHandler:
USCI1_IRQHandler:
DEFAULT_IRQHandler:
        B       .

    .align 2


// ;int32_t SH_DoCommand(int32_t n32In_R0, int32_t n32In_R1, int32_t *pn32Out_R0)
    .global     SH_DoCommand
    .global     SH_Return
    .type       SH_DoCommand, "function"
SH_DoCommand:
                BKPT   0xAB                // ; Wait ICE or HardFault
                LDR    R3, =SH_Return
                MOV    R4, lr
                BLX    R3                  // ; Call SH_Return. The return value is in R0
                BX     R4                  // ; Return value = R0

    .align 2

    .global     __PC
    .type       __PC, "function"
__PC:
                MOV     r0, lr
                BLX     lr
