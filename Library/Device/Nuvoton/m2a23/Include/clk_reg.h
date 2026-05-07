/**************************************************************************//**
 * @file     clk_reg.h
 * @version  V3.00
 * @brief    CLK register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CLK_REG_H__
#define __CLK_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif


 /******************************************************************************/
 /*                Device Specific Peripheral registers structures             */
 /******************************************************************************/

 /** @addtogroup REGISTER Control Register

   @{

 */


/*---------------------- System Clock Controller -------------------------*/
/**
    @addtogroup CLK System Clock Controller(CLK)
    Memory Mapped Structure for CLK Controller
    @{
*/

typedef struct
{


    /**
     * @var CLK_T::PWRCTL
     * Offset: 0x00  System Power-down Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTEN     |HXT Enable Bit (Write Protect)
     * |        |          |0 = 4~24 MHz External High Speed Crystal (HXT) Disabled.
     * |        |          |1 = 4~24 MHz External High Speed Crystal (HXT) Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |LXTEN     |LXT Enable Bit (Write Protect)
     * |        |          |0 = 32.768 KHz External Low Speed Crystal (LXT) Disabled.
     * |        |          |1 = 32.768 KHz External Low Speed Crystal (LXT) Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |HIRCEN    |HIRC Enable Bit (Write Protect)
     * |        |          |0 = 48 MHz internal high speed RC oscillator (HIRC) Disabled.
     * |        |          |1 = 48 MHz internal high speed RC oscillator (HIRC) Enabled.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: HIRC cannot be disabled if HCLK clock source is selected from HIRC or PLL (clock source from HIRC) or Flash ISP peripheral clock enabled.
     * |        |          |Flash ISP peripheral clock can be disabled by ISPCKEN(CLK_AHBCLK[2]).
     * |[3]     |LIRCEN    |LIRC Enable Bit (Write Protect)
     * |        |          |0 = 38.4 kHz internal low speed RC oscillator (LIRC) Disabled.
     * |        |          |1 = 38.4 kHz internal low speed RC oscillator (LIRC) Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[5]     |PDWKIEN   |Power-down Mode Wake-up Interrupt Enable Bit (Write Protect)
     * |        |          |0 = Power-down mode wake-up interrupt Disabled.
     * |        |          |1 = Power-down mode wake-up interrupt Enabled.
     * |        |          |Note 1: The interrupt will occur when both PDWKIF and PDWKIEN are high.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |PDWKIF    |Power-down Mode Wake-up Interrupt Status
     * |        |          |Set by Power-down wake-up event, it indicates that resume from Power-down mode.
     * |        |          |The flag is set if the BOD, CLKFAIL, EINT, GPIO, TMR, WDT, UART, USCI, I2C or ACMP wake-up occurred.
     * |        |          |Note 1: Write 1 to clear the bit to 0.
     * |        |          |Note 2: This bit works only if PDWKIEN (CLK_PWRCTL[5]) set to 1.
     * |[7]     |PDEN      |System Power-down Enable (Write Protect)
     * |        |          |When this bit is set to 1, Power-down mode is enabled and chip keeps active till the CPU sleep mode is also active and then the chip enters Power-down mode.
     * |        |          |When chip wakes up from Power-down mode, this bit is auto cleared.
     * |        |          |Users need to set this bit again for next Power-down.
     * |        |          |In Power-down mode, HXT and HIRC will be disabled in this mode, but LXT and LIRC are not controlled by Power-down mode.
     * |        |          |In Power-down mode, the PLL and system clock are disabled, and ignored the clock source selection.
     * |        |          |The clocks of peripheral are not controlled by Power-down mode, if the peripheral clock source is from LXT or LIRC.
     * |        |          |0 = Chip operating normally or chip in idle mode because of WFI command.
     * |        |          |1 = Chip waits CPU sleep command WFI and then enters Power-down mode.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[12:10] |HXTGAIN   |HXT Gain Control Bit (Write Protect)
     * |        |          |Gain control is used to enlarge the gain of crystal to make sure crystal work normally. 
     * |        |          |If gain control is enabled, crystal will consume more power than gain control off. 
     * |        |          |000 = HXT frequency is from 4 MHz to 8MHz.
     * |        |          |001 = HXT frequency is from 8 MHz to 12MHz.
     * |        |          |010 = HXT frequency is from 12 MHz to 16MHz.
     * |        |          |011 = HXT frequency is from 16 MHz to 24MHz.
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[15:13] |LXTGAIN   |LXT Gain Control Bit (Write Protect)
     * |        |          |User can select oscillator gain according to crystal external loading and operating temperature range.
     * |        |          |The greater gain value corresponding to stronger driving capability and higher power consumption.
     * |        |          |000 = L0 mode (ESR=35K; CL =25pF).
     * |        |          |001 = L1 mode (ESR=35K; CL =25pF).
     * |        |          |010 = L2 mode (ESR=35K; CL =25pF).
     * |        |          |011 = L3 mode (ESR=70K; CL =25pF).
     * |        |          |100 = L4 mode (ESR=70K; CL =25pF).
     * |        |          |101 = L5 mode (ESR=70K; CL =25pF).
     * |        |          |110 = L6 mode (ESR=90K; CL =25pF).
     * |        |          |111 = L7 mode (ESR=90K; CL =25pF).
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[17:16] |HIRCSTBS  |HIRC Stable Count Select (Write Protect )
     * |        |          |00 = HIRC48M stable count is 1024 clocks.
     * |        |          |01 = HIRC48M stable count is 512 clocks.
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[31]    |HXTMD     |HXT Bypass Mode (Write Protect)
     * |        |          |0 = HXT work as crystal mode. PF.2 and PF.3 are configured as external high speed crystal (HXT) pins.
     * |        |          |1 = HXT works as external clock mode. PF.3 is configured as external clock input pin.
     * |        |          |Note 1: When HXTMD = 1, PF.3 MFP should be setting as GPIO mode. The DC characteristic of XT1_IN is the same as GPIO.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGCTL register.
     * @var CLK_T::AHBCLK
     * Offset: 0x04  AHB Devices Clock Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |PDMACKEN  |PDMA Controller Clock Enable Bit
     * |        |          |0 = PDMA peripheral clock Disabled.
     * |        |          |1 = PDMA peripheral clock Enabled.
     * |[2]     |ISPCKEN   |Flash ISP Controller Clock Enable Bit
     * |        |          |0 = Flash ISP peripheral clock Disabled.
     * |        |          |1 = Flash ISP peripheral clock Enabled.
     * |4]      |STCKEN    |System Tick Clock Enable Bit
     * |        |          |0 = System tick clock Disabled.
     * |        |          |1 = System tick clock Enabled.
     * |[7]     |CRCCKEN   |CRC Generator Controller Clock Enable Bit
     * |        |          |0 = CRC peripheral clock Disabled.
     * |        |          |1 = CRC peripheral clock Enabled.
     * |[8]     |CANFD0CKEN|CANFD0 Clock Enable Bit
     * |        |          |0 = CANFD0 clock Disabled.
     * |        |          |1 = CANFD0 clock Enabled.
     * |[9]     |CANFD1CKEN|CANFD1 Clock Enable Bit
     * |        |          |0 = CANFD1 clock Disabled.
     * |        |          |1 = CANFD1 clock Enabled.
     * |[10]    |CANFD2CKEN|CANFD2 Clock Enable Bit
     * |        |          |0 = CANFD2 clock Disabled.
     * |        |          |1 = CANFD2 clock Enabled.
     * |[15]    |FMCIDLE   |Flash Memory Controller Clock Enable Bit in IDLE Mode
     * |        |          |0 = FMC peripheral clock Disabled when chip operating at IDLE mode.
     * |        |          |1 = FMC peripheral clock Enabled when chip operating at IDLE mode.
     * |[16]    |CANRAM0EN |CANFD0 Message SRAM Clock Enable Bit
     * |        |          |0 = CANFD0 Message SRAM clock Disabled.
     * |        |          |1 = CANFD0 Message SRAM clock Enabled.
     * |[17]    |CANRAM1EN |CANFD1 Message SRAM Clock Enable Bit
     * |        |          |0 = CANFD1 Message SRAM clock Disabled.
     * |        |          |1 = CANFD1 Message SRAM clock Enabled.
     * |[18]    |CANRAM2EN |CANFDw Message SRAM Clock Enable Bit
     * |        |          |0 = CANFD2 Message SRAM clock Disabled.
     * |        |          |1 = CANFD2 Message SRAM clock Enabled.
     * |[24]    |GPIOACKEN |General Purpose I/O PA Group Clock Enable Bit
     * |        |          |0 = GPIO PA group clock Disabled.
     * |        |          |1 = GPIO PA group clock Enabled.
     * |[25]    |GPIOBCKEN |General Purpose I/O PB Group Clock Enable Bit
     * |        |          |0 = GPIO PB group clock Disabled.
     * |        |          |1 = GPIO PB group clock Enabled.
     * |[26]    |GPIOCCKEN |General Purpose I/O PC Group Clock Enable Bit
     * |        |          |0 = GPIO PC group clock Disabled.
     * |        |          |1 = GPIO PC group clock Enabled.
     * |[27]    |GPIODCKEN |General Purpose I/O PD Group Clock Enable Bit
     * |        |          |0 = GPIO PD group clock Disabled.
     * |        |          |1 = GPIO PD group clock Enabled.
     * |[29]    |GPIOFCKEN |General Purpose I/O PF Group Clock Enable Bit
     * |        |          |0 = GPIO PF group clock Disabled.
     * |        |          |1 = GPIO PF group clock Enabled.
     * @var CLK_T::APBCLK0
     * Offset: 0x08  APB Devices Clock Enable Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDTCKEN   |Watchdog Timer Clock Enable Bit (Write Protect)
     * |        |          |0 = Watchdog Timer Clock Disabled.
     * |        |          |1 = Watchdog Timer Clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |WWDTCKEN  |Window Watchdog Timer Clock Enable Bit (Write Protect)
     * |        |          |0 = Window Watchdog Timer Clock Disabled.
     * |        |          |1 = Window Watchdog Timer Clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |TMR0CKEN  |Timer0 Clock Enable Bit
     * |        |          |0 = Timer0 Clock Disabled.
     * |        |          |1 = Timer0 Clock Enabled.
     * |[3]     |TMR1CKEN  |Timer1 Clock Enable Bit
     * |        |          |0 = Timer1 Clock Disabled.
     * |        |          |1 = Timer1 Clock Enabled.
     * |[4]     |TMR2CKEN  |Timer2 Clock Enable Bit
     * |        |          |0 = Timer2 Clock Disabled.
     * |        |          |1 = Timer2 Clock Enabled.
     * |[5]     |TMR3CKEN  |Timer3 Clock Enable Bit
     * |        |          |0 = Timer3 Clock Disabled.
     * |        |          |1 = Timer3 Clock Enabled.
     * |[6]     |CLKOCKEN  |CLKO Clock Enable Bit
     * |        |          |0 = CLKO Clock Disabled.
     * |        |          |1 = CLKO Clock Enabled.
     * |[8]     |I2C0CKEN  |I2C0 Clock Enable Bit
     * |        |          |0 = I2C0 Clock Disabled.
     * |        |          |1 = I2C0 Clock Enabled.
     * |[12]    |SPI0CKEN  |SPI0 Clock Enable Bit
     * |        |          |0 = SPI0 Clock Disabled.
     * |        |          |1 = SPI0 Clock Enabled.
     * |[16]    |UART0CKEN |UART0 Clock Enable Bit
     * |        |          |0 = UART0 clock Disabled.
     * |        |          |1 = UART0 clock Enabled.
     * |[17]    |UART1CKEN |UART1 Clock Enable Bit
     * |        |          |0 = UART1 clock Disabled.
     * |        |          |1 = UART1 clock Enabled.
     * |[28]    |ADC0CKEN  |ADC0 Clock Enable Bit
     * |        |          |0 = ADC0 clock Disabled.
     * |        |          |1 = ADC0 clock Enabled.
     * |[30]    |ACMP01CKEN|Analog Comparator 0/1 Clock Enable Bit
     * |        |          |0 = Analog comparator 0/1 clock Disabled.
     * |        |          |1 = Analog comparator 0/1 clock Enabled.
     * @var CLK_T::APBCLK1
     * Offset: 0x0C  APB Devices Clock Enable Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PWM0CKEN  |PWM0 Clock Enable Bit
     * |        |          |0 = PWM0 clock Disabled.
     * |        |          |1 = PWM0 clock Enabled.
     * |[4]     |BPWM0CKEN |BPWM0 Clock Enable Bit
     * |        |          |0 = BPWM0 clock Disabled.
     * |        |          |1 = BPWM0 clock Enabled.
     * |[8]     |USCI0CKEN |USCI0 Clock Enable Bit
     * |        |          |0 = USCI0 clock Disabled.
     * |        |          |1 = USCI0 clock Enabled.
     * |[9]     |USCI1CKEN |USCI1 Clock Enable Bit
     * |        |          |0 = USCI1 clock Disabled.
     * |        |          |1 = USCI1 clock Enabled.
     * |[16]    |LLSI0CKEN |LLSI0 Clock Enable Bit
     * |        |          |0 = LLSI0 Clock Disabled.
     * |        |          |1 = LLSI0 Clock Enabled.
     * |[17]    |LLSI1CKEN |LLSI1 Clock Enable Bit
     * |        |          |0 = LLSI1 Clock Disabled.
     * |        |          |1 = LLSI1 Clock Enabled.
     * @var CLK_T::CLKSEL0
     * Offset: 0x10  Clock Source Select Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |HCLKSEL   |HCLK Clock Source Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |000 = Clock source from HXT.
     * |        |          |001 = Clock source from LXT.
     * |        |          |010 = Clock source from PLL/2 clock.
     * |        |          |011 = Clock source from LIRC.
     * |        |          |111 = Clock source from HIRC clock.
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[5:3]   |STCLKSEL  |Cortex-M23 SysTick Clock Source Selection (Write Protect)
     * |        |          |If SYST_CTRL[2]=0, SysTick uses listed clock source below.
     * |        |          |000 = Clock source from HXT.
     * |        |          |001 = Clock source from LXT.
     * |        |          |010 = Clock source from HXT/2.
     * |        |          |011 = Clock source from HCLK/2.
     * |        |          |111 = Clock source from HIRC/2.
     * |        |          |Note 1: if SysTick clock source is not from HCLK (i.e. SYST_CTRL[2] = 0), SysTick clock source must less than or equal to HCLK/2.
     * |        |          |Note 2: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[25:24] |CANFD0SEL |CANFD0 Clock Source Selection (Write Protect)
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from PLL/2.
     * |        |          |10 = Clock source from HCLK.
     * |        |          |11 = Clock source from 48 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[27:26] |CANFD1SEL |CANFD1 Clock Source Selection (Write Protect)
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from PLL/2.
     * |        |          |10 = Clock source from HCLK.
     * |        |          |11 = Clock source from 48 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[29:28] |CANFD2SEL |CANFD2 Clock Source Selection (Write Protect)
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
     * |        |          |01 = Clock source from PLL/2.
     * |        |          |10 = Clock source from HCLK.
     * |        |          |11 = Clock source from 48 MHz internal high speed RC oscillator (HIRC).
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * @var CLK_T::CLKSEL1
     * Offset: 0x14  Clock Source Select Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |WDTSEL    |Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |00 = Reserved.
     * |        |          |01 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |10 = Clock source from HCLK/2048 clock.
     * |        |          |11 = Clock source from 38.4 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[3:2]   |WWDTSEL   |Window Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |10 = Clock source from HCLK/2048 clock.
     * |        |          |11 = Clock source from 38.4 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[6:4]   |CLKOSEL   |Clock Divider Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from HCLK.
     * |        |          |011 = Clock source from LIRC clock.
     * |        |          |100 = Clock source from PLL/2.
     * |        |          |101 = Clock source from HIRC clock.
     * |        |          |Others = Reserved.
     * |[10:8]  |TMR0SEL   |TIMER0 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock T0 pin.
     * |        |          |101 = Clock source from 38.4 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from HIRC clock.
     * |        |          |Others = Reserved.
     * |[14:12] |TMR1SEL   |TIMER1 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock T1 pin.
     * |        |          |101 = Clock source from 38.4 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from HIRC clock.
     * |        |          |Others = Reserved.
     * |[18:16] |TMR2SEL   |TIMER2 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock T2 pin.
     * |        |          |101 = Clock source from 38.4 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from HIRC clock.
     * |        |          |Others = Reserved.
     * |[22:20] |TMR3SEL   |TIMER3 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock T3 pin.
     * |        |          |101 = Clock source from 38.4 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from HIRC clock.
     * |        |          |Others = Reserved.
     * @var CLK_T::CLKSEL2
     * Offset: 0x18  Clock Source Select Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |UART0SEL  |UART0 Clock Source Selection
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |01 = Clock source from PLL clock.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |11 = Clock source from HIRC clock.
     * |[3:2]   |UART1SEL  |UART1 Clock Source Selection
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |01 = Clock source from PLL clock.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |11 = Clock source from HIRC clock.
     * |[25:24] |SPI0SEL   |SPI0 Clock Source Selection
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |01 = Clock source from PLL/2 clock.
     * |        |          |10 = Clock source from PCLK1.
     * |        |          |11 = Clock source from HIRC clock.
     * @var CLK_T::CLKSEL3
     * Offset: 0x1C  Clock Source Select Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |ADC0SEL   |ADC0 Clock Source Selection
     * |        |          |00 = Reserved.
     * |        |          |01 = Clock source from PLL.
     * |        |          |10 = Clock source from HCLK.
     * |        |          |11 = Clock source from HIRC clock.
     * |[4]     |PWM0SEL   |PWM0 Clock Source Selection
     * |        |          |The peripheral clock source of PWM0 is defined by PWM0SEL.
     * |        |          |0 = Clock source from PLL.
     * |        |          |1 = Clock source from PCLK0.
     * |[4]     |BPWM0SEL  |BPWM0 Clock Source Selection
     * |        |          |The peripheral clock source of BPWM0 is defined by BPWM0SEL.
     * |        |          |0 = Clock source from PLL.
     * |        |          |1 = Clock source from PCLK0.
     * @var CLK_T::CLKDIV0
     * Offset: 0x20  Clock Divider Number Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |HCLKDIV   |HCLK Clock Divide Number From HCLK Clock Source
     * |        |          |HCLK clock frequency = (HCLK clock source frequency) / (HCLKDIV + 1).
     * |[11:8]  |UART0DIV  |UART0 Clock Divide Number From UART0 Clock Source
     * |        |          |UART0 clock frequency = (UART0 clock source frequency) / (UART0DIV + 1).
     * |[15:12] |UART1DIV  |UART1 Clock Divide Number From UART1 Clock Source
     * |        |          |UART1 clock frequency = (UART1 clock source frequency) / (UART1DIV + 1).
     * |[23:16] |ADC0DIV   |ADC0 Clock Divide Number From ADC0 Clock Source
     * |        |          |ADC0 clock frequency = (ADC0 clock source frequency) / (ADC0DIV + 1).
     * @var CLK_T::CLKDIV1
     * Offset: 0x24  Clock Divider Number Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |CANFD0DIV |CANFD0 Clock Divide Number From CANFD0 Clock Source
     * |        |          |CANFD0 clock frequency = (CANFD0 clock source frequency) / (CANFD0DIV + 1).
     * |[7:4]   |CANFD1DIV |CANFD1 Clock Divide Number From CANFD1 Clock Source
     * |        |          |CANFD1 clock frequency = (CANFD1 clock source frequency) / (CANFD1DIV + 1).
     * |[3:0]   |CANFD2DIV |CANFD2 Clock Divide Number From CANFD2 Clock Source
     * |        |          |CANFD2 clock frequency = (CANFD2 clock source frequency) / (CANFD2DIV + 1).
     * @var CLK_T::PCLKDIV
     * Offset: 0x34  APB Clock Divider Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |APB0DIV   |APB0 Clock Divider
     * |        |          |APB0 clock can be divided from HCLK.
     * |        |          |000 = PCLK0 frequency is HCLK.
     * |        |          |001 = PCLK0 frequency is 1/2 HCLK.
     * |        |          |Others = Reserved.
     * |[6:4]   |APB1DIV   |APB1 Clock Divider
     * |        |          |APB1 clock can be divided from HCLK.
     * |        |          |000 = PCLK1 frequency is HCLK.
     * |        |          |001 = PCLK1 frequency is 1/2 HCLK.
     * |        |          |Others = Reserved.
     * @var CLK_T::PLLCTL
     * Offset: 0x40  PLL Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |FBDIV     |PLL Feedback Divider Control (Write Protect)
     * |        |          |Refer to the PLL formulas.
     * |[13:9]  |INDIV     |PLL Input Divider Control (Write Protect)
     * |        |          |Refer to the PLL formulas.
     * |[15:14] |OUTDIV    |PLL Output Divider Control (Write Protect)
     * |        |          |Refer to the PLL formulas.
     * |[16]    |PD        |Power-down Mode (Write Protect)
     * |        |          |If set PDEN(CLK_PWRCTL[7]) bit to 1, the PLL will enter Power-down mode, too.
     * |        |          |0 = PLL is in normal mode.
     * |        |          |1 = PLL is in Power-down mode (default).
     * |[17]    |BP        |PLL Bypass Control (Write Protect)
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock.
     * |[18]    |OE        |PLL FOUT Enable Control (Write Protect)
     * |        |          |0 = PLL FOUT Enabled.
     * |        |          |1 = PLL FOUT is fixed low.
     * |[19]    |PLLSRC    |PLL Source Clock Selection (Write Protect)
     * |        |          |0 = PLL source clock from external 4~24 MHz high-speed crystal (HXT).
     * |        |          |1 = PLL source clock from 48 MHz internal high-speed oscillator divided by 2 (HIRC/2).
     * |[23]    |STBSEL    |PLL Stable Counter Selection (Write Protect)
     * |        |          |0 = PLL stable time is 6144 PLL source clock (suitable for source clock is equal to or less than 12MHz).
     * |        |          |1 = PLL stable time is 12288 PLL source clock (suitable for source clock is larger than 12MHz).
     * @var CLK_T::STATUS
     * Offset: 0x50  Clock Status Monitor Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTSTB    |HXT Clock Source Stable Flag (Read Only)
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock is not stable or disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock is stable and enabled.
     * |[1]     |LXTSTB    |LXT Clock Source Stable Flag (Read Only)
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock is not stable or disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock is stabled and enabled.
     * |[2]     |PLLSTB    |Internal PLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = Internal PLL clock is not stable or disabled.
     * |        |          |1 = Internal PLL clock is stable and enabled.
     * |[3]     |LIRCSTB   |LIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = 38.4 kHz internal low speed RC oscillator (LIRC) clock is not stable or disabled.
     * |        |          |1 = 38.4 kHz internal low speed RC oscillator (LIRC) clock is stable and enabled.
     * |[4]     |HIRCSTB   |HIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = HIRC clock is not stable or disabled.
     * |        |          |1 = HIRC clock is stable and enabled.
     * |[7]     |CLKSFAIL  |Clock Switching Fail Flag (Read Only)
     * |        |          |This bit is updated when software switches system clock source.
     * |        |          |If switch target clock is stable, this bit will be set to 0.
     * |        |          |If switch target clock is not stable, this bit will be set to 1.
     * |        |          |0 = Clock switching success.
     * |        |          |1 = Clock switching failure.
     * |        |          |Note: After selected clock source is stable, hardware will switch system clock to selected clock automatically, and CLKSFAIL will be cleared automatically by hardware.
     * @var CLK_T::CLKOCTL
     * Offset: 0x60  Clock Output Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |FREQSEL   |Clock Output Frequency Selection
     * |        |          |The formula of output frequency is Fout = Fin/(2^(N+1)).
     * |        |          |Fin is the input clock frequency.
     * |        |          |Fout is the frequency of divider output clock.
     * |        |          |N is the 4-bit value of FREQSEL[3:0].
     * |[4]     |CLKOEN    |Clock Output Enable Bit
     * |        |          |0 = Clock Output function Disabled.
     * |        |          |1 = Clock Output function Enabled.
     * |[5]     |DIV1EN    |Clock Output Divide One Enable Bit
     * |        |          |0 = Clock Output will output clock with source frequency divided by FREQSEL.
     * |        |          |1 = Clock Output will output clock with source frequency.
     * @var CLK_T::CLKDCTL
     * Offset: 0x70  Clock Fail Detector Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4]     |HXTFDEN   |HXT Clock Fail Detector Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock Fail detector Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock Fail detector Enabled.
     * |[5]     |HXTFIEN   |HXT Clock Fail Interrupt Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock Fail interrupt Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock Fail interrupt Enabled.
     * |[12]    |LXTFDEN   |LXT Clock Fail Detector Enable Bit
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail detector Disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail detector Enabled.
     * |[13]    |LXTFIEN   |LXT Clock Fail Interrupt Enable Bit
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail interrupt Disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail interrupt Enabled.
     * |[16]    |HXTFQDEN  |HXT Clock Frequency Monitor Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor Enabled.
     * |[17]    |HXTFQIEN  |HXT Clock Frequency Monitor Interrupt Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor fail interrupt Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor fail interrupt Enabled.
     * @var CLK_T::CLKDSTS
     * Offset: 0x74  Clock Fail Detector Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTFIF    |HXT Clock Fail Interrupt Flag (Write Protect)
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock normal.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock stop.
     * |        |          |Note 1: This bit can be cleared to 0 by software writing 1.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |LXTFIF    |LXT Clock Fail Interrupt Flag (Write Protect)
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock normal.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock stop.
     * |        |          |Note 1: This bit can be cleared to 0 by software writing 1.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[8]     |HXTFQIF   |HXT Clock Frequency Monitor Interrupt Flag (Write Protect)
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock normal.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency abnormal.
     * |        |          |Note 1: This bit can be cleared to 0 by software writing 1.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var CLK_T::CDUPB
     * Offset: 0x78  Clock Frequency Detector Upper Boundary Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |UPERBD    |HXT Clock Frequency Detector Upper Boundary
     * |        |          |The bits define the high value of frequency monitor window.
     * |        |          |When HXT frequency monitor value higher than this register, the HXT frequency detect fail interrupt flag will set to 1.
     * |        |          |Note: The frequency out of range will be asserted when HIRC_period*1024 > HXT_period*CLK_DUPB or HIRC_period*1024 < HXT_period*CLK_CDLOWB.
     * @var CLK_T::CDLOWB
     * Offset: 0x7C  Clock Frequency Detector Low Boundary Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[10:0]  |LOWERBD   |HXT Clock Frequency Detector Low Boundary
     * |        |          |The bits define the low value of frequency monitor window.
     * |        |          |When HXT frequency monitor value lower than this register, the HXT frequency detect fail interrupt flag will set to 1.
     * |        |          |Note: The frequency out of range will be asserted when HIRC_period*1024 > HXT_period*CLK_DUPB or HIRC_period*1024 < HXT_period*CLK_CDLOWB.
     * @var CLK_T::STOPREQ
     * Offset: 0x80  Clock Stop Request Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CANFD0REQ |CANFD0 Clock Stop Request
     * |        |          |This bit is used to stop CANFD0 clock.
     * |        |          |0 = CANFD0 clock is not stopped by this bit. (default)
     * |        |          |1 = Set this bit and check the CANFD0ACK(CLK_STOPACK[0]) is 1, then CANFD0 clock stop.
     * |[1]     |CANFD1REQ |CANFD1 Clock Stop Request
     * |        |          |This bit is used to stop CANFD1 clock.
     * |        |          |0 = CANFD1 clock is not stopped by this bit. (default)
     * |        |          |1 = Set this bit and check the CANFD1ACK(CLK_STOPACK[1]) is 1, then CANFD1 clock stop.
     * |[2]     |CANFD2REQ |CANFD2 Clock Stop Request
     * |        |          |This bit is used to stop CANFD2 clock.
     * |        |          |0 = CANFD2 clock is not stopped by this bit. (default)
     * |        |          |1 = Set this bit and check the CANFD2ACK(CLK_STOPACK[2]) is 1, then CANFD2 clock stop.
     * @var CLK_T::STOPACK
     * Offset: 0x80  Clock Stop Acknowledge Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CANFD0ACK |CANFD0 Clock Stop Acknowledge (Read Only)
     * |        |          |This bit is used to check CANFD0 clock stop by setting CANFD0REQ(CLK_STOPREQ[0]).
     * |        |          |0 = CANFD0 clock not stopped.
     * |        |          |1 = CANFD0 clock stopped.
     * |[1]     |CANFD1ACK |CANFD1 Clock Stop Acknowledge (Read Only)
     * |        |          |This bit is used to check CANFD1 clock stop by setting CANFD1REQ(CLK_STOPREQ[1]).
     * |        |          |0 = CANFD0 clock not stopped.
     * |        |          |1 = CANFD0 clock stopped.
     * |[2]     |CANFD2ACK |CANFD2 Clock Stop Acknowledge (Read Only)
     * |        |          |This bit is used to check CANFD2 clock stop by setting CANFD2REQ(CLK_STOPREQ[0]).
     * |        |          |0 = CANFD2 clock not stopped.
     * |        |          |1 = CANFD2 clock stopped.
     */


    __IO uint32_t PWRCTL;                /*!< [0x0000] System Power-down Control Register                               */
    __IO uint32_t AHBCLK;                /*!< [0x0004] AHB Devices Clock Enable Control Register                        */
    __IO uint32_t APBCLK0;               /*!< [0x0008] APB Devices Clock Enable Control Register 0                      */
    __IO uint32_t APBCLK1;               /*!< [0x000c] APB Devices Clock Enable Control Register 1                      */
    __IO uint32_t CLKSEL0;               /*!< [0x0010] Clock Source Select Control Register 0                           */
    __IO uint32_t CLKSEL1;               /*!< [0x0014] Clock Source Select Control Register 1                           */
    __IO uint32_t CLKSEL2;               /*!< [0x0018] Clock Source Select Control Register 2                           */
    __IO uint32_t CLKSEL3;               /*!< [0x001c] Clock Source Select Control Register 3                           */
    __IO uint32_t CLKDIV0;               /*!< [0x0020] Clock Divider Number Register 0                                  */
    __IO uint32_t CLKDIV1;               /*!< [0x0024] Clock Divider Number Register 1                                  */
    __I  uint32_t RESERVE0[3];
    __IO uint32_t PCLKDIV;               /*!< [0x0034] APB Clock Divider Register                                       */
    __I  uint32_t RESERVE1[2];
    __IO uint32_t PLLCTL;                /*!< [0x0040] PLL Control Register                                             */
    __I  uint32_t RESERVE2[3];
    __I  uint32_t STATUS;                /*!< [0x0050] Clock Status Monitor Register                                    */
    __I  uint32_t RESERVE3[3];
    __IO uint32_t CLKOCTL;               /*!< [0x0060] Clock Output Control Register                                    */
    __I  uint32_t RESERVE4[3];
    __IO uint32_t CLKDCTL;               /*!< [0x0070] Clock Fail Detector Control Register                             */
    __IO uint32_t CLKDSTS;               /*!< [0x0074] Clock Fail Detector Status Register                              */
    __IO uint32_t CDUPB;                 /*!< [0x0078] Clock Frequency Range Detector Upper Boundary Register           */
    __IO uint32_t CDLOWB;                /*!< [0x007c] Clock Frequency Range Detector Lower Boundary Register           */
    __IO uint32_t STOPREQ;               /*!< [0x0080] Clock Stop Request Register                                      */
    __I  uint32_t STOPACK;               /*!< [0x0084] Clock Stop Acknowledge Register                                  */


} CLK_T;

/**
    @addtogroup CLK_CONST CLK Bit Field Definition
    Constant Definitions for CLK Controller
    @{
*/

#define CLK_PWRCTL_HXTEN_Pos             (0)                                               /*!< CLK_T::PWRCTL: HXTEN Position          */
#define CLK_PWRCTL_HXTEN_Msk             (0x1ul << CLK_PWRCTL_HXTEN_Pos)                   /*!< CLK_T::PWRCTL: HXTEN Mask              */

#define CLK_PWRCTL_LXTEN_Pos             (1)                                               /*!< CLK_T::PWRCTL: LXTEN Position          */
#define CLK_PWRCTL_LXTEN_Msk             (0x1ul << CLK_PWRCTL_LXTEN_Pos)                   /*!< CLK_T::PWRCTL: LXTEN Mask              */

#define CLK_PWRCTL_HIRCEN_Pos            (2)                                               /*!< CLK_T::PWRCTL: HIRCEN Position         */
#define CLK_PWRCTL_HIRCEN_Msk            (0x1ul << CLK_PWRCTL_HIRCEN_Pos)                  /*!< CLK_T::PWRCTL: HIRCEN Mask             */

#define CLK_PWRCTL_LIRCEN_Pos            (3)                                               /*!< CLK_T::PWRCTL: LIRCEN Position         */
#define CLK_PWRCTL_LIRCEN_Msk            (0x1ul << CLK_PWRCTL_LIRCEN_Pos)                  /*!< CLK_T::PWRCTL: LIRCEN Mask             */

#define CLK_PWRCTL_PDWKIEN_Pos           (5)                                               /*!< CLK_T::PWRCTL: PDWKIEN Position        */
#define CLK_PWRCTL_PDWKIEN_Msk           (0x1ul << CLK_PWRCTL_PDWKIEN_Pos)                 /*!< CLK_T::PWRCTL: PDWKIEN Mask            */

#define CLK_PWRCTL_PDWKIF_Pos            (6)                                               /*!< CLK_T::PWRCTL: PDWKIF Position         */
#define CLK_PWRCTL_PDWKIF_Msk            (0x1ul << CLK_PWRCTL_PDWKIF_Pos)                  /*!< CLK_T::PWRCTL: PDWKIF Mask             */

#define CLK_PWRCTL_PDEN_Pos              (7)                                               /*!< CLK_T::PWRCTL: PDEN Position           */
#define CLK_PWRCTL_PDEN_Msk              (0x1ul << CLK_PWRCTL_PDEN_Pos)                    /*!< CLK_T::PWRCTL: PDEN Mask               */

#define CLK_PWRCTL_HXTGAIN_Pos           (10)                                              /*!< CLK_T::PWRCTL: HXTGAIN Position        */
#define CLK_PWRCTL_HXTGAIN_Msk           (0x7ul << CLK_PWRCTL_HXTGAIN_Pos)                 /*!< CLK_T::PWRCTL: HXTGAIN Mask            */

#define CLK_PWRCTL_LXTGAIN_Pos           (13)                                              /*!< CLK_T::PWRCTL: LXTGAIN Position        */
#define CLK_PWRCTL_LXTGAIN_Msk           (0x7ul << CLK_PWRCTL_LXTGAIN_Pos)                 /*!< CLK_T::PWRCTL: LXTGAIN Mask            */

#define CLK_PWRCTL_HIRCSTB_Pos           (16)                                              /*!< CLK_T::PWRCTL: HIRCSTB Position        */
#define CLK_PWRCTL_HIRCSTB_Msk           (0x3ul << CLK_PWRCTL_HIRCSTB_Pos)                 /*!< CLK_T::PWRCTL: HIRCSTB Mask            */

#define CLK_PWRCTL_HXTMD_Pos             (31)                                              /*!< CLK_T::PWRCTL: HXTMD Position          */
#define CLK_PWRCTL_HXTMD_Msk             (0x1ul << CLK_PWRCTL_HXTMD_Pos)                   /*!< CLK_T::PWRCTL: HXTMD Mask              */

#define CLK_AHBCLK_PDMACKEN_Pos          (1)                                               /*!< CLK_T::AHBCLK: PDMACKEN Position       */
#define CLK_AHBCLK_PDMACKEN_Msk          (0x1ul << CLK_AHBCLK_PDMACKEN_Pos)                /*!< CLK_T::AHBCLK: PDMACKEN Mask           */
#define CLK_AHBCLK_PDMA0CKEN_Pos         (1)                                               /*!< CLK_T::AHBCLK: PDMA0CKEN Position      */
#define CLK_AHBCLK_PDMA0CKEN_Msk         (0x1ul << CLK_AHBCLK_PDMA0CKEN_Pos)               /*!< CLK_T::AHBCLK: PDMA0CKEN Mask          */

#define CLK_AHBCLK_ISPCKEN_Pos           (2)                                               /*!< CLK_T::AHBCLK: ISPCKEN Position        */
#define CLK_AHBCLK_ISPCKEN_Msk           (0x1ul << CLK_AHBCLK_ISPCKEN_Pos)                 /*!< CLK_T::AHBCLK: ISPCKEN Mask            */

#define CLK_AHBCLK_STCKEN_Pos            (4)                                               /*!< CLK_T::AHBCLK: STCKEN Position         */
#define CLK_AHBCLK_STCKEN_Msk            (0x1ul << CLK_AHBCLK_STCKEN_Pos)                  /*!< CLK_T::AHBCLK: STCKEN Mask             */

#define CLK_AHBCLK_CRCCKEN_Pos           (7)                                               /*!< CLK_T::AHBCLK: CRCCKEN Position        */
#define CLK_AHBCLK_CRCCKEN_Msk           (0x1ul << CLK_AHBCLK_CRCCKEN_Pos)                 /*!< CLK_T::AHBCLK: CRCCKEN Mask            */

#define CLK_AHBCLK_CANFD0CKEN_Pos        (8)                                               /*!< CLK_T::AHBCLK: CANFD0CKEN Position     */
#define CLK_AHBCLK_CANFD0CKEN_Msk        (0x1ul << CLK_AHBCLK_CANFD0CKEN_Pos)              /*!< CLK_T::AHBCLK: CANFD0CKEN Mask         */

#define CLK_AHBCLK_CANFD1CKEN_Pos        (9)                                               /*!< CLK_T::AHBCLK: CANFD1CKEN Position     */
#define CLK_AHBCLK_CANFD1CKEN_Msk        (0x1ul << CLK_AHBCLK_CANFD1CKEN_Pos)              /*!< CLK_T::AHBCLK: CANFD1CKEN Mask         */

#define CLK_AHBCLK_CANFD2CKEN_Pos        (10)                                              /*!< CLK_T::AHBCLK: CANFD2CKEN Position     */
#define CLK_AHBCLK_CANFD2CKEN_Msk        (0x1ul << CLK_AHBCLK_CANFD2CKEN_Pos)              /*!< CLK_T::AHBCLK: CANFD2CKEN Mask         */

#define CLK_AHBCLK_FMCIDLE_Pos           (15)                                              /*!< CLK_T::AHBCLK: FMCIDLE Position        */
#define CLK_AHBCLK_FMCIDLE_Msk           (0x1ul << CLK_AHBCLK_FMCIDLE_Pos)                 /*!< CLK_T::AHBCLK: FMCIDLE Mask            */

#define CLK_AHBCLK_CANRAM0EN_Pos         (16)                                              /*!< CLK_T::AHBCLK: CANRAM0EN Position      */
#define CLK_AHBCLK_CANRAM0EN_Msk         (0x1ul << CLK_AHBCLK_CANRAM0EN_Pos)               /*!< CLK_T::AHBCLK: CANRAM0EN Mask          */

#define CLK_AHBCLK_CANRAM1EN_Pos         (17)                                              /*!< CLK_T::AHBCLK: CANRAM1EN Position      */
#define CLK_AHBCLK_CANRAM1EN_Msk         (0x1ul << CLK_AHBCLK_CANRAM1EN_Pos)               /*!< CLK_T::AHBCLK: CANRAM1EN Mask          */

#define CLK_AHBCLK_CANRAM2EN_Pos         (18)                                              /*!< CLK_T::AHBCLK: CANRAM2EN Position      */
#define CLK_AHBCLK_CANRAM2EN_Msk         (0x1ul << CLK_AHBCLK_CANRAM2EN_Pos)               /*!< CLK_T::AHBCLK: CANRAM2EN Mask          */

#define CLK_AHBCLK_GPIOACKEN_Pos         (24)                                              /*!< CLK_T::AHBCLK: GPIOACKEN Position      */
#define CLK_AHBCLK_GPIOACKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOACKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOACKEN Mask          */

#define CLK_AHBCLK_GPIOBCKEN_Pos         (25)                                              /*!< CLK_T::AHBCLK: GPIOBCKEN Position      */
#define CLK_AHBCLK_GPIOBCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOBCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOBCKEN Mask          */

#define CLK_AHBCLK_GPIOCCKEN_Pos         (26)                                              /*!< CLK_T::AHBCLK: GPIOCCKEN Position      */
#define CLK_AHBCLK_GPIOCCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOCCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOCCKEN Mask          */

#define CLK_AHBCLK_GPIODCKEN_Pos         (27)                                              /*!< CLK_T::AHBCLK: GPIODCKEN Position      */
#define CLK_AHBCLK_GPIODCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIODCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIODCKEN Mask          */

#define CLK_AHBCLK_GPIOFCKEN_Pos         (29)                                              /*!< CLK_T::AHBCLK: GPIOFCKEN Position      */
#define CLK_AHBCLK_GPIOFCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOFCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOFCKEN Mask          */

#define CLK_APBCLK0_WDTCKEN_Pos          (0)                                               /*!< CLK_T::APBCLK0: WDTCKEN Position       */
#define CLK_APBCLK0_WDTCKEN_Msk          (0x1ul << CLK_APBCLK0_WDTCKEN_Pos)                /*!< CLK_T::APBCLK0: WDTCKEN Mask           */

#define CLK_APBCLK0_WWDTCKEN_Pos         (1)                                               /*!< CLK_T::APBCLK0: WWDTCKEN Position      */
#define CLK_APBCLK0_WWDTCKEN_Msk         (0x1ul << CLK_APBCLK0_WWDTCKEN_Pos)               /*!< CLK_T::APBCLK0: WWDTCKEN Mask          */

#define CLK_APBCLK0_TMR0CKEN_Pos         (2)                                               /*!< CLK_T::APBCLK0: TMR0CKEN Position      */
#define CLK_APBCLK0_TMR0CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR0CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR0CKEN Mask          */

#define CLK_APBCLK0_TMR1CKEN_Pos         (3)                                               /*!< CLK_T::APBCLK0: TMR1CKEN Position      */
#define CLK_APBCLK0_TMR1CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR1CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR1CKEN Mask          */

#define CLK_APBCLK0_TMR2CKEN_Pos         (4)                                               /*!< CLK_T::APBCLK0: TMR2CKEN Position      */
#define CLK_APBCLK0_TMR2CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR2CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR2CKEN Mask          */

#define CLK_APBCLK0_TMR3CKEN_Pos         (5)                                               /*!< CLK_T::APBCLK0: TMR3CKEN Position      */
#define CLK_APBCLK0_TMR3CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR3CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR3CKEN Mask          */

#define CLK_APBCLK0_CLKOCKEN_Pos         (6)                                               /*!< CLK_T::APBCLK0: CLKOCKEN Position      */
#define CLK_APBCLK0_CLKOCKEN_Msk         (0x1ul << CLK_APBCLK0_CLKOCKEN_Pos)               /*!< CLK_T::APBCLK0: CLKOCKEN Mask          */

#define CLK_APBCLK0_I2C0CKEN_Pos         (8)                                               /*!< CLK_T::APBCLK0: I2C0CKEN Position      */
#define CLK_APBCLK0_I2C0CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C0CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C0CKEN Mask          */

#define CLK_APBCLK0_SPI0CKEN_Pos         (12)                                              /*!< CLK_T::APBCLK0: SPI0CKEN Position      */
#define CLK_APBCLK0_SPI0CKEN_Msk         (0x1ul << CLK_APBCLK0_SPI0CKEN_Pos)               /*!< CLK_T::APBCLK0: SPI0CKEN Mask          */

#define CLK_APBCLK0_UART0CKEN_Pos        (16)                                              /*!< CLK_T::APBCLK0: UART0CKEN Position     */
#define CLK_APBCLK0_UART0CKEN_Msk        (0x1ul << CLK_APBCLK0_UART0CKEN_Pos)              /*!< CLK_T::APBCLK0: UART0CKEN Mask         */

#define CLK_APBCLK0_UART1CKEN_Pos        (17)                                              /*!< CLK_T::APBCLK0: UART1CKEN Position     */
#define CLK_APBCLK0_UART1CKEN_Msk        (0x1ul << CLK_APBCLK0_UART1CKEN_Pos)              /*!< CLK_T::APBCLK0: UART1CKEN Mask         */

#define CLK_APBCLK0_ADCCKEN_Pos          (28)                                              /*!< CLK_T::APBCLK0: ADCCKEN Position       */
#define CLK_APBCLK0_ADCCKEN_Msk          (0x1ul << CLK_APBCLK0_ADCCKEN_Pos)                /*!< CLK_T::APBCLK0: ADCCKEN Mask           */
#define CLK_APBCLK0_ADC0CKEN_Pos         (28)                                              /*!< CLK_T::APBCLK0: ADC0CKEN Position       */
#define CLK_APBCLK0_ADC0CKEN_Msk         (0x1ul << CLK_APBCLK0_ADC0CKEN_Pos)               /*!< CLK_T::APBCLK0: ADC0CKEN Mask           */

#define CLK_APBCLK0_ACMP01CKEN_Pos       (30)                                              /*!< CLK_T::APBCLK0: ACMP01CKEN Position    */
#define CLK_APBCLK0_ACMP01CKEN_Msk       (0x1ul << CLK_APBCLK0_ACMP01CKEN_Pos)             /*!< CLK_T::APBCLK0: ACMP01CKEN Mask        */

#define CLK_APBCLK1_PWM0CKEN_Pos         (0)                                               /*!< CLK_T::APBCLK1: PWM0CKEN Position      */
#define CLK_APBCLK1_PWM0CKEN_Msk         (0x1ul << CLK_APBCLK1_PWM0CKEN_Pos)               /*!< CLK_T::APBCLK1: PWM0CKEN Mask          */

#define CLK_APBCLK1_BPWM0CKEN_Pos        (4)                                               /*!< CLK_T::APBCLK1: BPWM0CKEN Position     */
#define CLK_APBCLK1_BPWM0CKEN_Msk        (0x1ul << CLK_APBCLK1_BPWM0CKEN_Pos)              /*!< CLK_T::APBCLK1: BPWM0CKEN Mask         */

#define CLK_APBCLK1_USCI0CKEN_Pos        (8)                                               /*!< CLK_T::APBCLK1: USCI0CKEN Position     */
#define CLK_APBCLK1_USCI0CKEN_Msk        (0x1ul << CLK_APBCLK1_USCI0CKEN_Pos)              /*!< CLK_T::APBCLK1: USCI0CKEN Mask         */

#define CLK_APBCLK1_USCI1CKEN_Pos        (9)                                               /*!< CLK_T::APBCLK1: USCI1CKEN Position     */
#define CLK_APBCLK1_USCI1CKEN_Msk        (0x1ul << CLK_APBCLK1_USCI1CKEN_Pos)              /*!< CLK_T::APBCLK1: USCI1CKEN Mask         */

#define CLK_APBCLK1_LLSI0CKEN_Pos        (16)                                              /*!< CLK_T::APBCLK1: LLSI0CKEN Position     */
#define CLK_APBCLK1_LLSI0CKEN_Msk        (0x1ul << CLK_APBCLK1_LLSI0CKEN_Pos)              /*!< CLK_T::APBCLK1: LLSI0CKEN Mask         */

#define CLK_APBCLK1_LLSI1CKEN_Pos        (17)                                              /*!< CLK_T::APBCLK1: LLSI1CKEN Position     */
#define CLK_APBCLK1_LLSI1CKEN_Msk        (0x1ul << CLK_APBCLK1_LLSI1CKEN_Pos)              /*!< CLK_T::APBCLK1: LLSI1CKEN Mask         */

#define CLK_CLKSEL0_HCLKSEL_Pos          (0)                                               /*!< CLK_T::CLKSEL0: HCLKSEL Position       */
#define CLK_CLKSEL0_HCLKSEL_Msk          (0x7ul << CLK_CLKSEL0_HCLKSEL_Pos)                /*!< CLK_T::CLKSEL0: HCLKSEL Mask           */

#define CLK_CLKSEL0_STCLKSEL_Pos         (3)                                               /*!< CLK_T::CLKSEL0: STCLKSEL Position      */
#define CLK_CLKSEL0_STCLKSEL_Msk         (0x7ul << CLK_CLKSEL0_STCLKSEL_Pos)               /*!< CLK_T::CLKSEL0: STCLKSEL Mask          */

#define CLK_CLKSEL0_CANFD0SEL_Pos        (24)                                              /*!< CLK_T::CLKSEL0: CANFD0SEL Position     */
#define CLK_CLKSEL0_CANFD0SEL_Msk        (0x3ul << CLK_CLKSEL0_CANFD0SEL_Pos)              /*!< CLK_T::CLKSEL0: CANFD0SEL Mask         */

#define CLK_CLKSEL0_CANFD1SEL_Pos        (26)                                              /*!< CLK_T::CLKSEL0: CANFD1SEL Position     */
#define CLK_CLKSEL0_CANFD1SEL_Msk        (0x3ul << CLK_CLKSEL0_CANFD1SEL_Pos)              /*!< CLK_T::CLKSEL0: CANFD1SEL Mask         */

#define CLK_CLKSEL0_CANFD2SEL_Pos        (28)                                              /*!< CLK_T::CLKSEL0: CANFD2SEL Position     */
#define CLK_CLKSEL0_CANFD2SEL_Msk        (0x3ul << CLK_CLKSEL0_CANFD2SEL_Pos)              /*!< CLK_T::CLKSEL0: CANFD2SEL Mask         */

#define CLK_CLKSEL1_WDTSEL_Pos           (0)                                               /*!< CLK_T::CLKSEL1: WDTSEL Position        */
#define CLK_CLKSEL1_WDTSEL_Msk           (0x3ul << CLK_CLKSEL1_WDTSEL_Pos)                 /*!< CLK_T::CLKSEL1: WDTSEL Mask            */

#define CLK_CLKSEL1_WWDTSEL_Pos          (2)                                               /*!< CLK_T::CLKSEL1: WWDTSEL Position       */
#define CLK_CLKSEL1_WWDTSEL_Msk          (0x3ul << CLK_CLKSEL1_WWDTSEL_Pos)                /*!< CLK_T::CLKSEL1: WWDTSEL Mask           */

#define CLK_CLKSEL1_CLKOSEL_Pos          (4)                                               /*!< CLK_T::CLKSEL1: CLKOSEL Position       */
#define CLK_CLKSEL1_CLKOSEL_Msk          (0x7ul << CLK_CLKSEL1_CLKOSEL_Pos)                /*!< CLK_T::CLKSEL1: CLKOSEL Mask           */

#define CLK_CLKSEL1_TMR0SEL_Pos          (8)                                               /*!< CLK_T::CLKSEL1: TMR0SEL Position       */
#define CLK_CLKSEL1_TMR0SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR0SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR0SEL Mask           */

#define CLK_CLKSEL1_TMR1SEL_Pos          (12)                                              /*!< CLK_T::CLKSEL1: TMR1SEL Position       */
#define CLK_CLKSEL1_TMR1SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR1SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR1SEL Mask           */

#define CLK_CLKSEL1_TMR2SEL_Pos          (16)                                              /*!< CLK_T::CLKSEL1: TMR2SEL Position       */
#define CLK_CLKSEL1_TMR2SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR2SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR2SEL Mask           */

#define CLK_CLKSEL1_TMR3SEL_Pos          (20)                                              /*!< CLK_T::CLKSEL1: TMR3SEL Position       */
#define CLK_CLKSEL1_TMR3SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR3SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR3SEL Mask           */

#define CLK_CLKSEL2_UART0SEL_Pos         (0)                                               /*!< CLK_T::CLKSEL2: UART0SEL Position      */
#define CLK_CLKSEL2_UART0SEL_Msk         (0x3ul << CLK_CLKSEL2_UART0SEL_Pos)               /*!< CLK_T::CLKSEL2: UART0SEL Mask          */

#define CLK_CLKSEL2_UART1SEL_Pos         (2)                                               /*!< CLK_T::CLKSEL2: UART1SEL Position      */
#define CLK_CLKSEL2_UART1SEL_Msk         (0x3ul << CLK_CLKSEL2_UART1SEL_Pos)               /*!< CLK_T::CLKSEL2: UART1SEL Mask          */

#define CLK_CLKSEL2_SPI0SEL_Pos          (24)                                              /*!< CLK_T::CLKSEL2: SPI0SEL Position       */
#define CLK_CLKSEL2_SPI0SEL_Msk          (0x3ul << CLK_CLKSEL2_SPI0SEL_Pos)                /*!< CLK_T::CLKSEL2: SPI0SEL Mask           */

#define CLK_CLKSEL3_ADCSEL_Pos           (0)                                               /*!< CLK_T::CLKSEL3: ADCSEL Position        */
#define CLK_CLKSEL3_ADCSEL_Msk           (0x3ul << CLK_CLKSEL3_ADCSEL_Pos)                 /*!< CLK_T::CLKSEL3: ADCSEL Mask            */
#define CLK_CLKSEL3_ADC0SEL_Pos          (0)                                               /*!< CLK_T::CLKSEL3: ADC0SEL Position       */
#define CLK_CLKSEL3_ADC0SEL_Msk          (0x3ul << CLK_CLKSEL3_ADC0SEL_Pos)                /*!< CLK_T::CLKSEL3: ADC0SEL Mask           */

#define CLK_CLKSEL3_PWM0SEL_Pos          (4)                                               /*!< CLK_T::CLKSEL3: PWM0SEL Position       */
#define CLK_CLKSEL3_PWM0SEL_Msk          (0x1ul << CLK_CLKSEL3_PWM0SEL_Pos)                /*!< CLK_T::CLKSEL3: PWM0SEL Mask           */

#define CLK_CLKSEL3_BPWM0SEL_Pos         (6)                                               /*!< CLK_T::CLKSEL3: BPWM0SEL Position      */
#define CLK_CLKSEL3_BPWM0SEL_Msk         (0x1ul << CLK_CLKSEL3_BPWM0SEL_Pos)               /*!< CLK_T::CLKSEL3: BPWM0SEL Mask          */

#define CLK_CLKDIV0_HCLKDIV_Pos          (0)                                               /*!< CLK_T::CLKDIV0: HCLKDIV Position       */
#define CLK_CLKDIV0_HCLKDIV_Msk          (0xful << CLK_CLKDIV0_HCLKDIV_Pos)                /*!< CLK_T::CLKDIV0: HCLKDIV Mask           */

#define CLK_CLKDIV0_UART0DIV_Pos         (8)                                               /*!< CLK_T::CLKDIV0: UART0DIV Position      */
#define CLK_CLKDIV0_UART0DIV_Msk         (0xful << CLK_CLKDIV0_UART0DIV_Pos)               /*!< CLK_T::CLKDIV0: UART0DIV Mask          */

#define CLK_CLKDIV0_UART1DIV_Pos         (12)                                              /*!< CLK_T::CLKDIV0: UART1DIV Position      */
#define CLK_CLKDIV0_UART1DIV_Msk         (0xful << CLK_CLKDIV0_UART1DIV_Pos)               /*!< CLK_T::CLKDIV0: UART1DIV Mask          */

#define CLK_CLKDIV0_ADCDIV_Pos           (16)                                              /*!< CLK_T::CLKDIV0: ADCDIV Position        */
#define CLK_CLKDIV0_ADCDIV_Msk           (0xfful << CLK_CLKDIV0_ADCDIV_Pos)                /*!< CLK_T::CLKDIV0: ADCDIV Mask            */
#define CLK_CLKDIV0_ADC0DIV_Pos          (16)                                              /*!< CLK_T::CLKDIV0: ADC0DIV Position       */
#define CLK_CLKDIV0_ADC0DIV_Msk          (0xfful << CLK_CLKDIV0_ADC0DIV_Pos)               /*!< CLK_T::CLKDIV0: ADC0DIV Mask           */

#define CLK_CLKDIV1_CANFD0DIV_Pos        (0)                                               /*!< CLK_T::CLKDIV1: CANFD0DIV Position     */
#define CLK_CLKDIV1_CANFD0DIV_Msk        (0xful << CLK_CLKDIV1_CANFD0DIV_Pos)              /*!< CLK_T::CLKDIV1: CANFD0DIV Mask         */

#define CLK_CLKDIV1_CANFD1DIV_Pos        (4)                                               /*!< CLK_T::CLKDIV1: CANFD1DIV Position     */
#define CLK_CLKDIV1_CANFD1DIV_Msk        (0xful << CLK_CLKDIV1_CANFD1DIV_Pos)              /*!< CLK_T::CLKDIV1: CANFD1DIV Mask         */

#define CLK_CLKDIV1_CANFD2DIV_Pos        (8)                                               /*!< CLK_T::CLKDIV1: CANFD2DIV Position     */
#define CLK_CLKDIV1_CANFD2DIV_Msk        (0xful << CLK_CLKDIV1_CANFD2DIV_Pos)              /*!< CLK_T::CLKDIV1: CANFD2DIV Mask         */

#define CLK_PCLKDIV_APB0DIV_Pos          (0)                                               /*!< CLK_T::PCLKDIV: APB0DIV Position       */
#define CLK_PCLKDIV_APB0DIV_Msk          (0x7ul << CLK_PCLKDIV_APB0DIV_Pos)                /*!< CLK_T::PCLKDIV: APB0DIV Mask           */

#define CLK_PCLKDIV_APB1DIV_Pos          (4)                                               /*!< CLK_T::PCLKDIV: APB1DIV Position       */
#define CLK_PCLKDIV_APB1DIV_Msk          (0x7ul << CLK_PCLKDIV_APB1DIV_Pos)                /*!< CLK_T::PCLKDIV: APB1DIV Mask           */

#define CLK_PLLCTL_FBDIV_Pos             (0)                                               /*!< CLK_T::PLLCTL: FBDIV Position          */
#define CLK_PLLCTL_FBDIV_Msk             (0x1fful << CLK_PLLCTL_FBDIV_Pos)                 /*!< CLK_T::PLLCTL: FBDIV Mask              */

#define CLK_PLLCTL_INDIV_Pos             (9)                                               /*!< CLK_T::PLLCTL: INDIV Position          */
#define CLK_PLLCTL_INDIV_Msk             (0x1ful << CLK_PLLCTL_INDIV_Pos)                  /*!< CLK_T::PLLCTL: INDIV Mask              */

#define CLK_PLLCTL_OUTDIV_Pos            (14)                                              /*!< CLK_T::PLLCTL: OUTDIV Position         */
#define CLK_PLLCTL_OUTDIV_Msk            (0x3ul << CLK_PLLCTL_OUTDIV_Pos)                  /*!< CLK_T::PLLCTL: OUTDIV Mask             */

#define CLK_PLLCTL_PD_Pos                (16)                                              /*!< CLK_T::PLLCTL: PD Position             */
#define CLK_PLLCTL_PD_Msk                (0x1ul << CLK_PLLCTL_PD_Pos)                      /*!< CLK_T::PLLCTL: PD Mask                 */

#define CLK_PLLCTL_BP_Pos                (17)                                              /*!< CLK_T::PLLCTL: BP Position             */
#define CLK_PLLCTL_BP_Msk                (0x1ul << CLK_PLLCTL_BP_Pos)                      /*!< CLK_T::PLLCTL: BP Mask                 */

#define CLK_PLLCTL_OE_Pos                (18)                                              /*!< CLK_T::PLLCTL: OE Position             */
#define CLK_PLLCTL_OE_Msk                (0x1ul << CLK_PLLCTL_OE_Pos)                      /*!< CLK_T::PLLCTL: OE Mask                 */

#define CLK_PLLCTL_PLLSRC_Pos            (19)                                              /*!< CLK_T::PLLCTL: PLLSRC Position         */
#define CLK_PLLCTL_PLLSRC_Msk            (0x1ul << CLK_PLLCTL_PLLSRC_Pos)                  /*!< CLK_T::PLLCTL: PLLSRC Mask             */

#define CLK_PLLCTL_STBSEL_Pos            (23)                                              /*!< CLK_T::PLLCTL: STBSEL Position         */
#define CLK_PLLCTL_STBSEL_Msk            (0x1ul << CLK_PLLCTL_STBSEL_Pos)                  /*!< CLK_T::PLLCTL: STBSEL Mask             */

#define CLK_STATUS_HXTSTB_Pos            (0)                                               /*!< CLK_T::STATUS: HXTSTB Position         */
#define CLK_STATUS_HXTSTB_Msk            (0x1ul << CLK_STATUS_HXTSTB_Pos)                  /*!< CLK_T::STATUS: HXTSTB Mask             */

#define CLK_STATUS_LXTSTB_Pos            (1)                                               /*!< CLK_T::STATUS: LXTSTB Position         */
#define CLK_STATUS_LXTSTB_Msk            (0x1ul << CLK_STATUS_LXTSTB_Pos)                  /*!< CLK_T::STATUS: LXTSTB Mask             */

#define CLK_STATUS_PLLSTB_Pos            (2)                                               /*!< CLK_T::STATUS: PLLSTB Position         */
#define CLK_STATUS_PLLSTB_Msk            (0x1ul << CLK_STATUS_PLLSTB_Pos)                  /*!< CLK_T::STATUS: PLLSTB Mask             */

#define CLK_STATUS_LIRCSTB_Pos           (3)                                               /*!< CLK_T::STATUS: LIRCSTB Position        */
#define CLK_STATUS_LIRCSTB_Msk           (0x1ul << CLK_STATUS_LIRCSTB_Pos)                 /*!< CLK_T::STATUS: LIRCSTB Mask            */

#define CLK_STATUS_HIRCSTB_Pos           (4)                                               /*!< CLK_T::STATUS: HIRCSTB Position        */
#define CLK_STATUS_HIRCSTB_Msk           (0x1ul << CLK_STATUS_HIRCSTB_Pos)                 /*!< CLK_T::STATUS: HIRCSTB Mask            */

#define CLK_STATUS_CLKSFAIL_Pos          (7)                                               /*!< CLK_T::STATUS: CLKSFAIL Position       */
#define CLK_STATUS_CLKSFAIL_Msk          (0x1ul << CLK_STATUS_CLKSFAIL_Pos)                /*!< CLK_T::STATUS: CLKSFAIL Mask           */

#define CLK_CLKOCTL_FREQSEL_Pos          (0)                                               /*!< CLK_T::CLKOCTL: FREQSEL Position       */
#define CLK_CLKOCTL_FREQSEL_Msk          (0xful << CLK_CLKOCTL_FREQSEL_Pos)                /*!< CLK_T::CLKOCTL: FREQSEL Mask           */

#define CLK_CLKOCTL_CLKOEN_Pos           (4)                                               /*!< CLK_T::CLKOCTL: CLKOEN Position        */
#define CLK_CLKOCTL_CLKOEN_Msk           (0x1ul << CLK_CLKOCTL_CLKOEN_Pos)                 /*!< CLK_T::CLKOCTL: CLKOEN Mask            */

#define CLK_CLKOCTL_DIV1EN_Pos           (5)                                               /*!< CLK_T::CLKOCTL: DIV1EN Position        */
#define CLK_CLKOCTL_DIV1EN_Msk           (0x1ul << CLK_CLKOCTL_DIV1EN_Pos)                 /*!< CLK_T::CLKOCTL: DIV1EN Mask            */

#define CLK_CLKDCTL_HXTFDEN_Pos          (4)                                               /*!< CLK_T::CLKDCTL: HXTFDEN Position       */
#define CLK_CLKDCTL_HXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFDEN Mask           */

#define CLK_CLKDCTL_HXTFIEN_Pos          (5)                                               /*!< CLK_T::CLKDCTL: HXTFIEN Position       */
#define CLK_CLKDCTL_HXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFIEN Mask           */

#define CLK_CLKDCTL_LXTFDEN_Pos          (12)                                              /*!< CLK_T::CLKDCTL: LXTFDEN Position       */
#define CLK_CLKDCTL_LXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFDEN Mask           */

#define CLK_CLKDCTL_LXTFIEN_Pos          (13)                                              /*!< CLK_T::CLKDCTL: LXTFIEN Position       */
#define CLK_CLKDCTL_LXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFIEN Mask           */

#define CLK_CLKDCTL_HXTFQDEN_Pos         (16)                                              /*!< CLK_T::CLKDCTL: HXTFQDEN Position      */
#define CLK_CLKDCTL_HXTFQDEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQDEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQDEN Mask          */

#define CLK_CLKDCTL_HXTFQIEN_Pos         (17)                                              /*!< CLK_T::CLKDCTL: HXTFQIEN Position      */
#define CLK_CLKDCTL_HXTFQIEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQIEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQIEN Mask          */

#define CLK_CLKDSTS_HXTFIF_Pos           (0)                                               /*!< CLK_T::CLKDSTS: HXTFIF Position        */
#define CLK_CLKDSTS_HXTFIF_Msk           (0x1ul << CLK_CLKDSTS_HXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: HXTFIF Mask            */

#define CLK_CLKDSTS_LXTFIF_Pos           (1)                                               /*!< CLK_T::CLKDSTS: LXTFIF Position        */
#define CLK_CLKDSTS_LXTFIF_Msk           (0x1ul << CLK_CLKDSTS_LXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: LXTFIF Mask            */

#define CLK_CLKDSTS_HXTFQIF_Pos          (8)                                               /*!< CLK_T::CLKDSTS: HXTFQIF Position       */
#define CLK_CLKDSTS_HXTFQIF_Msk          (0x1ul << CLK_CLKDSTS_HXTFQIF_Pos)                /*!< CLK_T::CLKDSTS: HXTFQIF Mask           */

#define CLK_CDUPB_UPERBD_Pos             (0)                                               /*!< CLK_T::CDUPB: UPERBD Position          */
#define CLK_CDUPB_UPERBD_Msk             (0x7fful << CLK_CDUPB_UPERBD_Pos)                 /*!< CLK_T::CDUPB: UPERBD Mask              */

#define CLK_CDLOWB_LOWERBD_Pos           (0)                                               /*!< CLK_T::CDLOWB: LOWERBD Position        */
#define CLK_CDLOWB_LOWERBD_Msk           (0x7fful << CLK_CDLOWB_LOWERBD_Pos)               /*!< CLK_T::CDLOWB: LOWERBD Mask            */

#define CLK_STOPREQ_CANFD0REQ_Pos        (0)                                               /*!< CLK_T::STOPREQ: CANFD0REQ Position     */
#define CLK_STOPREQ_CANFD0REQ_Msk        (0x1ul << CLK_STOPREQ_CANFD0REQ_Pos)              /*!< CLK_T::STOPREQ: CANFD0REQ Mask         */

#define CLK_STOPREQ_CANFD1REQ_Pos        (1)                                               /*!< CLK_T::STOPREQ: CANFD1REQ Position     */
#define CLK_STOPREQ_CANFD1REQ_Msk        (0x1ul << CLK_STOPREQ_CANFD1REQ_Pos)              /*!< CLK_T::STOPREQ: CANFD1REQ Mask         */

#define CLK_STOPREQ_CANFD2REQ_Pos        (2)                                               /*!< CLK_T::STOPREQ: CANFD2REQ Position     */
#define CLK_STOPREQ_CANFD2REQ_Msk        (0x1ul << CLK_STOPREQ_CANFD2REQ_Pos)              /*!< CLK_T::STOPREQ: CANFD2REQ Mask         */

#define CLK_STOPACK_CANFD0ACK_Pos        (0)                                               /*!< CLK_T::STOPACK: CANFD0ACK Position     */
#define CLK_STOPACK_CANFD0ACK_Msk        (0x1ul << CLK_STOPACK_CANFD0ACK_Pos)              /*!< CLK_T::STOPACK: CANFD0ACK Mask         */

#define CLK_STOPACK_CANFD1ACK_Pos        (1)                                               /*!< CLK_T::STOPACK: CANFD1ACK Position     */
#define CLK_STOPACK_CANFD1ACK_Msk        (0x1ul << CLK_STOPACK_CANFD1ACK_Pos)              /*!< CLK_T::STOPACK: CANFD1ACK Mask         */

#define CLK_STOPACK_CANFD2ACK_Pos        (2)                                               /*!< CLK_T::STOPACK: CANFD2ACK Position     */
#define CLK_STOPACK_CANFD2ACK_Msk        (0x1ul << CLK_STOPACK_CANFD2ACK_Pos)              /*!< CLK_T::STOPACK: CANFD2ACK Mask         */


/**@}*/ /* CLK_CONST */
/**@}*/ /* end of CLK register group */

/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __CLK_REG_H__ */
