;/**************************************************************************//**
; * @file     startup_m2a23.s
; * @version  V3.00
; * @brief    M2A23 Series Startup Source File for IAR Platform
; *
; * @copyright SPDX-License-Identifier: Apache-2.0
; * @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
; ******************************************************************************/

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    MODULE  ?cstartup

    ;; Forward declaration of sections.
    SECTION CSTACK:DATA:NOROOT(3) ;; 8 bytes alignment

    SECTION .intvec:CODE:NOROOT(2);; 4 bytes alignment

    EXTERN  SystemInit
    EXTERN  ProcessHardFault
    EXTERN  __iar_program_start
    PUBLIC  __vector_table
    PUBLIC  __Vectors

    DATA
__Vectors
__vector_table
    DCD     sfe(CSTACK)
    DCD     Reset_Handler

    DCD     NMI_Handler
    DCD     HardFault_Handler
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     SVC_Handler
    DCD     0
    DCD     0
    DCD     PendSV_Handler
    DCD     SysTick_Handler

    ; External Interrupts
    DCD     BOD_IRQHandler              ; Brownout low voltage detected interrupt
    DCD     IRC_IRQHandler              ; Internal RC
    DCD     PWRWU_IRQHandler            ; Power down wake up
    DCD     RAMPE_IRQHandler            ; RAM parity error
    DCD     CKFAIL_IRQHandler           ; Clock detection fail
    DCD     ISP_IRQHandler              ; ISP
    DCD     Default_Handler             ; Reserved
    DCD     Default_Handler             ; Reserved
    DCD     WDT_IRQHandler              ; Watch Dog Timer interrupt
    DCD     WWDT_IRQHandler             ; Window watchdog timer interrupt
    DCD     EINT0_IRQHandler            ; External Input 0
    DCD     EINT1_IRQHandler            ; External Input 1
    DCD     EINT2_IRQHandler            ; External Input 2
    DCD     EINT3_IRQHandler            ; External Input 3
    DCD     EINT4_IRQHandler            ; External Input 4
    DCD     EINT5_IRQHandler            ; External Input 5
    DCD     GPA_IRQHandler              ; GPIO Port A
    DCD     GPB_IRQHandler              ; GPIO Port B
    DCD     GPC_IRQHandler              ; GPIO Port C
    DCD     GPD_IRQHandler              ; GPIO Port D
    DCD     Default_Handler             ; Reserved
    DCD     GPF_IRQHandler              ; GPIO Port F
    DCD     Default_Handler             ; Reserved
    DCD     SPI0_IRQHandler             ; SPI0
    DCD     BRAKE0_IRQHandler           ; PWM0 brake
    DCD     PWM0P0_IRQHandler           ; PWM0 pair 0
    DCD     PWM0P1_IRQHandler           ; PWM0 pair 1
    DCD     PWM0P2_IRQHandler           ; PWM0 pair 2
    DCD     Default_Handler             ; Reserved
    DCD     Default_Handler             ; Reserved
    DCD     Default_Handler             ; Reserved
    DCD     Default_Handler             ; Reserved
    DCD     TMR0_IRQHandler             ; Timer 0 interrupt
    DCD     TMR1_IRQHandler             ; Timer 1 interrupt
    DCD     TMR2_IRQHandler             ; Timer 2 interrupt
    DCD     TMR3_IRQHandler             ; Timer 3 interrupt
    DCD     UART0_IRQHandler            ; UART0 interrupt
    DCD     UART1_IRQHandler            ; UART1 interrupt
    DCD     I2C0_IRQHandler             ; I2C0 interrupt
    DCD     Default_Handler             ; Reserved
    DCD     PDMA0_IRQHandler            ; Peripheral DMA 0
    DCD     Default_Handler             ; Reserved
    DCD     ADC0_IRQHandler             ; ADC0 interrupt
    DCD     Default_Handler             ; Reserved
    DCD     ACMP01_IRQHandler           ; ACMP01 interrupt
    DCD     BPWM0_IRQHandler            ; BPWM0 interrupt
    DCD     LLSI0_IRQHandler            ; LLSI0 interrupt
    DCD     LLSI1_IRQHandler            ; LLSI1 interrupt
    DCD     CANFD00_IRQHandler          ; CANFD0 interrupt source 0
    DCD     CANFD01_IRQHandler          ; CANFD0 interrupt source 1
    DCD     CANFD10_IRQHandler          ; CANFD1 interrupt source 0
    DCD     CANFD11_IRQHandler          ; CANFD1 interrupt source 1
    DCD     CANFD20_IRQHandler          ; CANFD2 interrupt source 0
    DCD     CANFD21_IRQHandler          ; CANFD2 interrupt source 1
    DCD     Default_Handler             ; Reserved
    DCD     Default_Handler             ; Reserved
    DCD     USCI0_IRQHandler            ; USCI0
    DCD     USCI1_IRQHandler            ; USCI1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
    THUMB
    PUBWEAK Reset_Handler
    SECTION .text:CODE:REORDER:NOROOT(2)   ; 4 bytes alignment
Reset_Handler

        LDR      R0, =SystemInit
        BLX      R0
        LDR      R0, =__iar_program_start
        BX       R0

    PUBWEAK HardFault_Handler
HardFault_Handler\

        MOV     R0, LR
        MRS     R1, MSP
        MRS     R2, PSP
        LDR     R3, =ProcessHardFault
        BLX     R3
        BX      R0

    PUBWEAK  SysTick_Handler
    PUBWEAK  BOD_IRQHandler
    PUBWEAK  IRC_IRQHandler
    PUBWEAK  PWRWU_IRQHandler
    PUBWEAK  RAMPE_IRQHandler
    PUBWEAK  CKFAIL_IRQHandler
    PUBWEAK  ISP_IRQHandler
    PUBWEAK  WDT_IRQHandler
    PUBWEAK  WWDT_IRQHandler
    PUBWEAK  EINT0_IRQHandler
    PUBWEAK  EINT1_IRQHandler
    PUBWEAK  EINT2_IRQHandler
    PUBWEAK  EINT3_IRQHandler
    PUBWEAK  EINT4_IRQHandler
    PUBWEAK  EINT5_IRQHandler
    PUBWEAK  GPA_IRQHandler
    PUBWEAK  GPB_IRQHandler
    PUBWEAK  GPC_IRQHandler
    PUBWEAK  GPD_IRQHandler
    PUBWEAK  GPF_IRQHandler
    PUBWEAK  SPI0_IRQHandler
    PUBWEAK  BRAKE0_IRQHandler
    PUBWEAK  PWM0P0_IRQHandler
    PUBWEAK  PWM0P1_IRQHandler
    PUBWEAK  PWM0P2_IRQHandler
    PUBWEAK  TMR0_IRQHandler
    PUBWEAK  TMR1_IRQHandler
    PUBWEAK  TMR2_IRQHandler
    PUBWEAK  TMR3_IRQHandler
    PUBWEAK  UART0_IRQHandler
    PUBWEAK  UART1_IRQHandler
    PUBWEAK  I2C0_IRQHandler
    PUBWEAK  PDMA0_IRQHandler
    PUBWEAK  ADC0_IRQHandler
    PUBWEAK  ACMP01_IRQHandler
    PUBWEAK  BPWM0_IRQHandler
    PUBWEAK  LLSI0_IRQHandler
    PUBWEAK  LLSI1_IRQHandler
    PUBWEAK  CANFD00_IRQHandler
    PUBWEAK  CANFD01_IRQHandler
    PUBWEAK  CANFD10_IRQHandler
    PUBWEAK  CANFD11_IRQHandler
    PUBWEAK  CANFD20_IRQHandler
    PUBWEAK  CANFD21_IRQHandler
    PUBWEAK  USCI0_IRQHandler
    PUBWEAK  USCI1_IRQHandler

    SECTION .text:CODE:REORDER:NOROOT(2)

;HardFault_Handler
NMI_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler
BOD_IRQHandler
IRC_IRQHandler
PWRWU_IRQHandler
RAMPE_IRQHandler
CKFAIL_IRQHandler
ISP_IRQHandler
WDT_IRQHandler
WWDT_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
EINT4_IRQHandler
EINT5_IRQHandler
GPA_IRQHandler
GPB_IRQHandler
GPC_IRQHandler
GPD_IRQHandler
GPF_IRQHandler
SPI0_IRQHandler
BRAKE0_IRQHandler
PWM0P0_IRQHandler
PWM0P1_IRQHandler
PWM0P2_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
I2C0_IRQHandler
PDMA0_IRQHandler
ADC0_IRQHandler
ACMP01_IRQHandler
BPWM0_IRQHandler
LLSI0_IRQHandler
LLSI1_IRQHandler
CANFD00_IRQHandler
CANFD01_IRQHandler
CANFD10_IRQHandler
CANFD11_IRQHandler
CANFD20_IRQHandler
CANFD21_IRQHandler
USCI0_IRQHandler
USCI1_IRQHandler
Default_Handler
    B Default_Handler


;void SH_ICE(void)
    PUBLIC    SH_ICE
SH_ICE
    CMP   R2,#0
    BEQ   SH_End
    STR   R0,[R2]   ; Save the return value to *pn32Out_R0

;void SH_End(void)
    PUBLIC    SH_End
SH_End
    MOVS   R0,#1    ; Set return value to 1
    BX     lr       ; Return


;int32_t SH_DoCommand(int32_t n32In_R0, int32_t n32In_R1, int32_t *pn32Out_R0)
    PUBLIC    SH_DoCommand
SH_DoCommand
    BKPT   0xAB             ; This instruction will cause ICE trap or system HardFault
    B      SH_ICE
SH_HardFault                ; Captured by HardFault
    MOVS   R0,#0            ; Set return value to 0
    BX     lr               ; Return


    PUBLIC    __PC
__PC
        MOV     r0, lr
        BLX     lr

    END

