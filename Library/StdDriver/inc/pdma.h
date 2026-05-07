/**************************************************************************//**
 * @file     pdma.h
 * @version  V3.00
 * @brief    PDMA driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2023 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PDMA_H__
#define __PDMA_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PDMA_Driver PDMA Driver
  @{
*/

/** @addtogroup PDMA_EXPORTED_CONSTANTS PDMA Exported Constants
  @{
*/
#define PDMA_CH_MAX         6UL   /*!< Specify Maximum Channels of PDMA  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Operation Mode Constant Definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_OP_STOP        0x00000000UL            /*!<DMA Stop Mode  \hideinitializer */
#define PDMA_OP_BASIC       0x00000001UL            /*!<DMA Basic Mode  \hideinitializer */
#define PDMA_OP_SCATTER     0x00000002UL            /*!<DMA Scatter-gather Mode  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Data Width Constant Definitions                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_WIDTH_8        0x00000000UL            /*!<DMA Transfer Width 8-bit  \hideinitializer */
#define PDMA_WIDTH_16       0x00001000UL            /*!<DMA Transfer Width 16-bit  \hideinitializer */
#define PDMA_WIDTH_32       0x00002000UL            /*!<DMA Transfer Width 32-bit  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Address Attribute Constant Definitions                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_SAR_INC        0x00000000UL            /*!<DMA SAR increment  \hideinitializer */
#define PDMA_SAR_FIX        0x00000300UL            /*!<DMA SAR fix address  \hideinitializer */
#define PDMA_DAR_INC        0x00000000UL            /*!<DMA DAR increment  \hideinitializer */
#define PDMA_DAR_FIX        0x00000C00UL            /*!<DMA DAR fix address  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Burst Mode Constant Definitions                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_REQ_SINGLE     0x00000004UL            /*!<DMA Single Request  \hideinitializer */
#define PDMA_REQ_BURST      0x00000000UL            /*!<DMA Burst Request  \hideinitializer */

#define PDMA_BURST_128      0x00000000UL            /*!<DMA Burst 128 Transfers  \hideinitializer */
#define PDMA_BURST_64       0x00000010UL            /*!<DMA Burst 64 Transfers  \hideinitializer */
#define PDMA_BURST_32       0x00000020UL            /*!<DMA Burst 32 Transfers  \hideinitializer */
#define PDMA_BURST_16       0x00000030UL            /*!<DMA Burst 16 Transfers  \hideinitializer */
#define PDMA_BURST_8        0x00000040UL            /*!<DMA Burst 8 Transfers  \hideinitializer */
#define PDMA_BURST_4        0x00000050UL            /*!<DMA Burst 4 Transfers  \hideinitializer */
#define PDMA_BURST_2        0x00000060UL            /*!<DMA Burst 2 Transfers  \hideinitializer */
#define PDMA_BURST_1        0x00000070UL            /*!<DMA Burst 1 Transfers  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Table Interrupt Disable Constant Definitions                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_TBINTDIS_ENABLE  (0x0UL<<PDMA_DSCT_CTL_TBINTDIS_Pos)  /*!<DMA Table Interrupt Enabled   \hideinitializer */
#define PDMA_TBINTDIS_DISABLE (0x1UL<<PDMA_DSCT_CTL_TBINTDIS_Pos)  /*!<DMA Table Interrupt Disabled  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Peripheral Transfer Mode Constant Definitions                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_MEM                   0UL /*!<PDMA channel request source select to MEM */
#define PDMA_UART0_TX              1UL /*!<PDMA channel request source select to UART0_TX */
#define PDMA_UART0_RX              2UL /*!<PDMA channel request source select to UART0_RX */
#define PDMA_UART1_TX              3UL /*!<PDMA channel request source select to UART1_TX */
#define PDMA_UART1_RX              4UL /*!<PDMA channel request source select to UART1_RX */
#define PDMA_USCI0_TX              5UL /*!<PDMA channel request source select to USCI0_TX */
#define PDMA_USCI0_RX              6UL /*!<PDMA channel request source select to USCI0_RX */
#define PDMA_USCI1_TX              7UL /*!<PDMA channel request source select to USCI1_TX */
#define PDMA_USCI1_RX              8UL /*!<PDMA channel request source select to USCI1_RX */
#define PDMA_SPI0_TX               9UL /*!<PDMA channel request source select to SPI0_TX */
#define PDMA_SPI0_RX              10UL /*!<PDMA channel request source select to SPI0_RX */
#define PDMA_I2C0_TX              11UL /*!<PDMA channel request source select to I2C0_TX */
#define PDMA_I2C0_RX              12UL /*!<PDMA channel request source select to I2C0_RX */
#define PDMA_TMR0                 13UL /*!<PDMA channel request source select to TMR0 */
#define PDMA_TMR1                 14UL /*!<PDMA channel request source select to TMR1 */
#define PDMA_TMR2                 15UL /*!<PDMA channel request source select to TMR2 */
#define PDMA_TMR3                 16UL /*!<PDMA channel request source select to TMR3 */
#define PDMA_ADC0_RX              17UL /*!<PDMA channel request source select to ADC0_RX */
#define PDMA_ACMP0                18UL /*!<PDMA channel request source select to ACMP0 */
#define PDMA_ACMP1                19UL /*!<PDMA channel request source select to ACMP1 */
#define PDMA_PWM0_P1_RX           20UL /*!<PDMA channel request source select to PWM0_P1_RX */
#define PDMA_PWM0_P2_RX           21UL /*!<PDMA channel request source select to PWM0_P2_RX */
#define PDMA_PWM0_P3_RX           22UL /*!<PDMA channel request source select to PWM0_P3_RX */
#define PDMA_PWM0_CH0_TX          23UL /*!<PDMA channel request source select to PWM0_CH0_TX */
#define PDMA_PWM0_CH2_TX          24UL /*!<PDMA channel request source select to PWM0_CH2_TX */
#define PDMA_PWM0_CH4_TX          25UL /*!<PDMA channel request source select to PWM0_CH4_TX */
#define PDMA_EINT0                26UL /*!<PDMA channel request source select to EINT0 */
#define PDMA_EINT1                27UL /*!<PDMA channel request source select to EINT1 */
#define PDMA_EINT2                28UL /*!<PDMA channel request source select to EINT2 */
#define PDMA_EINT3                29UL /*!<PDMA channel request source select to EINT3 */
#define PDMA_EINT4                30UL /*!<PDMA channel request source select to EINT4 */
#define PDMA_EINT5                31UL /*!<PDMA channel request source select to EINT5 */
#define PDMA_LLSI0                32UL /*!<PDMA channel request source select to LLSI0 */
#define PDMA_LLSI1                33UL /*!<PDMA channel request source select to LLSI1 *//*---------------------------------------------------------------------------------------------------------*/
/*  Interrupt Type Constant Definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_INT_TRANS_DONE 0x00000000UL            /*!<Transfer Done Interrupt  \hideinitializer */
#define PDMA_INT_TEMPTY     0x00000001UL            /*!<Table Empty Interrupt  \hideinitializer */
#define PDMA_INT_TIMEOUT    0x00000002UL            /*!<Timeout Interrupt \hideinitializer */


/*@}*/ /* end of group PDMA_EXPORTED_CONSTANTS */

/** @addtogroup PDMA_EXPORTED_FUNCTIONS PDMA Exported Functions
  @{
*/

/**
 * @brief       Get PDMA Interrupt Status
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @return      None
 *
 * @details     This macro gets the interrupt status.
 * \hideinitializer
 */
#define PDMA_GET_INT_STATUS(pdma) ((uint32_t)(pdma->INTSTS))

/**
 * @brief       Get Transfer Done Interrupt Status
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @return      None
 *
 * @details     Get the transfer done Interrupt status.
 * \hideinitializer
 */
#define PDMA_GET_TD_STS(pdma) ((uint32_t)(pdma->TDSTS))

/**
 * @brief       Clear Transfer Done Interrupt Status
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @param[in]   u32Mask     The channel mask
 *
 * @return      None
 *
 * @details     Clear the transfer done Interrupt status.
 * \hideinitializer
 */
#define PDMA_CLR_TD_FLAG(pdma,u32Mask) ((uint32_t)(pdma->TDSTS = (u32Mask)))

/**
 * @brief       Get Target Abort Interrupt Status
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @return      None
 *
 * @details     Get the target abort Interrupt status.
 * \hideinitializer
 */
#define PDMA_GET_ABORT_STS(pdma) ((uint32_t)(pdma->ABTSTS))

/**
 * @brief       Clear Target Abort Interrupt Status
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @param[in]   u32Mask     The channel mask
 *
 * @return      None
 *
 * @details     Clear the target abort Interrupt status.
 * \hideinitializer
 */
#define PDMA_CLR_ABORT_FLAG(pdma,u32Mask) ((uint32_t)(pdma->ABTSTS = (u32Mask)))

/**
 * @brief       Get Alignment Interrupt Status
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @return      None
 *
 * @details     Get Alignment Interrupt status.
 * \hideinitializer
 */
#define PDMA_GET_ALIGN_STS(pdma) ((uint32_t)(pdma->ALIGN))

/**
 * @brief       Clear Alignment Interrupt Status
  *
 * @param[in]   pdma        The pointer of the specified PDMA module
 * @param[in]   u32Mask     The channel mask
 *
 * @return      None
 *
 * @details     Clear the Alignment Interrupt status.
 * \hideinitializer
 */
#define PDMA_CLR_ALIGN_FLAG(pdma,u32Mask) ((uint32_t)(pdma->ALIGN = (u32Mask)))

/**
 * @brief       Clear Timeout Interrupt Status
  *
 * @param[in]   pdma      The pointer of the specified PDMA module
 * @param[in]   u32Ch     The selected channel
 *
 * @return      None
 *
 * @details     Clear the selected channel timeout interrupt status.
 * \hideinitializer
 */
#define PDMA_CLR_TMOUT_FLAG(pdma,u32Ch) ((uint32_t)(pdma->INTSTS = (1UL << ((u32Ch) + 8UL))))

/**
 * @brief       Check Channel Status
  *
 * @param[in]   pdma      The pointer of the specified PDMA module
 * @param[in]   u32Ch     The selected channel
 *
 * @retval      0 Idle state
 * @retval      1 Busy state
 *
 * @details     Check the selected channel is busy or not.
 * \hideinitializer
 */
#define PDMA_IS_CH_BUSY(pdma,u32Ch) ((uint32_t)(pdma->TRGSTS & (1UL << (u32Ch)))? 1 : 0)

/**
 * @brief       Set Source Address
  *
 * @param[in]   pdma      The pointer of the specified PDMA module
 * @param[in]   u32Ch     The selected channel
 * @param[in]   u32Addr   The selected address
 *
 * @return      None
 *
 * @details     This macro set the selected channel source address.
 * \hideinitializer
 */
#define PDMA_SET_SRC_ADDR(pdma,u32Ch, u32Addr) ((uint32_t)(pdma->DSCT[(u32Ch)].SA = (u32Addr)))

/**
 * @brief       Set Destination Address
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 * @param[in]   u32Ch     The selected channel
 * @param[in]   u32Addr   The selected address
 *
 * @return      None
 *
 * @details     This macro set the selected channel destination address.
 * \hideinitializer
 */
#define PDMA_SET_DST_ADDR(pdma,u32Ch, u32Addr) ((uint32_t)(pdma->DSCT[(u32Ch)].DA = (u32Addr)))

/**
 * @brief       Set Transfer Count
  *
 * @param[in]   pdma           The pointer of the specified PDMA module
 * @param[in]   u32Ch          The selected channel
 * @param[in]   u32TransCount  Transfer Count
 *
 * @return      None
 *
 * @details     This macro set the selected channel transfer count.
 * \hideinitializer
 */
#define PDMA_SET_TRANS_CNT(pdma,u32Ch, u32TransCount) ((uint32_t)(pdma->DSCT[(u32Ch)].CTL=(pdma->DSCT[(u32Ch)].CTL&~PDMA_DSCT_CTL_TXCNT_Msk)|(((u32TransCount)-1UL) << PDMA_DSCT_CTL_TXCNT_Pos)))

/**
 * @brief       Set Scatter-gather descriptor Address
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 * @param[in]   u32Ch     The selected channel
 * @param[in]   u32Addr   The descriptor address
 *
 * @return      None
 *
 * @details     This macro set the selected channel scatter-gather descriptor address.
 * \hideinitializer
 */
#define PDMA_SET_SCATTER_DESC(pdma,u32Ch, u32Addr) ((uint32_t)(pdma->DSCT[(u32Ch)].NEXT = (u32Addr) - (pdma->SCATBA)))

/**
 * @brief       Stop the channel
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @param[in]   u32Ch     The selected channel
 *
 * @return      None
 *
 * @details     This macro stop the selected channel.
 * \hideinitializer
 */
#define PDMA_STOP(pdma,u32Ch) ((uint32_t)(pdma->PAUSE = (1UL << (u32Ch))))

/**
 * @brief       Pause the channel
 *
 * @param[in]   pdma      The pointer of the specified PDMA module
 *
 * @param[in]   u32Ch     The selected channel
 *
 * @return      None
 *
 * @details     This macro pause the selected channel.
 * \hideinitializer
 */
#define PDMA_PAUSE(pdma,u32Ch) ((uint32_t)(pdma->PAUSE = (1UL << (u32Ch))))

/*---------------------------------------------------------------------------------------------------------*/
/* Define PDMA functions prototype                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
void PDMA_Open(PDMA_T * pdma,uint32_t u32Mask);
void PDMA_Close(PDMA_T * pdma);
void PDMA_SetTransferCnt(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Width, uint32_t u32TransCount);
void PDMA_SetTransferAddr(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32SrcAddr, uint32_t u32SrcCtrl, uint32_t u32DstAddr, uint32_t u32DstCtrl);
void PDMA_SetTransferMode(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Peripheral, uint32_t u32ScatterEn, uint32_t u32DescAddr);
void PDMA_SetBurstType(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32BurstType, uint32_t u32BurstSize);
void PDMA_EnableTimeout(PDMA_T * pdma,uint32_t u32Mask);
void PDMA_DisableTimeout(PDMA_T * pdma,uint32_t u32Mask);
void PDMA_SetTimeOut(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32OnOff, uint32_t u32TimeOutCnt);
void PDMA_Trigger(PDMA_T * pdma,uint32_t u32Ch);
void PDMA_EnableInt(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Mask);
void PDMA_DisableInt(PDMA_T * pdma,uint32_t u32Ch, uint32_t u32Mask);


/*@}*/ /* end of group PDMA_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PDMA_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __PDMA_H__ */

/*** (C) COPYRIGHT 2023 Nuvoton Technology Corp. ***/
