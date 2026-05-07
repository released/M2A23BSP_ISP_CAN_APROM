/**************************************************************************//**
 * @file     adc.c
 * @version  V3.00
 * @brief    M2A23 series ADC driver source file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup ADC_Driver ADC Driver
  @{
*/

int32_t g_ADC_i32ErrCode = 0;		/*!< ADC global error code */

/** @addtogroup ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief Execute ADC Calibration
  * @param[in] adc The pointer of the specified ADC module
  * @return ADC clock frequency must less or equal to 24MHz to get correct calibration code.
  */
void ADC_Calibration(ADC_T *adc)
{
    int32_t i32TimeOutCnt = (SystemCoreClock >> 1);
    uint32_t clksrc, clkdiv, clkfreq, clkdiv_adj;
    uint32_t pllfreq, pllsrc_freq, pllctl = CLK->PLLCTL;
        
    clksrc = CLK_GetModuleClockSource(ADC_MODULE);
    clkdiv = CLK_GetModuleClockDivider(ADC_MODULE);
    clkdiv_adj = clkdiv;
    
    /* Notes: ADC clock frequency MUST <= 24MHz for Calibration */
        
    if(clksrc == 1)
    {
        /* PLL: 50MHz ~ 144MHz */
        if(pllctl & CLK_PLLCTL_PLLSRC_Msk)
            pllsrc_freq = (__HIRC >> 1);
        else
            pllsrc_freq = __HXT;
        
        pllfreq = (pllsrc_freq * ((pllctl&0x1FF) + 2)) / (((pllctl>>CLK_PLLCTL_INDIV_Pos)&0x1F) + 2);
        if(((pllctl>>CLK_PLLCTL_OUTDIV_Pos)&0x3) == 0)
            clkfreq = (pllfreq / 1);
        else if(((pllctl>>CLK_PLLCTL_OUTDIV_Pos)&0x3) == 3)
            clkfreq = (pllfreq / 4);
        else
            clkfreq = (pllfreq / 2);

        if(clkfreq > 72000000)
            clkdiv_adj = (6 - 1);
        else
            clkdiv_adj = (3 - 1);
    }
    else if(clksrc == 2)
    {
        /* SystemCoreClock, maximum is 72MHz */
        clkfreq = SystemCoreClock;
        if(clkfreq > 24000000)
        {
            if(clkfreq <= 48000000)
                clkdiv_adj = (2 - 1);
            else
                clkdiv_adj = (3 - 1);
        }
    }
    else
    {
        /* HIRC 48MHz */
        clkfreq = __HIRC;
        clkdiv_adj = (2 - 1);
    }        

    /* Adjust ADC clock divider for calibration */
    if(clkdiv_adj > clkdiv)
        CLK->CLKDIV0 = ((CLK->CLKDIV0 & ~CLK_CLKDIV0_ADC0DIV_Msk) | (clkdiv_adj << CLK_CLKDIV0_ADC0DIV_Pos));
    
    (adc)->CALCTL = ADC_CALCTL_CAL_Msk;
    while(((adc)->CALSR & ADC_CALSR_CALIF_Msk) == 0) 
    {
        if(i32TimeOutCnt-- <= 0)
            break;
    }
    (adc)->CALSR = (adc)->CALSR;
    
    /* Restore user's ADC clock divider */
    if(clkdiv_adj > clkdiv)
        CLK->CLKDIV0 = ((CLK->CLKDIV0 & ~CLK_CLKDIV0_ADC0DIV_Msk) | (clkdiv << CLK_CLKDIV0_ADC0DIV_Pos));   
}

/**
  * @brief This API configures ADC module to be ready for convert the input from selected channel
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32InputMode Decides the ADC analog input mode. Valid values are:
  *                          - \ref ADC_ADCR_DIFFEN_SINGLE_END      :Single end input mode
  *                          - \ref ADC_ADCR_DIFFEN_DIFFERENTIAL    :Differential input type
  * @param[in] u32OpMode Decides the ADC operation mode. Valid values are:
  *                       - \ref ADC_ADCR_ADMD_SINGLE               :Single mode.
  *                       - \ref ADC_ADCR_ADMD_BURST                :Burst mode.
  *                       - \ref ADC_ADCR_ADMD_SINGLE_CYCLE         :Single cycle scan mode.
  *                       - \ref ADC_ADCR_ADMD_CONTINUOUS           :Continuous scan mode.
  * @param[in] u32ChMask Channel enable bit. Each bit corresponds to a input channel. Bit 0 is channel 0, bit 1 is channel 1..., bit 7 is channel 7.
  * @return  None
  * @note M2A23 series MCU ADC can only convert 1 channel at a time. \n
	*				If more than 1 channels are enabled, only channel with smallest number will be converted at single and burst mode, \n
	*	      and others channels will be converted in the sequence from the smallest number channel to the largest number channel at single-cycle scan and continuous scan mode.
  * @note This API does not turn on ADC power nor does trigger ADC conversion
  */
void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask)
{
    
	/* ADC macro settings for chip-A */
    if((inpw(ADC0_BASE+0xFF4)&BIT16) == BIT16)
        outpw(ADC0_BASE+0xFF4, 0x31);

	/* Execute Calibration */
    ADC_Calibration(adc);            
            
    (adc)->ADCR = ((adc)->ADCR & (~(ADC_ADCR_DIFFEN_Msk | ADC_ADCR_ADMD_Msk))) | \
                (u32InputMode) | \
                (u32OpMode);

    (adc)->ADCHER = ((adc)->ADCHER & ~ADC_ADCHER_CHEN_Msk) | (u32ChMask);

    if ((adc)->ADCHER & BIT29)
    {
        // CH-29 for band-gap voltage
    }

    if ((adc)->ADCHER & BIT30)
    {
        // CH-30 for temperature sensor
        SYS->IVSCTL |= SYS_IVSCTL_VTEMPEN_Msk;
    }

    if ((adc)->ADCHER & BIT31)
    {
        // CH-31 for AVDD divide 4 
        SYS->IVSCTL |= SYS_IVSCTL_AVDDDIVEN_Msk;
    }

    return;
}

/**
  * @brief Disable ADC module
  * @param[in] adc The pointer of the specified ADC module
  * @return None
  */
void ADC_Close(ADC_T *adc)
{    
    SYS->IPRST1 |= SYS_IPRST1_ADC0RST_Msk;
    SYS->IPRST1 &= ~SYS_IPRST1_ADC0RST_Msk;
    
    SYS->IVSCTL &= ~(SYS_IVSCTL_VTEMPEN_Msk | SYS_IVSCTL_AVDDDIVEN_Msk);

    return;
}

/**
  * @brief Configure the hardware trigger condition and enable hardware trigger
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32Source Decides the hardware trigger source. Valid values are:
  *                       - \ref ADC_ADCR_TRGS_STADC            :A/D conversion is started by external STADC pin.
  *                       - \ref ADC_ADCR_TRGS_TIMER0           :A/D conversion is started by Timer0 overflow pulse trigger.
  *                       - \ref ADC_ADCR_TRGS_TIMER1           :A/D conversion is started by Timer1 overflow pulse trigger.
  *                       - \ref ADC_ADCR_TRGS_TIMER2           :A/D conversion is started by Timer2 overflow pulse trigger.
  *                       - \ref ADC_ADCR_TRGS_TIMER3           :A/D conversion is started by Timer3 overflow pulse trigger.
  *                       - \ref ADC_ADCR_TRGS_PWM              :A/D conversion is started by PWM trigger.
  *                       - \ref ADC_ADCR_TRGS_BPWM             :A/D conversion is started by BPWM trigger.
  *                       - \ref ADC_ADCR_TRGS_ACMP0          	:A/D conversion is started by ACMP0 trigger.
  *                       - \ref ADC_ADCR_TRGS_ACMP1           	:A/D conversion is started by ACMP1 trigger.
  * @param[in] u32Param While ADC trigger by PWM/BPWM, this parameter is used to set the delay between PWM/BPWM \n
  *                     trigger and ADC conversion. Valid values are from 0 ~ 0xFF, and actual delay time is (4 * u32Param * HCLK). \n
	*											While ADC trigger by external STADC pin, this parameter \n
  *                     is used to set trigger condition. While ADC trigger by Timer, this parameter \n
  *                     is u non-used. Valid values are: \n
  *                      - \ref ADC_ADCR_TRGCOND_LOW_LEVEL     :STADC Low level active \n
  *                      - \ref ADC_ADCR_TRGCOND_HIGH_LEVEL    :STADC High level active \n
  *                      - \ref ADC_ADCR_TRGCOND_FALLING_EDGE  :STADC Falling edge active \n
  *                      - \ref ADC_ADCR_TRGCOND_RISING_EDGE   :STADC Rising edge active \n
  * @return None
  * @note Software should disable ADST(ADC_ADCR[11]) before change TRGS(ADC_ADCR[15:12]).
  */
void ADC_EnableHWTrigger(ADC_T *adc,
                         uint32_t u32Source,
                         uint32_t u32Param)
{
    if(u32Source == ADC_ADCR_TRGS_STADC)
    {
        (adc)->ADCR = ((adc)->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk)) | (u32Source) | (u32Param);
    }
    else if((u32Source == ADC_ADCR_TRGS_TIMER0) || (u32Source == ADC_ADCR_TRGS_TIMER1) || (u32Source == ADC_ADCR_TRGS_TIMER2) || (u32Source == ADC_ADCR_TRGS_TIMER3))
    {
        (adc)->ADCR = ((adc)->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk)) | (u32Source);
    }
    else if((u32Source == ADC_ADCR_TRGS_PWM) || (u32Source == ADC_ADCR_TRGS_BPWM))
    {
        (adc)->ADTDCR = ((adc)->ADTDCR & ~ADC_ADTDCR_PTDT_Msk) | (u32Param);
        (adc)->ADCR = ((adc)->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk)) | (u32Source);
    }
    else if((u32Source == ADC_ADCR_TRGS_ACMP0) || (u32Source == ADC_ADCR_TRGS_ACMP1))
    {
        (adc)->ADCR = ((adc)->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk)) | (u32Source);
    }
	else
	{
        (adc)->ADCR = ((adc)->ADCR & ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk));
	}
		
    return;
}

/**
  * @brief Disable hardware trigger ADC function.
  * @param[in] adc The pointer of the specified ADC module
  * @return None
  */
void ADC_DisableHWTrigger(ADC_T *adc)
{
    (adc)->ADCR &= ~(ADC_ADCR_TRGS_Msk | ADC_ADCR_TRGCOND_Msk);
	
    return;
}

/**
  * @brief Enable the interrupt(s) selected by u32Mask parameter.
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32Mask The combination of interrupt status bits listed below. Each bit
  *                    corresponds to a interrupt status. This parameter decides which
  *                    interrupts will be enabled.
  *                     - \ref ADC_ADF_INT    :ADC convert complete interrupt
  *                     - \ref ADC_CMP0_INT   :ADC comparator 0 interrupt
  *                     - \ref ADC_CMP1_INT   :ADC comparator 1 interrupt
  * @return None
  */
void ADC_EnableInt(ADC_T *adc, uint32_t u32Mask)
{
    if((u32Mask) & ADC_ADF_INT)
        (adc)->ADCR |= ADC_ADCR_ADIE_Msk;
    if((u32Mask) & ADC_CMP0_INT)
        (adc)->ADCMPR[0] |= ADC_ADCMPR_CMPIE_Msk;
    if((u32Mask) & ADC_CMP1_INT)
        (adc)->ADCMPR[1] |= ADC_ADCMPR_CMPIE_Msk;

    return;
}

/**
  * @brief Disable the interrupt(s) selected by u32Mask parameter.
  * @param[in] adc The pointer of the specified ADC module
  * @param[in] u32Mask The combination of interrupt status bits listed below. Each bit
  *                    corresponds to a interrupt status. This parameter decides which
  *                    interrupts will be disabled.
  *                     - \ref ADC_ADF_INT     :ADC convert complete interrupt
  *                     - \ref ADC_CMP0_INT    :ADC comparator 0 interrupt
  *                     - \ref ADC_CMP1_INT    :ADC comparator 1 interrupt
  * @return None
  */
void ADC_DisableInt(ADC_T *adc, uint32_t u32Mask)
{
    if((u32Mask) & ADC_ADF_INT)
        (adc)->ADCR &= ~ADC_ADCR_ADIE_Msk;
    if((u32Mask) & ADC_CMP0_INT)
        (adc)->ADCMPR[0] &= ~ADC_ADCMPR_CMPIE_Msk;
    if((u32Mask) & ADC_CMP1_INT)
        (adc)->ADCMPR[1] &= ~ADC_ADCMPR_CMPIE_Msk;

    return;
}

/**
  * @brief Set ADC extend sample time.
  * @param[in] adc The pointer of the specified ADC module.
  * @param[in] u32ModuleNum Decides the sample module number, not used in M2A23.
  * @param[in] u32ExtendSampleTime Decides the extend sampling time, the range is from 0~255 ADC clock. Valid value are from 0 to 0xFF. \n
  * 															 Extended Sampling Time = (u32ExtendSampleTime+1) x ADC_CLK period.
  * @return None
  * @details When A/D converting at high conversion rate, the sampling time of analog input voltage may not enough if input channel loading is heavy,
  *         user can extend A/D sampling time after trigger source is coming to get enough sampling time.
  */
void ADC_SetExtendSampleTime(ADC_T *adc, uint32_t u32ModuleNum, uint32_t u32ExtendSampleTime)
{
    (adc)->ADCR = (((adc)->ADCR & ~ADC_ADCR_EXTSMPT_Msk) | (u32ExtendSampleTime << ADC_ADCR_EXTSMPT_Pos));
}


/*@}*/ /* end of group ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group ADC_Driver */

/*@}*/ /* end of group Standard_Driver */

