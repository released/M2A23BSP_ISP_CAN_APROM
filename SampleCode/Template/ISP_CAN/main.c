/***************************************************************************//**
 * @file     main.c
 * @brief    CAN ISP bootloader (LDROM, Classical CAN only)
 ******************************************************************************/
#include "NuMicro.h"
#include "memory_map.h"

#define CAN_BAUD_RATE                     (500000U)
#define MASTER_ISP_ID                     (0x487U)
#define DEVICE_ISP_ID                     (0x784U)
#define CAN_ISP_DATA_LENGTH               (8U)
#define UART0_BAUD_RATE                   (115200U)
#define UART0_CLK_SRC_HZ                  (__HIRC)

#define CMD_READ_CONFIG                   (0xA2000000UL)
#define CMD_RUN_APROM                     (0xAB000000UL)
#define CMD_GET_DEVICEID                  (0xB1000000UL)

#define BOOT_DEBUG_PRINT_CMD              (0)

/*
 * Reference options for future tuning:
 * 1) Keep a short ISP window even when APP is valid, e.g. 100 ms.
 *    #define BOOT_WAIT_TIMEOUT_MS_APP_VALID    (100UL)
 * 2) Force boot mode by GPIO key (pressed -> stay in boot for CAN ISP).
 *    Example:
 *      - Configure one GPIO as input with pull-up.
 *      - If key is pressed at power-on, skip APP jump and stay in boot.
 */
#define BOOT_WAIT_TIMEOUT_MS              (5000UL)

typedef struct
{
    uint32_t Address;
    uint32_t Data;
} STR_CANMSG_ISP_T;

static volatile CANFD_FD_MSG_T g_sRxMsgFrame;
static volatile uint8_t g_u8CANPacketReady;

static void UART0_WriteByte(uint8_t u8Data)
{
    while (UART_IS_TX_FULL(UART0))
    {
    }

    UART_WRITE(UART0, u8Data);
}

static void UART0_WriteString(const char *pcStr)
{
    if (pcStr == (const char *)0)
    {
        return;
    }

    while (*pcStr != '\0')
    {
        if (*pcStr == '\n')
        {
            UART0_WriteByte('\r');
        }

        UART0_WriteByte((uint8_t)*pcStr);
        pcStr++;
    }
}

static void UART0_WriteHex32(uint32_t u32Value)
{
    uint8_t i;

    for (i = 0U; i < 8U; i++)
    {
        uint32_t u32Shift = 28U - (uint32_t)(i * 4U);
        uint8_t u8Nibble = (uint8_t)((u32Value >> u32Shift) & 0x0FUL);
        uint8_t u8Ch = (u8Nibble < 10U) ? (uint8_t)('0' + u8Nibble) : (uint8_t)('A' + (u8Nibble - 10U));
        UART0_WriteByte(u8Ch);
    }
}

static void UART0_Init(void)
{
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL2_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    SET_UART0_RXD_PB12();
    SET_UART0_TXD_PB13();
    SYS_ResetModule(UART0_RST);

    UART0->LINE = (UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1);
    UART0->BAUD = (UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(UART0_CLK_SRC_HZ, UART0_BAUD_RATE));
}

static uint32_t App_Crc32(const uint32_t u32Start, const uint32_t u32Size)
{
    uint32_t u32Addr;
    uint32_t u32Crc = 0xFFFFFFFFUL;

    for (u32Addr = u32Start; u32Addr < (u32Start + u32Size); u32Addr += 4UL)
    {
        uint32_t u32Data = FMC_Read(u32Addr);
        uint8_t i;
        uint8_t b;

        for (i = 0U; i < 4U; i++)
        {
            uint8_t u8Byte = (uint8_t)(u32Data >> (i * 8U));
            u32Crc ^= u8Byte;
            for (b = 0U; b < 8U; b++)
            {
                if (u32Crc & 1UL)
                    u32Crc = (u32Crc >> 1U) ^ 0xEDB88320UL;
                else
                    u32Crc >>= 1U;
            }
        }
    }

    return ~u32Crc;
}

static uint8_t App_IsValid(void)
{
    uint32_t u32Sp = FMC_Read(APP_START_ADDR);
    uint32_t u32Rv = FMC_Read(APP_START_ADDR + 4UL);
    uint32_t u32StoredCrc = FMC_Read(APP_CHECKSUM_ADDR);
    uint32_t u32CalcCrc;

    if ((u32Sp < SRAM_BASE) || (u32Sp >= (SRAM_BASE + APP_SRAM_SIZE)))
    {
// #if BOOT_DEBUG_PRINT_CMD
//         UART0_WriteString("[boot]IV1-");
//         UART0_WriteHex32(u32Sp);
//         UART0_WriteString("\n");
// #endif
        return 0U;
    }

    if ((u32Rv < APP_START_ADDR) || (u32Rv >= APP_END_ADDR) || ((u32Rv & 1UL) == 0UL))
    {
#if BOOT_DEBUG_PRINT_CMD
        UART0_WriteString("[boot]IV2-");
        UART0_WriteHex32(u32Rv);
        UART0_WriteString("\n");
#endif
        return 0U;
    }

    if ((u32StoredCrc == 0xFFFFFFFFUL) || (u32StoredCrc == 0x00000000UL))
    {
#if BOOT_DEBUG_PRINT_CMD
        UART0_WriteString("[boot]IV3-");
        UART0_WriteHex32(u32StoredCrc);
        UART0_WriteString("\n");
#endif
        return 0U;
    }

    u32CalcCrc = App_Crc32(APP_START_ADDR, APP_SIZE_BYTES - 4UL);
    if (u32CalcCrc != u32StoredCrc)
    {
#if BOOT_DEBUG_PRINT_CMD
        UART0_WriteString("[boot]IV4-");
        UART0_WriteHex32(u32CalcCrc);
        UART0_WriteString(":");
        UART0_WriteHex32(u32StoredCrc);
        UART0_WriteString("\n");
#endif
        return 0U;
    }
    return 1U;
}

static void Boot_JumpToApplication(void)
{
    __set_PRIMASK(1);
    FMC_SetVectorPageAddr(APP_START_ADDR);
    SYS_ResetCPU();

    while (1)
    {
    }
}

void CANFD00_IRQHandler(void)
{
    uint32_t u32IrStatus = CANFD0->IR;

    if (u32IrStatus & CANFD_IR_RF0N_Msk)
    {
        CANFD_ClearStatusFlag(CANFD0, CANFD_IR_RF0N_Msk | CANFD_IR_TOO_Msk);
        CANFD_ReadRxFifoMsg(CANFD0, 0, (CANFD_FD_MSG_T *)&g_sRxMsgFrame);
        g_u8CANPacketReady = 1U;
    }
}

static int32_t SYS_Init(void)
{
    uint32_t u32TimeOutCnt;

    SYS_UnlockReg();

    /* Ensure XT1 pins are in input mode for external crystal */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);
    u32TimeOutCnt = SystemCoreClock;
    while (!(CLK->STATUS & CLK_STATUS_HIRCSTB_Msk))
        if (--u32TimeOutCnt == 0U) return -1;

    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);
    u32TimeOutCnt = SystemCoreClock;
    while (!(CLK->STATUS & CLK_STATUS_HXTSTB_Msk))
        if (--u32TimeOutCnt == 0U) return -1;

    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_HCLKSEL_Msk) | CLK_CLKSEL0_HCLKSEL_HXT;

    CLK->PLLCTL |= CLK_PLLCTL_PD_Msk;
    CLK->PLLCTL = CLK_PLLCTL_144MHz_HXT;

    u32TimeOutCnt = SystemCoreClock;
    while (!(CLK->STATUS & CLK_STATUS_PLLSTB_Msk))
        if (--u32TimeOutCnt == 0U) return -1;

    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_HCLKDIV_Msk) | CLK_CLKDIV0_HCLK(1);
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_HCLKSEL_Msk) | CLK_CLKSEL0_HCLKSEL_PLL_DIV2;

    SystemCoreClockUpdate();

    CLK_SetModuleClock(CANFD0_MODULE, CLK_CLKSEL0_CANFD0SEL_PLL_DIV2, CLK_CLKDIV1_CANFD0(1));
    CLK_EnableModuleClock(CANFD0_MODULE);

    UART0_Init();

    SET_CANFD0_RXD_PC4();
    SET_CANFD0_TXD_PC5();

    return 0;
}

static void CAN_Init(void)
{
    CANFD_FD_T sCANFD_Config;

    SYS_ResetModule(CANFD0_RST);

    CANFD_GetDefaultConfig(&sCANFD_Config, CANFD_OP_CAN_MODE);
    sCANFD_Config.sBtConfig.sDataBitRate.u32BitRate = 0U;

    sCANFD_Config.sBtConfig.sNormBitRate.u32BitRate = CAN_BAUD_RATE;
    CANFD_Open(CANFD0, &sCANFD_Config);

    CANFD_SetSIDFltr(CANFD0, 0, CANFD_RX_FIFO0_STD_MASK(MASTER_ISP_ID, 0x7FFUL));
    CANFD_SetGFC(CANFD0,
                 eCANFD_ACC_NON_MATCH_FRM_RX_FIFO0,
                 eCANFD_ACC_NON_MATCH_FRM_RX_FIFO0,
                 1,
                 1);

    CANFD_EnableInt(CANFD0, (CANFD_IE_RF0NE_Msk | CANFD_IE_TOOE_Msk), 0, 0, 0);
    NVIC_EnableIRQ(CANFD00_IRQn);

    CANFD_RunToNormal(CANFD0, TRUE);
}

static void CAN_SendAck(volatile STR_CANMSG_ISP_T *psMsg)
{
    CANFD_FD_MSG_T sTxMsg;

    sTxMsg.eFrmType = eCANFD_DATA_FRM;
    sTxMsg.eIdType = eCANFD_SID;
    sTxMsg.u32Id = DEVICE_ISP_ID;
    sTxMsg.u32DLC = CAN_ISP_DATA_LENGTH;
    sTxMsg.bFDFormat = 0U;
    sTxMsg.bBitRateSwitch = 0U;

    sTxMsg.au32Data[0] = psMsg->Address;
    sTxMsg.au32Data[1] = psMsg->Data;

    (void)CANFD_TransmitTxMsg(CANFD0, 0, &sTxMsg);
}

int main(void)
{
    uint8_t u8AppValid;

    if (SYS_Init() < 0)
    {
        while (1)
        {
        }
    }

    FMC->ISPCTL |= FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_APUEN_Msk | FMC_ISPCTL_CFGUEN_Msk | FMC_ISPCTL_ISPFF_Msk;

    SCB->VTOR = FMC_LDROM_BASE;

    UART0_WriteString("[boot]boot start\n");
#if 1
    u8AppValid = App_IsValid();
    if (u8AppValid != 0U)
    {
        UART0_WriteString("[boot]valid,quick jump\n");
        Boot_JumpToApplication();
    }
    /* APP invalid -> stay in boot and wait for CAN ISP commands. */
    UART0_WriteString("[boot]invalid,stay boot\n");
    CAN_Init();
#else
    {
        uint32_t u32WaitMs = 0U;

        CAN_Init();

        SysTick->LOAD = (SystemCoreClock / 1000UL) - 1UL;
        SysTick->VAL = 0UL;
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

        while (u32WaitMs < BOOT_WAIT_TIMEOUT_MS)
        {
            if (g_u8CANPacketReady != 0U)
                break;

            if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
                u32WaitMs++;
        }

        SysTick->CTRL = 0UL;

        if (g_u8CANPacketReady == 0U)
        {
            if (App_IsValid())
            {
                UART0_WriteString("[boot]valid,jump\n");
                Boot_JumpToApplication();
            }

            UART0_WriteString("[boot]invalid,stay boot\n");
            while (1)
            {
            }
        }
    }
#endif

    while (1)
    {
        if (g_u8CANPacketReady != 0U)
        {
            volatile STR_CANMSG_ISP_T *psISPCanMsg = (STR_CANMSG_ISP_T *)&g_sRxMsgFrame.au32Data[0];
            g_u8CANPacketReady = 0U;

#if BOOT_DEBUG_PRINT_CMD
            UART0_WriteString("[boot]cmd:");
            UART0_WriteHex32(psISPCanMsg->Address);
#endif

            if (psISPCanMsg->Address == CMD_GET_DEVICEID)
            {
                psISPCanMsg->Data = SYS->PDID;
#if BOOT_DEBUG_PRINT_CMD
                UART0_WriteString("h,id:");
                UART0_WriteHex32(psISPCanMsg->Data);
                UART0_WriteString("h\n");
#endif                
            }
            else if (psISPCanMsg->Address == CMD_READ_CONFIG)
            {
                psISPCanMsg->Data = FMC_Read(psISPCanMsg->Data);
#if BOOT_DEBUG_PRINT_CMD
                UART0_WriteString("h,cfg:");
                UART0_WriteHex32(psISPCanMsg->Data);
                UART0_WriteString("h\n");
#endif                
            }
            else if (psISPCanMsg->Address == CMD_RUN_APROM)
            {

#if BOOT_DEBUG_PRINT_CMD
                UART0_WriteString("h\n");
#endif

                if (App_IsValid())
                {
                    UART0_WriteString("[boot]valid,jump\n");
                    Boot_JumpToApplication();
                }

                continue;
            }
            else
            {
                if ((psISPCanMsg->Address >= APP_START_ADDR) && (psISPCanMsg->Address < APP_END_ADDR))
                {
                    if ((psISPCanMsg->Address % FMC_FLASH_PAGE_SIZE) == 0U)
                    {
                        FMC_Erase(psISPCanMsg->Address);
                    }

                    FMC_Write(psISPCanMsg->Address, psISPCanMsg->Data);
                    psISPCanMsg->Data = FMC_Read(psISPCanMsg->Address);
#if BOOT_DEBUG_PRINT_CMD
                    UART0_WriteString("h,read:");
                    UART0_WriteHex32(psISPCanMsg->Data);
                    UART0_WriteString("h\n");
#endif
                }
                else
                {
                    psISPCanMsg->Data = 0xFFFFFFFFUL;
                }
            }

            CAN_SendAck(psISPCanMsg);
        }
    }
}

void ProcessHardFault(void)
{
}

void SH_Return(void)
{
}

void SendChar_ToUART(int ch)
{
    (void)ch;
}
