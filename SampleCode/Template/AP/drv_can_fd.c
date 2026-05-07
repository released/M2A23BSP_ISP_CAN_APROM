/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "drv_can_fd.h"
/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

CANFD_FD_MSG_T g_sRxMsgFrame;
CANFD_FD_MSG_T g_sTxMsgFrame;

volatile uint32_t g_u32CanIrqStatus = 0;
static uint8_t g_u8CanFdModeOpened = 0;
uint8_t msg_tx_buffer_idx = 0;

uint8_t num_cnt = 0;
/*_____ M A C R O S ________________________________________________________*/
#define CANFD_RX_INT_MASK    (CANFD_IR_RF0N_Msk | CANFD_IR_RF0L_Msk | CANFD_IR_RF1N_Msk | CANFD_IR_RF1L_Msk)
#define CANFD_TX_RETRY_MAX   (10U)

/*_____ F U N C T I O N S __________________________________________________*/

static void CAN_DumpBusStatus(void)
{
    uint8_t u8TxErr = 0;
    uint8_t u8RxErr = 0;

    CANFD_GetBusErrCount(CANFD0, &u8TxErr, &u8RxErr);
    printf("CAN status: PSR=0x%08X ECR=0x%08X IR=0x%08X (TEC=%u REC=%u)\r\n",
           CANFD0->PSR, CANFD0->ECR, CANFD0->IR, u8TxErr, u8RxErr);

    if (CANFD0->IR & CANFD_IR_PED_Msk)
    {
        printf("Hint: PED=1, check FD data phase settings (ISO/Non-ISO mode, data bitrate, BRS).\r\n");
    }
}

static uint32_t CAN_GetModuleClock(CANFD_T *psCanfd)
{
    uint32_t u32ClkSrc = 0U;
    uint32_t u32ClkDiv = 1U;
    uint32_t u32CanClk = 0U;

    if (psCanfd == CANFD0)
    {
        u32ClkSrc = CLK_GetModuleClockSource(CANFD0_MODULE);
        u32ClkDiv = ((CLK->CLKDIV1 & CLK_CLKDIV1_CANFD0DIV_Msk) >> CLK_CLKDIV1_CANFD0DIV_Pos) + 1U;
    }
#if defined(CANFD1)
    else if (psCanfd == CANFD1)
    {
        u32ClkSrc = CLK_GetModuleClockSource(CANFD1_MODULE);
        u32ClkDiv = ((CLK->CLKDIV1 & CLK_CLKDIV1_CANFD1DIV_Msk) >> CLK_CLKDIV1_CANFD1DIV_Pos) + 1U;
    }
#endif
#if defined(CANFD2)
    else if (psCanfd == CANFD2)
    {
        u32ClkSrc = CLK_GetModuleClockSource(CANFD2_MODULE);
        u32ClkDiv = ((CLK->CLKDIV1 & CLK_CLKDIV1_CANFD2DIV_Msk) >> CLK_CLKDIV1_CANFD2DIV_Pos) + 1U;
    }
#endif
    else
    {
        return 0U;
    }

    if (u32ClkSrc == 0U)
    {
        u32CanClk = CLK_GetHXTFreq();
    }
    else if (u32ClkSrc == 1U)
    {
        u32CanClk = CLK_GetPLLClockFreq() / 2U;
    }
    else if (u32ClkSrc == 2U)
    {
        u32CanClk = CLK_GetHCLKFreq();
    }
    else
    {
        u32CanClk = __HIRC;
    }

    return (u32CanClk / u32ClkDiv);
}


static void CAN_PrintRxMessage(uint8_t u8FifoIdx, CANFD_FD_MSG_T *psRxMsg)
{
    uint8_t u8Cnt;

    if (psRxMsg->eIdType == eCANFD_SID)
    {
        printf("Rx FIFO%u [%s] Standard ID = 0x%08X\r\n",
               u8FifoIdx, psRxMsg->bFDFormat ? "CAN FD" : "CAN", psRxMsg->u32Id);
    }
    else
    {
        printf("Rx FIFO%u [%s] Extended ID = 0x%08X\r\n",
               u8FifoIdx, psRxMsg->bFDFormat ? "CAN FD" : "CAN", psRxMsg->u32Id);
    }

    printf("Message Data(%02u bytes) : ", psRxMsg->u32DLC);

    for (u8Cnt = 0; u8Cnt < psRxMsg->u32DLC; u8Cnt++)
    {
        printf("0x%02X ", psRxMsg->au8Data[u8Cnt]);
    }

    printf("\r\n");
}

static uint32_t CAN_RxFifo0FillLevel(void)
{
    return (CANFD0->RXF0S & CANFD_RXF0S_F0FL_Msk);
}

static uint32_t CAN_RxFifo1FillLevel(void)
{
    return (CANFD0->RXF1S & CANFD_RXF1S_F1FL_Msk);
}

#if (CANFD_MODULE == 0)
void CANFD00_IRQHandler(void)
#elif (CANFD_MODULE == 1)
void CANFD10_IRQHandler(void)
#elif (CANFD_MODULE == 2)
void CANFD20_IRQHandler(void)
#else
void CANFD20_IRQHandler(void)
#endif
{
    uint32_t u32IrqStatus = CANFD_GetStatusFlag(CANFD0, CANFD_RX_INT_MASK);

    if (u32IrqStatus == 0)
    {
        return;
    }

    g_u32CanIrqStatus |= u32IrqStatus;
    CANFD_ClearStatusFlag(CANFD0, u32IrqStatus);
}

void CAN_Rx_process(void)
{
    uint32_t u32IrqStatus;
    uint32_t u32RxResult;
    uint32_t u32Fifo0FillLevel;
    uint32_t u32Fifo1FillLevel;

    __disable_irq();
    u32IrqStatus = g_u32CanIrqStatus;
    g_u32CanIrqStatus = 0;
    __enable_irq();

    u32Fifo0FillLevel = CAN_RxFifo0FillLevel();
    u32Fifo1FillLevel = CAN_RxFifo1FillLevel();

    if ((u32IrqStatus == 0U) && (u32Fifo0FillLevel == 0U) && (u32Fifo1FillLevel == 0U))
    {
        return;
    }

    if ((u32IrqStatus & CANFD_IR_RF0L_Msk) || (CANFD0->RXF0S & CANFD_RXF0S_RF0L_Msk))
    {
        printf("Warning: RX FIFO0 message lost\r\n");
    }

    if ((u32IrqStatus & (CANFD_IR_RF0N_Msk | CANFD_IR_RF0L_Msk)) || (u32Fifo0FillLevel != 0U))
    {
        do
        {
            u32RxResult = CANFD_ReadRxFifoMsg(CANFD0, 0, &g_sRxMsgFrame);
            if (u32RxResult != eCANFD_RECEIVE_EMPTY)
            {
                CAN_PrintRxMessage(0, &g_sRxMsgFrame);
            }
        }
        while ((u32RxResult != eCANFD_RECEIVE_EMPTY) && (CAN_RxFifo0FillLevel() != 0U));
    }

    if ((u32IrqStatus & CANFD_IR_RF1L_Msk) || (CANFD0->RXF1S & CANFD_RXF1S_RF1L_Msk))
    {
        printf("Warning: RX FIFO1 message lost\r\n");
    }

    if ((u32IrqStatus & (CANFD_IR_RF1N_Msk | CANFD_IR_RF1L_Msk)) || (u32Fifo1FillLevel != 0U))
    {
        do
        {
            u32RxResult = CANFD_ReadRxFifoMsg(CANFD0, 1, &g_sRxMsgFrame);
            if (u32RxResult != eCANFD_RECEIVE_EMPTY)
            {
                CAN_PrintRxMessage(1, &g_sRxMsgFrame);
            }
        }
        while ((u32RxResult != eCANFD_RECEIVE_EMPTY) && (CAN_RxFifo1FillLevel() != 0U));
    }

    memset(&g_sRxMsgFrame, 0, sizeof(g_sRxMsgFrame));
}

void CAN_SendMessage(uint8_t en_can_fd, CANFD_FD_MSG_T *psTxMsg, E_CANFD_ID_TYPE eIdType, uint32_t u32Id, uint8_t u8Len)
{
    uint8_t u8Cnt;
    uint8_t u8Retry;

    if ((en_can_fd != 0U) && (g_u8CanFdModeOpened == 0U))
    {
        printf("Blocked FD TX (ID:0x%08X): controller is in Classical CAN mode\r\n", u32Id);
        printf("Set CAN_APP_ENABLE_FD_MODE=1 and set PCAN to CAN FD mode first.\r\n");
        return;
    }

    psTxMsg->u32Id = u32Id;
    psTxMsg->eIdType = eIdType;
    psTxMsg->eFrmType = eCANFD_DATA_FRM;
    psTxMsg->bFDFormat = (en_can_fd != 0U) ? 1U : 0U;
    psTxMsg->bBitRateSwitch = (en_can_fd != 0U) ? 1U : 0U;

    if ((en_can_fd == 0U) && (u8Len > 8U))
    {
        u8Len = 8U;
    }

    psTxMsg->u32DLC = u8Len;

    for (u8Cnt = 0; u8Cnt < psTxMsg->u32DLC; u8Cnt++)
    {
        psTxMsg->au8Data[u8Cnt] = u8Cnt + num_cnt;
    } 

    #if 1
    /* use message buffer 0 */
    if (eIdType == eCANFD_SID)
        printf("Send to transmit message 0x%08x (11-bit)\n", psTxMsg->u32Id);
    else
        printf("Send to transmit message 0x%08x (29-bit)\n", psTxMsg->u32Id);
    #endif

    // if (CANFD_TransmitTxMsg(CANFD0, 0, psTxMsg) != eCANFD_TRANSMIT_SUCCESS)
    // {
    //     printf("Failed to transmit message\n");
    // }

    for (u8Retry = 0; u8Retry < CANFD_TX_RETRY_MAX; u8Retry++)
    {
        if (CANFD_TransmitTxMsg(CANFD0, msg_tx_buffer_idx, psTxMsg) == eCANFD_TRANSMIT_SUCCESS)
        {
            #if 1
            printf("tx request queued\r\n");
            #endif
            return;
        }
    }

    printf("Failed to transmit message (ID:0x%08X)\r\n", psTxMsg->u32Id);
    CAN_DumpBusStatus();
}


/*---------------------------------------------------------------------------*/
/*  Get the CANFD interface Nominal bit rate Function                        */
/*---------------------------------------------------------------------------*/
uint32_t Get_CANFD_NominalBitRate(CANFD_T *psCanfd)
{
    uint32_t u32BitRate = 0;
    uint32_t u32CanClk  = 0;
    uint8_t  u8Tq = 0;
    uint8_t  u8NtSeg1 = 0;
    uint8_t  u8NtSeg2 = 0;

    u32CanClk = CAN_GetModuleClock(psCanfd);
    if (u32CanClk == 0U)
    {
        return 0U;
    }

    u8Tq = ((psCanfd->NBTP & CANFD_NBTP_NBRP_Msk) >> CANFD_NBTP_NBRP_Pos) + 1 ;
    u8NtSeg1 = ((psCanfd->NBTP & CANFD_NBTP_NTSEG1_Msk) >> CANFD_NBTP_NTSEG1_Pos);
    u8NtSeg2 = ((psCanfd->NBTP & CANFD_NBTP_NTSEG2_Msk) >> CANFD_NBTP_NTSEG2_Pos);
    u32BitRate = u32CanClk / u8Tq / (u8NtSeg1 + u8NtSeg2 + 3);

    return u32BitRate;
}
/*---------------------------------------------------------------------------*/
/*  Get the CANFD interface Data bit rate Function                           */
/*---------------------------------------------------------------------------*/
uint32_t Get_CANFD_DataBitRate(CANFD_T *psCanfd)
{
    uint32_t u32BitRate = 0;
    uint32_t u32CanClk  = 0;
    uint8_t  u8Tq = 0;
    uint8_t  u8NtSeg1 = 0;
    uint8_t  u8NtSeg2 = 0;

    u32CanClk = CAN_GetModuleClock(psCanfd);
    if (u32CanClk == 0U)
    {
        return 0U;
    }

    u8Tq = ((psCanfd->DBTP & CANFD_DBTP_DBRP_Msk) >> CANFD_DBTP_DBRP_Pos) + 1 ;
    u8NtSeg1 = ((psCanfd->DBTP & CANFD_DBTP_DTSEG1_Msk) >> CANFD_DBTP_DTSEG1_Pos);
    u8NtSeg2 = ((psCanfd->DBTP & CANFD_DBTP_DTSEG2_Msk) >> CANFD_DBTP_DTSEG2_Pos);
    u32BitRate = u32CanClk / u8Tq / (u8NtSeg1 + u8NtSeg2 + 3);

    return u32BitRate;
}

void CAN_Init(void)
{
    CANFD_FD_T sCANFD_Config;
    uint32_t u32ActualNomBitRate;
    uint32_t u32ActualDataBitRate;

    uint32_t u32NormBitRate = CAN_APP_NOMINAL_BITRATE;
    uint32_t u32DataBitRate = CAN_APP_DATA_BITRATE;

    SYS_ResetModule(CANFD0_RST);

#if (CAN_APP_ENABLE_FD_MODE == 1U)
    CANFD_GetDefaultConfig(&sCANFD_Config, CANFD_OP_CAN_FD_MODE);
    g_u8CanFdModeOpened = 1U;
#else
    CANFD_GetDefaultConfig(&sCANFD_Config, CANFD_OP_CAN_MODE);
    g_u8CanFdModeOpened = 0U;
#endif

    sCANFD_Config.sBtConfig.sNormBitRate.u32BitRate = u32NormBitRate;
    if (g_u8CanFdModeOpened)
    {
        sCANFD_Config.sBtConfig.sDataBitRate.u32BitRate = u32DataBitRate;
    }
    else
    {
        sCANFD_Config.sBtConfig.sDataBitRate.u32BitRate = 0U;
    }
    CANFD_Open(CANFD0, &sCANFD_Config);

#if (CAN_APP_ENABLE_FD_MODE == 1U)
    if (g_u8CanFdModeOpened)
    {
#if (CAN_APP_FD_NON_ISO_MODE == 1U)
        CANFD0->CCCR |= CANFD_CCCR_NISO_Msk;
#else
        CANFD0->CCCR &= ~CANFD_CCCR_NISO_Msk;
#endif
    }
#endif

    u32ActualNomBitRate = Get_CANFD_NominalBitRate(CANFD0);
    u32ActualDataBitRate = Get_CANFD_DataBitRate(CANFD0);

    printf("CAN mode: %s\r\n", g_u8CanFdModeOpened ? "CAN FD" : "Classical CAN");
    if (g_u8CanFdModeOpened)
    {
        printf("FD protocol: %s\r\n", (CANFD0->CCCR & CANFD_CCCR_NISO_Msk) ? "Non-ISO" : "ISO");
    }
    printf("Nominal baud rate(bps): %u\r\n", u32ActualNomBitRate);
    printf("Data baud rate(bps): %u\r\n", u32ActualDataBitRate);
    if (g_u8CanFdModeOpened)
    {
        printf("PCAN setting: CAN FD mode, Nominal=%u, Data=%u\r\n", u32NormBitRate, u32DataBitRate);
        if ((u32ActualNomBitRate != u32NormBitRate) || (u32ActualDataBitRate != u32DataBitRate))
        {
            printf("Warning: CAN FD timing mismatch, check CAN clock source / bitrate settings.\r\n");
        }
    }
    else
    {
        printf("PCAN setting: Classical CAN mode, Baud=%u\r\n", u32NormBitRate);
        if (u32ActualNomBitRate != u32NormBitRate)
        {
            printf("Warning: CAN timing mismatch, check CAN clock source / bitrate settings.\r\n");
        }
    }

    #if defined (ENABLE_MONITOR_MODE)
    /*Enable the Bus Monitoring Mode */
    CANFD0->CCCR |= CANFD_CCCR_MON_Msk;
    #endif

    /* Clear all pending status before enabling interrupt */
    CANFD_ClearStatusFlag(CANFD0, CANFD_INT_ALL_SIGNALS);

    /* Non-matching Frames with Extended ID and Standard ID are stored in Rx FIFO0 or Rx FIFO1, reject all remote frames with 11-bit standard IDs and 29-bit extended IDs */
    CANFD_SetGFC(CANFD0, eCANFD_ACC_NON_MATCH_FRM_RX_FIFO0, eCANFD_ACC_NON_MATCH_FRM_RX_FIFO1, 1, 1);
    /* Enable RX FIFO New message, Message lost interrupt using interrupt line 0 */
    CANFD_EnableInt(CANFD0, (CANFD_IE_RF0NE_Msk | CANFD_IE_RF0LE_Msk | CANFD_IE_RF1NE_Msk | CANFD_IE_RF1LE_Msk), 0, 0, 0);

#if (CANFD_MODULE == 0)
    NVIC_EnableIRQ(CANFD00_IRQn);
#elif (CANFD_MODULE == 1)
    NVIC_EnableIRQ(CANFD10_IRQn);
#elif (CANFD_MODULE == 2)
    NVIC_EnableIRQ(CANFD20_IRQn);
#else
    NVIC_EnableIRQ(CANFD20_IRQn);
#endif

    /* CAN FD Run to Normal mode */
    CANFD_RunToNormal(CANFD0, TRUE);
}
