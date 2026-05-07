/**************************************************************************//**
 * @file     clk.c
 * @version  V3.00
 * @brief    M2A23 series Clock Controller (CLK) driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include "NuMicro.h"
/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup CLK_Driver CLK Driver
  @{
*/


/** @addtogroup CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/

/**
  * @brief      Disable clock divider output function
  * @param      None
  * @return     None
  * @details    This function disable clock divider output function.
  */
void CLK_DisableCKO(void)
{
    /* Disable CKO clock source */
    CLK->APBCLK0 &= (~CLK_APBCLK0_CLKOCKEN_Msk);
}

/**
  * @brief      This function enable clock divider output module clock,
  *             enable clock divider output function and set frequency selection.
  * @param[in]  u32ClkSrc is frequency divider function clock source. Including :
  *             - \ref CLK_CLKSEL1_CLKOSEL_HXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_LXT
  *             - \ref CLK_CLKSEL1_CLKOSEL_HCLK
  *             - \ref CLK_CLKSEL1_CLKOSEL_LIRC
  *             - \ref CLK_CLKSEL1_CLKOSEL_PLL_DIV2
  *             - \ref CLK_CLKSEL1_CLKOSEL_HIRC
  * @param[in]  u32ClkDiv is divider output frequency selection. It could be 0~15.
  * @param[in]  u32ClkDivBy1En is clock divided by one enabled.
  * @return     None
  *
  * @details    Output selected clock to CKO. The output clock frequency is divided by u32ClkDiv. \n
  *             The formula is: \n
  *                 CKO frequency = (Clock source frequency) / 2^(u32ClkDiv + 1) \n
  *             This function is just used to set CKO clock.
  *             User must enable I/O for CKO clock output pin by themselves. \n
  */
void CLK_EnableCKO(uint32_t u32ClkSrc, uint32_t u32ClkDiv, uint32_t u32ClkDivBy1En)
{
    /* CKO = clock source / 2^(u32ClkDiv + 1) */
    CLK->CLKOCTL = CLK_CLKOCTL_CLKOEN_Msk | u32ClkDiv | (u32ClkDivBy1En << CLK_CLKOCTL_DIV1EN_Pos);

    /* Enable CKO clock source */
    CLK->APBCLK0 |= CLK_APBCLK0_CLKOCKEN_Msk;

    /* Select CKO clock source */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_CLKOSEL_Msk)) | (u32ClkSrc);

}

/**
  * @brief      Enter to Power-down mode
  * @param      None
  * @return     None
  * @details    This function is used to let system enter to Power-down mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_PowerDown(void)
{
    /* Set the processor uses deep sleep as its low power mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Set system Power-down enabled */
    CLK->PWRCTL |= CLK_PWRCTL_PDEN_Msk;

    /* Chip enter Power-down mode after CPU run WFI instruction */
    __WFI();
}

/**
  * @brief      Enter to Idle mode
  * @param      None
  * @return     None
  * @details    This function let system enter to Idle mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_Idle(void)
{
    /* Set the processor uses sleep as its low power mode */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    /* Set chip in idle mode because of WFI command */
    CLK->PWRCTL &= ~CLK_PWRCTL_PDEN_Msk;

    /* Chip enter idle mode after CPU run WFI instruction */
    __WFI();
}

/**
  * @brief      Get external high speed crystal clock frequency
  * @param      None
  * @return     External high frequency crystal frequency
  * @details    This function get external high frequency crystal frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetHXTFreq(void)
{
    if(CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk)
        return __HXT;
    else
        return 0;
}

/**
  * @brief      Get external low speed crystal clock frequency
  * @param      None
  * @return     External low speed crystal clock frequency
  * @details    This function get external low frequency crystal frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetLXTFreq(void)
{
    if(CLK->PWRCTL & CLK_PWRCTL_LXTEN_Msk)
        return __LXT;
    else
        return 0;
}

/**
  * @brief      Get HCLK frequency
  * @param      None
  * @return     HCLK frequency
  * @details    This function get HCLK frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetHCLKFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}

/**
  * @brief      Get PCLK0 frequency
  * @param      None
  * @return     PCLK0 frequency
  * @details    This function get PCLK0 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPCLK0Freq(void)
{
    uint32_t u32Freq;
    SystemCoreClockUpdate();

    if((CLK->PCLKDIV & CLK_PCLKDIV_APB0DIV_Msk) == CLK_PCLKDIV_APB0DIV_DIV2)
    {
        u32Freq = SystemCoreClock>>1;
    }
    else
    {
        u32Freq = SystemCoreClock;
    }

    return u32Freq;
}

/**
  * @brief      Get PCLK1 frequency
  * @param      None
  * @return     PCLK1 frequency
  * @details    This function get PCLK1 frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetPCLK1Freq(void)
{
    uint32_t u32Freq;
    SystemCoreClockUpdate();

    if((CLK->PCLKDIV & CLK_PCLKDIV_APB1DIV_Msk) == CLK_PCLKDIV_APB1DIV_DIV2)
    {
        u32Freq = SystemCoreClock>>1;
    }
    else
    {
        u32Freq = SystemCoreClock;
    }

    return u32Freq;
}

/**
  * @brief      Get CPU frequency
  * @param      None
  * @return     CPU frequency
  * @details    This function get CPU frequency. The frequency unit is Hz.
  */
uint32_t CLK_GetCPUFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}

/**
  * @brief      Set HCLK frequency
  * @param[in]  u32Hclk is HCLK frequency. The range of u32Hclk is 25 MHz ~ 72 MHz.
  * @return     HCLK frequency
  * @details    This function is used to set HCLK frequency. The frequency unit is Hz. \n
  *             It would configure PLL frequency to 50MHz ~ 144MHz,
  *             set HCLK clock divider as 1 and switch HCLK clock source to PLL/2. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    uint32_t u32HIRCSTB;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* The range of u32Hclk is 25 MHz ~ 72 MHz */
    if(u32Hclk > FREQ_72MHZ)
        u32Hclk = FREQ_72MHZ;
    if(u32Hclk < FREQ_25MHZ)
        u32Hclk = FREQ_25MHZ;

    /* Switch HCLK clock source to HIRC clock for safe */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_Msk;
    CLK->CLKDIV0 &= (~CLK_CLKDIV0_HCLKDIV_Msk);

    /* Configure PLL setting if HXT clock is stable */
    if(CLK->STATUS & CLK_STATUS_HXTSTB_Msk)
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HXT, (u32Hclk << 1));

    /* Configure PLL setting if HXT clock is not stable */
    else
    {
        u32Hclk = CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HIRC_DIV2, (u32Hclk << 1));

        /* Read HIRC clock source stable flag */
        u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;
    }

    /* Select HCLK clock source to PLL/2,
       Select HCLK clock source divider as 1
       and update system core clock
    */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_PLL_DIV2, CLK_CLKDIV0_HCLK(1));

    /* Disable HIRC if HIRC is disabled before setting core clock */
    if(u32HIRCSTB == 0)
        CLK->PWRCTL &= ~CLK_PWRCTL_HIRCEN_Msk;

    /* Return actually HCLK frequency is PLL frequency divide 2 */
    return u32Hclk >> 1;
}

/**
  * @brief      Set HCLK clock source and HCLK clock divider
  * @param[in]  u32ClkSrc is HCLK clock source. Including :
  *             - \ref CLK_CLKSEL0_HCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_HCLKSEL_PLL_DIV2
  *             - \ref CLK_CLKSEL0_HCLKSEL_LIRC
  *             - \ref CLK_CLKSEL0_HCLKSEL_HIRC
  * @param[in]  u32ClkDiv is HCLK clock divider. Including :
  *             - \ref CLK_CLKDIV0_HCLK(x)
  * @return     None
  * @details    This function set HCLK clock source and HCLK clock divider.
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32HIRCSTB;

    /* Read HIRC clock source stable flag */
    u32HIRCSTB = CLK->STATUS & CLK_STATUS_HIRCSTB_Msk;

    /* Switch to HIRC for Safe. Avoid HCLK too high when applying new divider. */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_HIRC;

    /* Set Frequency Optimization Mode to 0 for safe */
    FMC->FTCTL = FMC->FTCTL & (~FMC_FTCTL_FOM_Msk);

    /* Apply new Divider */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & (~CLK_CLKDIV0_HCLKDIV_Msk)) | u32ClkDiv;

    /* Switch HCLK to new HCLK source */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | u32ClkSrc;

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Switch Frequency Optimization Mode to suitable value base on HCLK */
    if (SystemCoreClock <= FREQ_29MHZ)
    {
        FMC->FTCTL = (FMC->FTCTL & (~FMC_FTCTL_FOM_Msk)) | (2<<FMC_FTCTL_FOM_Pos);
    }
    else if (SystemCoreClock <= FREQ_43MHZ)
    {
        FMC->FTCTL = (FMC->FTCTL & (~FMC_FTCTL_FOM_Msk)) | (3<<FMC_FTCTL_FOM_Pos);
    }
    else if (SystemCoreClock <= FREQ_58MHZ)
    {
        FMC->FTCTL = (FMC->FTCTL & (~FMC_FTCTL_FOM_Msk)) | (4<<FMC_FTCTL_FOM_Pos);
    }
    else /* SystemCoreClock <= FREQ_72MHZ */
    {
        FMC->FTCTL = (FMC->FTCTL & (~FMC_FTCTL_FOM_Msk)) | (5<<FMC_FTCTL_FOM_Pos);
    }

    /* Disable HIRC if HIRC is disabled before switching HCLK source */
    if(u32HIRCSTB == 0)
        CLK->PWRCTL &= ~CLK_PWRCTL_HIRCEN_Msk;
}
/**
  * @brief      This function set selected module clock source and module clock divider
  * @param[in]  u32ModuleIdx is module index.
  * @param[in]  u32ClkSrc is module clock source.
  * @param[in]  u32ClkDiv is module clock divider.
  * @return     None
  * @details    Valid parameter combinations listed in following table:
  *
  * |Module index        |Clock source                          |Divider                    |
  * | :----------------  | :----------------------------------- | :------------------------ |
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_HXT        |\ref CLK_CLKDIV1_CANFD0(x )|
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_PLL_DIV2   |\ref CLK_CLKDIV1_CANFD0(x) |
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_HCLK       |\ref CLK_CLKDIV1_CANFD0(x) |
  * |\ref CANFD0_MODULE  |\ref CLK_CLKSEL0_CANFD0SEL_HIRC       |\ref CLK_CLKDIV1_CANFD0(x) |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_HXT        |\ref CLK_CLKDIV1_CANFD1(x) |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_PLL_DIV2   |\ref CLK_CLKDIV1_CANFD1(x) |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_HCLK       |\ref CLK_CLKDIV1_CANFD1(x) |
  * |\ref CANFD1_MODULE  |\ref CLK_CLKSEL0_CANFD1SEL_HIRC       |\ref CLK_CLKDIV1_CANFD1(x) |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_HXT        |\ref CLK_CLKDIV1_CANFD2(x) |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_PLL_DIV2   |\ref CLK_CLKDIV1_CANFD2(x) |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_HCLK       |\ref CLK_CLKDIV1_CANFD2(x) |
  * |\ref CANFD2_MODULE  |\ref CLK_CLKSEL0_CANFD2SEL_HIRC       |\ref CLK_CLKDIV1_CANFD2(x) |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LXT           | x                         |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_HCLK_DIV2048  | x                         |
  * |\ref WDT_MODULE     |\ref CLK_CLKSEL1_WDTSEL_LIRC          | x                         |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_HCLK_DIV2048 | x                         |
  * |\ref WWDT_MODULE    |\ref CLK_CLKSEL1_WWDTSEL_LIRC         | x                         |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HXT          | x                         |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LXT          | x                         |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HCLK         | x                         |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_LIRC         | x                         |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_PLL_DIV2     | x                         |
  * |\ref CLKO_MODULE    |\ref CLK_CLKSEL1_CLKOSEL_HIRC         | x                         |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HXT          | x                         |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LXT          | x                         |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_PCLK0        | x                         |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_EXT_TRG      | x                         |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_LIRC         | x                         |
  * |\ref TMR0_MODULE    |\ref CLK_CLKSEL1_TMR0SEL_HIRC         | x                         |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HXT          | x                         |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LXT          | x                         |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_PCLK0        | x                         |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_EXT_TRG      | x                         |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_LIRC         | x                         |
  * |\ref TMR1_MODULE    |\ref CLK_CLKSEL1_TMR1SEL_HIRC         | x                         |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HXT          | x                         |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LXT          | x                         |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_PCLK1        | x                         |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_EXT_TRG      | x                         |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_LIRC         | x                         |
  * |\ref TMR2_MODULE    |\ref CLK_CLKSEL1_TMR2SEL_HIRC         | x                         |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HXT          | x                         |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LXT          | x                         |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_PCLK1        | x                         |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_EXT_TRG      | x                         |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_LIRC         | x                         |
  * |\ref TMR3_MODULE    |\ref CLK_CLKSEL1_TMR3SEL_HIRC         | x                         |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_HXT         |\ref CLK_CLKDIV0_UART0(x)  |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_PLL         |\ref CLK_CLKDIV0_UART0(x)  |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_LXT         |\ref CLK_CLKDIV0_UART0(x)  |
  * |\ref UART0_MODULE   |\ref CLK_CLKSEL2_UART0SEL_HIRC        |\ref CLK_CLKDIV0_UART0(x)  |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_HXT         |\ref CLK_CLKDIV0_UART1(x)  |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_PLL         |\ref CLK_CLKDIV0_UART1(x)  |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_LXT         |\ref CLK_CLKDIV0_UART1(x)  |
  * |\ref UART1_MODULE   |\ref CLK_CLKSEL2_UART1SEL_HIRC        |\ref CLK_CLKDIV0_UART1(x)  |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HXT          | x                         |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PLL_DIV2     | x                         |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_PCLK1        | x                         |
  * |\ref SPI0_MODULE    |\ref CLK_CLKSEL2_SPI0SEL_HIRC         | x                         |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL3_ADCSEL_PLL           |\ref CLK_CLKDIV0_ADC(x)    |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL3_ADCSEL_HCLK          |\ref CLK_CLKDIV0_ADC(x)    |
  * |\ref ADC_MODULE     |\ref CLK_CLKSEL3_ADCSEL_HIRC          |\ref CLK_CLKDIV0_ADC(x)    |
  * |\ref PWM0_MODULE    |\ref CLK_CLKSEL3_PWM0SEL_PLL          | x                         |
  * |\ref PWM0_MODULE    |\ref CLK_CLKSEL3_PWM0SEL_PCLK0        | x                         |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL3_BPWM0SEL_PLL         | x                         |
  * |\ref BPWM0_MODULE   |\ref CLK_CLKSEL3_BPWM0SEL_PCLK0       | x                         |
  */
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32sel = 0, u32div = 0;
    uint32_t u32SelTbl[4] = {0x0, 0x4, 0x8, 0xC}; /* CLK_CLKSEL0~3 */
    uint32_t u32DivTbl[2] = {0x0, 0x4};           /* CLK_CLKDIV0~1 */

    if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock divider control register address */
        u32div = (uint32_t)&CLK->CLKDIV0 + (u32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
        /* Apply new divider */
        M32(u32div) = (M32(u32div) & (~(MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx)))) | u32ClkDiv;
    }

    if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock select control register address */
        u32sel = (uint32_t)&CLK->CLKSEL0 + (u32SelTbl[MODULE_CLKSEL(u32ModuleIdx)]);
        /* Set new clock selection setting */
        M32(u32sel) = (M32(u32sel) & (~(MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx)))) | u32ClkSrc;
    }
}

/**
  * @brief      Set SysTick clock source
  * @param[in]  u32ClkSrc is module clock source. Including:
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HCLK_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HIRC_DIV2
  * @return     None
  * @details    This function set SysTick clock source. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc)
{
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc;
}

/**
  * @brief      Enable clock source
  * @param[in]  u32ClkMask is clock source mask. Including :
  *             - \ref CLK_PWRCTL_HXTEN_Msk
  *             - \ref CLK_PWRCTL_LXTEN_Msk
  *             - \ref CLK_PWRCTL_HIRCEN_Msk
  *             - \ref CLK_PWRCTL_LIRCEN_Msk
  * @return     None
  * @details    This function enable clock source. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_EnableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCTL |= u32ClkMask;
}

/**
  * @brief      Disable clock source
  * @param[in]  u32ClkMask is clock source mask. Including :
  *             - \ref CLK_PWRCTL_HXTEN_Msk
  *             - \ref CLK_PWRCTL_LXTEN_Msk
  *             - \ref CLK_PWRCTL_HIRCEN_Msk
  *             - \ref CLK_PWRCTL_LIRCEN_Msk
  * @return     None
  * @details    This function disable clock source. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_DisableXtalRC(uint32_t u32ClkMask)
{
    CLK->PWRCTL &= ~u32ClkMask;
}

/**
  * @brief      Enable module clock
  * @param[in]  u32ModuleIdx is module index. Including :
  *             - \ref PDMA_MODULE
  *             - \ref ISP_MODULE
  *             - \ref ST_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref FMCIDLE_MODULE
  *             - \ref CANRAM0_MODULE
  *             - \ref CANRAM1_MODULE
  *             - \ref CANRAM2_MODULE
  *             - \ref GPIOA_MODULE
  *             - \ref GPIOB_MODULE
  *             - \ref GPIOC_MODULE
  *             - \ref GPIOD_MODULE
  *             - \ref GPIOF_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref ADC_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref PWM0_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  *             - \ref LLSI0_MODULE
  *             - \ref LLSI1_MODULE
  * @return     None
  * @details    This function is used to enable module clock.
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32ClkTbl[3] = {0x0, 0x4, 0x8}; /* CLK_AHBCLK, CLK_APBCLK0~1 */

    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK + (u32ClkTbl[MODULE_APBCLK(u32ModuleIdx)]))  |= 1 << MODULE_IP_EN_Pos(u32ModuleIdx);
}

/**
  * @brief      Disable module clock
  * @param[in]  u32ModuleIdx is module index
  *             - \ref PDMA_MODULE
  *             - \ref ISP_MODULE
  *             - \ref ST_MODULE
  *             - \ref CRC_MODULE
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref FMCIDLE_MODULE
  *             - \ref CANRAM0_MODULE
  *             - \ref CANRAM1_MODULE
  *             - \ref CANRAM2_MODULE
  *             - \ref GPIOA_MODULE
  *             - \ref GPIOB_MODULE
  *             - \ref GPIOC_MODULE
  *             - \ref GPIOD_MODULE
  *             - \ref GPIOF_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref I2C0_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref ADC_MODULE
  *             - \ref ACMP01_MODULE
  *             - \ref PWM0_MODULE
  *             - \ref BPWM0_MODULE
  *             - \ref USCI0_MODULE
  *             - \ref USCI1_MODULE
  *             - \ref LLSI0_MODULE
  *             - \ref LLSI1_MODULE
  * @return     None
  * @details    This function is used to disable module clock.
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    uint32_t u32ClkTbl[3] = {0x0, 0x4, 0x8}; /* CLK_AHBCLK, CLK_APBCLK0~1 */

    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK + (u32ClkTbl[MODULE_APBCLK(u32ModuleIdx)]))  &= ~(1 << MODULE_IP_EN_Pos(u32ModuleIdx));
}


/**
  * @brief      Set PLL frequency
  * @param[in]  u32PllClkSrc is PLL clock source. Including :
  *             - \ref CLK_PLLCTL_PLLSRC_HXT
  *             - \ref CLK_PLLCTL_PLLSRC_HIRC_DIV2
  * @param[in]  u32PllFreq is PLL frequency. The range of u32PllFreq is 50 MHz ~ 144 MHz.
  * @return     PLL frequency
  * @details    This function is used to configure PLLCTL register to set specified PLL frequency. \n
  *             The register write-protection function should be disabled before using this function.
  */
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32PllSrcClk, u32NR, u32NF, u32NO, u32CLK_SRC, u32STBSEL, u32PllClk=0UL;
    uint32_t u32Tmp, u32Tmp2, u32Tmp3, u32Min, u32MinNF, u32MinNR;

    /* Check PLL frequency range */
    /* Select "NO" according to request frequency */
    /* Constraint 1: 50MHz < FOUT < 144MHz */
    if((u32PllFreq <= FREQ_144MHZ) && (u32PllFreq > FREQ_100MHZ))
    {
        u32NO = 1;
        u32PllFreq = u32PllFreq << 1;
    }
    else if((u32PllFreq <= FREQ_100MHZ) && (u32PllFreq >= FREQ_50MHZ))
    {
        u32NO = 3;
        u32PllFreq = u32PllFreq << 2;
    }
    else
    {
        /* Wrong frequency request. Just return default setting. */
        goto lexit;
    }

    /* Disable PLL first to avoid unstable when setting PLL */
    CLK->PLLCTL |= CLK_PLLCTL_PD_Msk;

    /* PLL source clock is from HXT */
    if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
    {
        /* Enable HXT clock */
        CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk;

        /* Wait for HXT clock ready */
        CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

        /* Select PLL source clock from HXT */
        u32CLK_SRC = CLK_PLLCTL_PLLSRC_HXT;
        u32PllSrcClk = __HXT;

        /* u32NR start from 2 */
        u32NR = 2;
    }

    /* PLL source clock is from HIRC */
    else
    {
        /* Enable HIRC clock */
        CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;

        /* Wait for HIRC clock ready */
        CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

        /* Select PLL source clock from HIRC/2 */
        u32CLK_SRC = CLK_PLLCTL_PLLSRC_HIRC_DIV2;
        u32PllSrcClk = (__HIRC>>1);

        /* u32NR start from 4 when FIN = 24MHz to avoid calculation overflow */
        u32NR = 4;
    }

    /* Select PLL stable counter */
    if(u32PllSrcClk <= 12000000UL)
    {
        u32STBSEL = CLK_PLLCTL_STBSEL_6144;
    }
    else
    {
        u32STBSEL = CLK_PLLCTL_STBSEL_12288;
    }

    /* Find best solution */
    u32Min = (uint32_t) - 1;    /* initial u32Min to max value of uint32_t (0xFFFFFFFF) */
    u32MinNR = 0;
    u32MinNF = 0;
    for(; u32NR <= 33; u32NR++)  /* max NR = 33 since NR = INDIV+2 and INDIV = 0~31 */
    {
        u32Tmp = u32PllSrcClk / u32NR;                  /* FREF = FIN/NR */
        if((u32Tmp > 1600000) && (u32Tmp < 16000000))   /* Constraint 2: 1.6MHz < FREF < 16MHz. */
        {
            for(u32NF = 2; u32NF <= 513; u32NF++)       /* NF = 2~513 since NF = FBDIV+2 and FBDIV = 0~511 */
            {
                u32Tmp2 = u32Tmp * u32NF;                               /* FVCO = FREF*NF */
                if((u32Tmp2 >= 200000000) && (u32Tmp2 <= 500000000))    /* Constraint 3: 200MHz < FVCO < 500MHz */
                {
                    u32Tmp3 = (u32Tmp2 > u32PllFreq) ? u32Tmp2 - u32PllFreq : u32PllFreq - u32Tmp2;
                    if(u32Tmp3 < u32Min)
                    {
                        u32Min = u32Tmp3;
                        u32MinNR = u32NR;
                        u32MinNF = u32NF;

                        /* Break when get good results */
                        if(u32Min == 0)
                            break;
                    }
                }
            }
        }
    }

    /* Enable and apply new PLL setting. */
    CLK->PLLCTL = u32STBSEL| u32CLK_SRC | (u32NO << 14) | ((u32MinNR - 2) << 9) | (u32MinNF - 2);

    /* Actual PLL output clock frequency. FOUT = (FIN/NR)*NF*(1/NO) */
    u32PllClk = u32PllSrcClk / ((u32NO + 1) * u32MinNR) * u32MinNF;

lexit:

     /* Input PLL frequency is out of range. Apply default PLL setting. */
    if(u32PllClk == 0)
    {
        if(u32PllClkSrc == CLK_PLLCTL_PLLSRC_HXT)
        {
#if ((__HXT == 12000000)||(__HXT == 24000000))
            CLK->PLLCTL = CLK_PLLCTL_144MHz_HXT;        /* 144MHz */
            u32PllClk = FREQ_144MHZ;
#else
            u32PllClk = 0;  /* No default PLL setting */
#endif
        }
        else
        {
            CLK->PLLCTL = CLK_PLLCTL_144MHz_HIRC_DIV2;  /* 144MHz */
            u32PllClk = FREQ_144MHZ;
        }
    }

    if(u32PllClk != 0)
    {
        /* Wait for PLL clock stable */
        CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);
    }

    /* Return actual PLL output clock frequency */
    return u32PllClk;

}

/**
  * @brief      Disable PLL
  * @param      None
  * @return     None
  * @details    This function set PLL in Power-down mode. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_DisablePLL(void)
{
    CLK->PLLCTL |= CLK_PLLCTL_PD_Msk;
}

/**
  * @brief      This function check selected clock source status
  * @param[in]  u32ClkMask is selected clock source. Including :
  *             - \ref CLK_STATUS_HXTSTB_Msk
  *             - \ref CLK_STATUS_LXTSTB_Msk
  *             - \ref CLK_STATUS_HIRCSTB_Msk
  *             - \ref CLK_STATUS_LIRCSTB_Msk
  *             - \ref CLK_STATUS_PLLSTB_Msk
  * @retval     0  clock is not stable
  * @retval     1  clock is stable
  * @details    To wait for clock ready by specified clock source stable flag or timeout (>500ms)
  */
uint32_t CLK_WaitClockReady(uint32_t u32ClkMask)
{
    int32_t i32TimeOutCnt = SystemCoreClock>>1; /* 500ms time-out */

    while((CLK->STATUS & u32ClkMask) != u32ClkMask)
    {
        if(i32TimeOutCnt-- <= 0)
            return 0;
    }

    return 1;
}

/**
  * @brief      Enable System Tick counter
  * @param[in]  u32ClkSrc is System Tick clock source. Including:
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_LXT
  *             - \ref CLK_CLKSEL0_STCLKSEL_HXT_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HCLK_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HIRC_DIV2
  *             - \ref CLK_CLKSEL0_STCLKSEL_HCLK
  * @param[in]  u32Count is System Tick reload value. It could be 0~0xFFFFFF.
  * @return     None
  * @details    This function set System Tick clock source, reload value, enable System Tick counter and interrupt. \n
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_EnableSysTick(uint32_t u32ClkSrc, uint32_t u32Count)
{
    /* Set System Tick counter disabled */
    SysTick->CTRL = 0;

    /* Set System Tick clock source */
    if(u32ClkSrc == CLK_CLKSEL0_STCLKSEL_HCLK)
    {
        /* Select System Tick clock source from core clock */
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    }
    else
    {
        /* Select System Tick external reference clock source */
        CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc;

        /* Select System Tick clock source from external reference clock */
        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
    }

    /* Set System Tick reload value */
    SysTick->LOAD = u32Count;

    /* Clear System Tick current value and counter flag */
    SysTick->VAL = 0;

    /* Set System Tick interrupt enabled and counter enabled */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief      Disable System Tick counter
  * @param      None
  * @return     None
  * @details    This function disable System Tick counter.
  */
void CLK_DisableSysTick(void)
{
    /* Set System Tick counter disabled */
    SysTick->CTRL = 0;
}

/**
  * @brief      Get selected module clock source
  * @param[in]  u32ModuleIdx is module index.
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref WDT_MODULE
  *             - \ref WWDT_MODULE
  *             - \ref CLKO_MODULE
  *             - \ref TMR0_MODULE
  *             - \ref TMR1_MODULE
  *             - \ref TMR2_MODULE
  *             - \ref TMR3_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref SPI0_MODULE
  *             - \ref ADC_MODULE
  *             - \ref PWM0_MODULE
  *             - \ref BPWM0_MODULE
  * @return     Selected module clock source setting
  * @details    This function get selected module clock source.
  */
uint32_t CLK_GetModuleClockSource(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;
    uint32_t au32SelTbl[4] = {0x0, 0x4, 0x8, 0xC}; /* CLK_CLKSEL0~3 */

    if(MODULE_CLKSEL_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock select control register address */
        u32TmpAddr = (uint32_t)&CLK->CLKSEL0 + (au32SelTbl[MODULE_CLKSEL(u32ModuleIdx)]);
        /* Get clock source selection setting */
        u32TmpVal = ((inpw((uint32_t *)u32TmpAddr) & (MODULE_CLKSEL_Msk(u32ModuleIdx) << MODULE_CLKSEL_Pos(u32ModuleIdx))) >> MODULE_CLKSEL_Pos(u32ModuleIdx));
    }

    return u32TmpVal;
}

/**
  * @brief      Get selected module clock divider number
  * @param[in]  u32ModuleIdx is module index.
  *             - \ref CANFD0_MODULE
  *             - \ref CANFD1_MODULE
  *             - \ref CANFD2_MODULE
  *             - \ref UART0_MODULE
  *             - \ref UART1_MODULE
  *             - \ref ADC_MODULE
  * @return     Selected module clock divider number setting
  * @details    This function get selected module clock divider number.
  */
uint32_t CLK_GetModuleClockDivider(uint32_t u32ModuleIdx)
{
    uint32_t u32TmpVal = 0UL, u32TmpAddr = 0UL;
    uint32_t au32DivTbl[2] = {0x0, 0x4}; /* CLK_CLKDIV0~1 */

    if(MODULE_CLKDIV_Msk(u32ModuleIdx) != MODULE_NoMsk)
    {
        /* Get clock divider control register address */
        u32TmpAddr = (uint32_t)&CLK->CLKDIV0 + (au32DivTbl[MODULE_CLKDIV(u32ModuleIdx)]);
        /* Get clock divider number setting */
        u32TmpVal = ((inpw((uint32_t *)u32TmpAddr) & (MODULE_CLKDIV_Msk(u32ModuleIdx) << MODULE_CLKDIV_Pos(u32ModuleIdx))) >> MODULE_CLKDIV_Pos(u32ModuleIdx));
    }

    return u32TmpVal;
}


/*@}*/ /* end of group CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group CLK_Driver */

/*@}*/ /* end of group Standard_Driver */
