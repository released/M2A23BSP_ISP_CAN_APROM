/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "memory_map.h"

#include "misc_config.h"

#include "timer_service.h"
#include "drv_can_fd.h"
/*_____ D E C L A R A T I O N S ____________________________________________*/

volatile struct flag_32bit flag_PROJ_CTL;
#define FLAG_PROJ_TIMER_PERIOD_1000MS                 	(flag_PROJ_CTL.bit0)
#define FLAG_PROJ_ERASE_CHECKSUM                        (flag_PROJ_CTL.bit1)
#define FLAG_PROJ_STANDBY_REQUEST                       (flag_PROJ_CTL.bit2)
#define FLAG_PROJ_SEND_CAN_1                            (flag_PROJ_CTL.bit3)
#define FLAG_PROJ_SEND_CAN_2                            (flag_PROJ_CTL.bit4)
#define FLAG_PROJ_REVERSE5                              (flag_PROJ_CTL.bit5)
#define FLAG_PROJ_REVERSE6                              (flag_PROJ_CTL.bit6)
#define FLAG_PROJ_REVERSE7                              (flag_PROJ_CTL.bit7)


/*_____ D E F I N I T I O N S ______________________________________________*/

volatile unsigned long counter_systick = 0;
volatile uint32_t counter_tick = 0;

// timer task
static int g_timer_id_task1 = -1;
static int g_timer_id_task2 = -1;
static int g_timer_id_task3 = -1;

#define PWM_GROUP_NUM                                   (3U)
#define PWM_FREQ_MIN_HZ                                 (100U)
#define PWM_FREQ_MAX_HZ                                 (500U)
#define PWM_FREQ_STEP_HZ                                (10U)
#define PWM_DUTY_MIN                                    (0U)
#define PWM_DUTY_MAX                                    (100U)
#define PWM_DUTY_STEP                                   (1U)
#define PWM_CTRL_SEL_MAX                                (PWM_GROUP_NUM * 2U)

static const uint8_t g_au8PwmChannel[PWM_GROUP_NUM] = {0U, 2U, 4U};
static uint16_t g_au16PwmFreq[PWM_GROUP_NUM] = {100U, 100U, 100U};
static uint8_t  g_au8PwmDuty[PWM_GROUP_NUM] = {50U, 50U, 50U};
static uint8_t  g_u8PwmCtrlSel = 0U;

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

unsigned long get_systick(void)
{
	return (counter_systick);
}

void set_systick(unsigned long t)
{
	counter_systick = t;
}

void systick_counter(void)
{
	counter_systick++;
}

void SysTick_Handler(void)
{
    systick_counter();

    #if defined (ENABLE_TICK_EVENT)
    TickCheckTickEvent();
    #endif
}

void SysTick_delay(unsigned long delay)
{  
    
    unsigned long tickstart = get_systick(); 
    unsigned long wait = delay; 

    while((get_systick() - tickstart) < wait) 
    { 
    } 

}

void SysTick_enable(unsigned long ticks_per_second)
{
    set_systick(0);
    if (SysTick_Config(SystemCoreClock / ticks_per_second))
    {
        /* Setup SysTick Timer for 1 second interrupts  */
        printf("Set system tick error!!\n");
        while (1);
    }

    #if defined (ENABLE_TICK_EVENT)
    TickInitTickEvent();
    #endif
}

uint32_t get_tick(void)
{
	return (counter_tick);
}

void set_tick(uint32_t t)
{
	counter_tick = t;
}

void tick_counter(void)
{
	counter_tick++;
}

void delay_ms(uint16_t ms)
{
	#if 1
	uint32_t start = get_tick();
    while ((uint32_t)(get_tick() - start) < (uint32_t)ms) 
	{
		
	}	
	#else
	TIMER_Delay(TIMER0, 1000*ms);
	#endif
}

void Task_1000ms_Callback(void *user_data)
{
	static uint32_t LOG1 = 0;

    num_cnt += 0x10;
    // CAN_SendMessage(TRUE, &g_sTxMsgFrame, eCANFD_SID, 0x111, 8);
    // CAN_SendMessage(TRUE, &g_sTxMsgFrame, eCANFD_XID, 0x2222, 8);

    // printf("4444-%s(timer) : %4d\r\n",__FUNCTION__,LOG1++);
    PF14 ^= 1; 
}

void Task_100ms_Callback(void *user_data)
{

}

void Task_10ms_Callback(void *user_data)
{

}

void TimerService_CreateTask(void)
{
    /* Create task1 timer: 10 ms */
    g_timer_id_task1 = TimerService_CreateTimer(10U, Task_10ms_Callback, (void *)0);

    /* Start timers */
    if (g_timer_id_task1 >= 0)
    {
        TimerService_StartTimer((unsigned int)g_timer_id_task1);
        printf("task1 id = %d\r\n", g_timer_id_task1);
    }

    /* Create task2 timer: 100 ms */
    g_timer_id_task2 = TimerService_CreateTimer(100U, Task_100ms_Callback, (void *)0);

    /* Start timers */
    if (g_timer_id_task2 >= 0)
    {
        TimerService_StartTimer((unsigned int)g_timer_id_task2);
        printf("task2 id = %d\r\n", g_timer_id_task2);
    }

    /* Create task3 timer: 1000 ms */
    g_timer_id_task3 = TimerService_CreateTimer(1000U, Task_1000ms_Callback, (void *)0);

    /* Start timers */
    if (g_timer_id_task3 >= 0)
    {
        TimerService_StartTimer((unsigned int)g_timer_id_task3);
        printf("task3 id = %d\r\n", g_timer_id_task3);
    }
}

static void FMC_ISP_Program(uint32_t u32Cmd, uint32_t u32Addr, uint32_t u32Data)
{
    uint32_t u32TimeOutCnt;

    FMC_ENABLE_AP_UPDATE();
    FMC->ISPCMD = u32Cmd;
    FMC->ISPADDR = u32Addr;
    FMC->ISPDAT = u32Data;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
    __ISB();

    u32TimeOutCnt = FMC_TIMEOUT_READ;
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk)
    {
        if (--u32TimeOutCnt == 0U)
        {
            while (1)
            {
            }
        }
    }
}

static void APP_InvalidateChecksumAndReset(void)
{
    uint32_t u32TimeOutCnt;

    printf("erase APP checksum at 0x%08lX\r\n", APP_CHECKSUM_ADDR);

    SYS_UnlockReg();
    FMC_Open();
    FMC_ENABLE_AP_UPDATE();

    if ((APP_CHECKSUM_ADDR & (FMC_FLASH_PAGE_SIZE - 1U)) == 0U)
    {
        FMC_ISP_Program(FMC_ISPCMD_PAGE_ERASE, APP_CHECKSUM_ADDR, 0U);
    }

    FMC_ISP_Program(FMC_ISPCMD_PROGRAM, APP_CHECKSUM_ADDR, 0x00000000U);
    printf("Checksum now: 0x%08X\r\n", FMC_Read(APP_CHECKSUM_ADDR));

    u32TimeOutCnt = SystemCoreClock;
    while (!UART_IS_TX_EMPTY(UART0))
    {
        if (--u32TimeOutCnt == 0U)
        {
            break;
        }
    }

    __set_PRIMASK(1);
    FMC_SetVectorPageAddr(FMC_APROM_BASE);
    FMC_SET_APROM_BOOT();
    SYS_ResetChip();
}

//
// check_reset_source
//
uint8_t check_reset_source(void)
{
    uint32_t src = SYS_GetResetSrc();

    SYS->RSTSTS |= 0x1FF;
    printf("Reset Source <0x%08X>\r\n", src);

    #if 1   //DEBUG , list reset source
    if (src & BIT0)
    {
        printf("0)POR Reset Flag\r\n");       
    }
    if (src & BIT1)
    {
        printf("1)NRESET Pin Reset Flag\r\n");       
    }
    if (src & BIT2)
    {
        printf("2)WDT Reset Flag\r\n");       
    }
    if (src & BIT3)
    {
        printf("3)LVR Reset Flag\r\n");       
    }
    if (src & BIT4)
    {
        printf("4)BOD Reset Flag\r\n");       
    }
    if (src & BIT5)
    {
        printf("5)System Reset Flag \r\n");       
    }
    if (src & BIT6)
    {
        printf("6)Reserved.\r\n");       
    }
    if (src & BIT7)
    {
        printf("7)CPU Reset Flag\r\n");       
    }
    if (src & BIT8)
    {
        printf("8)CPU Lockup Reset Flag\r\n");       
    }
    #endif
    
    if (src & SYS_RSTSTS_PORF_Msk) {
        SYS_ClearResetSrc(SYS_RSTSTS_PORF_Msk);
        
        printf("power on from POR\r\n");
        return FALSE;
    }    
    else if (src & SYS_RSTSTS_PINRF_Msk)
    {
        SYS_ClearResetSrc(SYS_RSTSTS_PINRF_Msk);
        
        printf("power on from nRESET pin\r\n");
        return FALSE;
    } 
    else if (src & SYS_RSTSTS_WDTRF_Msk)
    {
        SYS_ClearResetSrc(SYS_RSTSTS_WDTRF_Msk);
        
        printf("power on from WDT Reset\r\n");
        return FALSE;
    }    
    else if (src & SYS_RSTSTS_LVRF_Msk)
    {
        SYS_ClearResetSrc(SYS_RSTSTS_LVRF_Msk);
        
        printf("power on from LVR Reset\r\n");
        return FALSE;
    }    
    else if (src & SYS_RSTSTS_BODRF_Msk)
    {
        SYS_ClearResetSrc(SYS_RSTSTS_BODRF_Msk);
        
        printf("power on from BOD Reset\r\n");
        return FALSE;
    }    
    else if (src & SYS_RSTSTS_SYSRF_Msk)
    {
        SYS_ClearResetSrc(SYS_RSTSTS_SYSRF_Msk);
        
        printf("power on from System Reset\r\n");
        return FALSE;
    } 
    else if (src & SYS_RSTSTS_CPURF_Msk)
    {
        SYS_ClearResetSrc(SYS_RSTSTS_CPURF_Msk);

        printf("power on from CPU reset\r\n");
        return FALSE;         
    }    
    else if (src & SYS_RSTSTS_CPULKRF_Msk)
    {
        SYS_ClearResetSrc(SYS_RSTSTS_CPULKRF_Msk);
        
        printf("power on from CPU Lockup Reset\r\n");
        return FALSE;
    }   
    
    printf("power on from unhandle reset source\r\n");
    return FALSE;
}

void TMR1_IRQHandler(void)
{
	
    if(TIMER_GetIntFlag(TIMER1) == 1)
    {
        TIMER_ClearIntFlag(TIMER1);
        tick_counter();
        TimerService_Tick1ms();
    }
}

void TIMER1_Init(void)
{
    TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 1000);
    TIMER_EnableInt(TIMER1);
    NVIC_EnableIRQ(TMR1_IRQn);	
    TIMER_Start(TIMER1);
}

static void PWM_ApplyChannel(uint8_t u8Index)
{
    if (u8Index >= PWM_GROUP_NUM)
    {
        return;
    }

    PWM_ConfigOutputChannel(PWM0,
                            g_au8PwmChannel[u8Index],
                            g_au16PwmFreq[u8Index],
                            g_au8PwmDuty[u8Index]);
}

static void PWM_PrintStatus(void)
{
    uint8_t i;
    uint8_t u8Grp = (g_u8PwmCtrlSel / 2U) + 1U;
    const char *pcMode = ((g_u8PwmCtrlSel & 0x1U) == 0U) ? "FREQ" : "DUTY";

    printf("PWM CTRL = Group%u %s\r\n", u8Grp, pcMode);
    for (i = 0U; i < PWM_GROUP_NUM; i++)
    {
        printf("PWM%u(ch%u): %u Hz, %u %%\r\n",
               i + 1U,
               g_au8PwmChannel[i],
               g_au16PwmFreq[i],
               g_au8PwmDuty[i]);
    }
}

static void PWM_SelectControl(uint8_t u8Sel)
{
    if (u8Sel >= PWM_CTRL_SEL_MAX)
    {
        return;
    }

    g_u8PwmCtrlSel = u8Sel;
    PWM_PrintStatus();
}

static void PWM_AdjustSelected(int8_t i8Direction)
{
    uint8_t u8Group = g_u8PwmCtrlSel / 2U;
    uint8_t u8IsFreqCtrl = ((g_u8PwmCtrlSel & 0x1U) == 0U) ? 1U : 0U;
    int32_t i32Temp;

    if ((u8Group >= PWM_GROUP_NUM) || (i8Direction == 0))
    {
        return;
    }

    if (u8IsFreqCtrl)
    {
        i32Temp = (int32_t)g_au16PwmFreq[u8Group] + ((int32_t)PWM_FREQ_STEP_HZ * (int32_t)i8Direction);

        if (i32Temp < (int32_t)PWM_FREQ_MIN_HZ)
        {
            i32Temp = (int32_t)PWM_FREQ_MIN_HZ;
        }
        if (i32Temp > (int32_t)PWM_FREQ_MAX_HZ)
        {
            i32Temp = (int32_t)PWM_FREQ_MAX_HZ;
        }

        g_au16PwmFreq[u8Group] = (uint16_t)i32Temp;
    }
    else
    {
        i32Temp = (int32_t)g_au8PwmDuty[u8Group] + ((int32_t)PWM_DUTY_STEP * (int32_t)i8Direction);

        if (i32Temp < (int32_t)PWM_DUTY_MIN)
        {
            i32Temp = (int32_t)PWM_DUTY_MIN;
        }
        if (i32Temp > (int32_t)PWM_DUTY_MAX)
        {
            i32Temp = (int32_t)PWM_DUTY_MAX;
        }

        g_au8PwmDuty[u8Group] = (uint8_t)i32Temp;
    }

    PWM_ApplyChannel(u8Group);
    PWM_PrintStatus();
}

static void PWM_InitChannels(void)
{
    uint8_t i;
    uint32_t u32Mask = 0U;

    for (i = 0U; i < PWM_GROUP_NUM; i++)
    {
        PWM_ApplyChannel(i);
        u32Mask |= (1UL << g_au8PwmChannel[i]);
    }

    PWM_EnableOutput(PWM0, u32Mask);
    PWM_Start(PWM0, u32Mask);
    PWM_PrintStatus();
}

static void APP_StandbyWaitCanWake(void)
{
    uint32_t u32TimeOutCnt;
    uint32_t u32SysTickCtrl = SysTick->CTRL;
    uint32_t u32UartIntEn = UART0->INTEN;

    printf("Enter standby (CPU sleep). Wake-up source: CAN RX IRQ\r\n");
    u32TimeOutCnt = SystemCoreClock;
    while (!UART_IS_TX_EMPTY(UART0))
    {
        if (--u32TimeOutCnt == 0U)
        {
            break;
        }
    }

    TIMER_DisableInt(TIMER1);
    TIMER_Stop(TIMER1);
    NVIC_DisableIRQ(TMR1_IRQn);
    UART_DisableInt(UART0, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk);
    NVIC_DisableIRQ(UART0_IRQn);

    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk);

    g_u32CanIrqStatus = 0U;
    while (g_u32CanIrqStatus == 0U)
    {
        __WFI();
    }

    SysTick->CTRL = u32SysTickCtrl;
    UART0->INTEN = u32UartIntEn;
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_EnableIRQ(TMR1_IRQn);
    TIMER_EnableInt(TIMER1);
    TIMER_Start(TIMER1);

    printf("Wake-up by CAN activity\r\n");
}

void loop(void)
{
    // timer service
    TimerService_Dispatch();

    CAN_Rx_process();

    if (FLAG_PROJ_ERASE_CHECKSUM)
    {
        FLAG_PROJ_ERASE_CHECKSUM = 0;
        APP_InvalidateChecksumAndReset();
    }

    if (FLAG_PROJ_STANDBY_REQUEST)
    {
        FLAG_PROJ_STANDBY_REQUEST = 0;
        APP_StandbyWaitCanWake();
    }

    if (FLAG_PROJ_SEND_CAN_1)
    {
        FLAG_PROJ_SEND_CAN_1 = 0;
        CAN_SendMessage(TRUE, &g_sTxMsgFrame, eCANFD_SID, 0x333, 16);
    }

    if (FLAG_PROJ_SEND_CAN_2)
    {
        FLAG_PROJ_SEND_CAN_2 = 0;
        CAN_SendMessage(TRUE, &g_sTxMsgFrame, eCANFD_XID, 0x4444, 32);
    }
}

void UARTx_Process(void)
{
	uint8_t res = 0;
	res = UART_READ(UART0);

	if (res > 0x7F)
	{
		printf("invalid command\r\n");
	}
	else
	{
		printf("press : %c\r\n" , res);
		switch(res)
		{
			case '1':
                PWM_SelectControl(0U);
				break;
			case '2':
                PWM_SelectControl(1U);
                break;
			case '3':
                PWM_SelectControl(2U);
                break;
			case '4':
                PWM_SelectControl(3U);
                break;
            case '5':
                PWM_SelectControl(4U);
                break;
            case '6':
                PWM_SelectControl(5U);
                break;
            case 'A':
            case 'a':
                PWM_AdjustSelected(1);
                break;
            case 'D':
            case 'd':
                PWM_AdjustSelected(-1);
                break;
            case '7':
                FLAG_PROJ_STANDBY_REQUEST = 1;
                break;

            case '8':
                FLAG_PROJ_SEND_CAN_1 = 1;
                break;
            case '9':
                FLAG_PROJ_SEND_CAN_2 = 1;
                break;                

            case 'E':
            case 'e':
                FLAG_PROJ_ERASE_CHECKSUM = 1;
                break;

			case 'X':
			case 'x':
			case 'Z':
			case 'z':
                SYS_UnlockReg();
				// NVIC_SystemReset();	// Reset I/O and peripherals , only check BS(FMC_ISPCTL[1])
                // SYS_ResetCPU();     // Not reset I/O and peripherals
                SYS_ResetChip();    // Reset I/O and peripherals ,  BS(FMC_ISPCTL[1]) reload from CONFIG setting (CBS)	
				break;
		}
	}
}

void UART0_IRQHandler(void)
{
    if(UART_GET_INT_FLAG(UART0, UART_INTSTS_RDAINT_Msk | UART_INTSTS_RXTOINT_Msk))     /* UART receive data available flag */
    {
        while(UART_GET_RX_EMPTY(UART0) == 0)
        {
            UARTx_Process();
        }
    }

    if(UART0->FIFOSTS & (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk | UART_FIFOSTS_RXOVIF_Msk))
    {
        UART_ClearIntFlag(UART0, (UART_INTSTS_RLSINT_Msk| UART_INTSTS_BUFERRINT_Msk));
    }	
}

void UART0_Init(void)
{
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
    UART_EnableInt(UART0, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk);
    NVIC_EnableIRQ(UART0_IRQn);
	
	#if (_debug_log_UART_ == 1)	//debug
	printf("\r\nCLK_GetCPUFreq : %8d\r\n",CLK_GetCPUFreq());
	printf("CLK_GetHCLKFreq : %8d\r\n",CLK_GetHCLKFreq());
	printf("CLK_GetHXTFreq : %8d\r\n",CLK_GetHXTFreq());
	printf("CLK_GetLXTFreq : %8d\r\n",CLK_GetLXTFreq());	
	printf("CLK_GetPCLK0Freq : %8d\r\n",CLK_GetPCLK0Freq());
	printf("CLK_GetPCLK1Freq : %8d\r\n",CLK_GetPCLK1Freq());	
	#endif	

    #if 0
    printf("FLAG_PROJ_TIMER_PERIOD_1000MS : 0x%2X\r\n",FLAG_PROJ_TIMER_PERIOD_1000MS);
    printf("FLAG_PROJ_ERASE_CHECKSUM : 0x%2X\r\n",FLAG_PROJ_ERASE_CHECKSUM);
    printf("FLAG_PROJ_STANDBY_REQUEST : 0x%2X\r\n",FLAG_PROJ_STANDBY_REQUEST);
    #endif

}

void GPIO_Init (void)
{
    SET_GPIO_PF14();
	// EVM LED_R
    GPIO_SetMode(PF, BIT14, GPIO_MODE_OUTPUT);	

    // PC3_CAN_MODE , SET AS LOW
    SET_GPIO_PC3();
    PC3 = 0;
    GPIO_SetMode(PC, BIT3, GPIO_MODE_OUTPUT);	    

}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);
    
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

//	CLK_EnableXtalRC(CLK_PWRCTL_LIRCEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);	

//	CLK_EnableXtalRC(CLK_PWRCTL_LXTEN_Msk);
//    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);	

    /* Set core clock to 72MHz */
    CLK_SetCoreClock(72000000);

    /* Select HCLK clock source as HIRC and HCLK source divider as 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    CLK_EnableModuleClock(UART0_MODULE);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL2_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    // CLK_EnableModuleClock(TMR0_MODULE);
  	// CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, 0);

    CLK_EnableModuleClock(TMR1_MODULE);
  	CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HIRC, 0);

    CLK_EnableModuleClock(PWM0_MODULE);
    CLK_SetModuleClock(PWM0_MODULE, CLK_CLKSEL3_PWM0SEL_PCLK0, 0);
	
    SET_UART0_RXD_PB12();
    SET_UART0_TXD_PB13();
    SET_PWM0_CH0_PB5();
    SET_PWM0_CH2_PB3();
    SET_PWM0_CH4_PB1();

    /* Use PLL/2 clock for CAN FD timing (supports 500k/2M profile) */
    CLK_SetModuleClock(CANFD0_MODULE, CLK_CLKSEL0_CANFD0SEL_PLL_DIV2, CLK_CLKDIV1_CANFD0(1));

    /* Enable CAN FD0 peripheral clock */
    CLK_EnableModuleClock(CANFD0_MODULE);
    
    SET_CANFD0_RXD_PC4();
    SET_CANFD0_TXD_PC5();

   /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Lock protected registers */
    SYS_LockReg();
}

int main()
{
    SYS_Init();

	GPIO_Init();
	UART0_Init();
	TIMER1_Init();
    check_reset_source();

    SysTick_enable(1000);
    #if defined (ENABLE_TICK_EVENT)
    TickSetTickEvent(1000, TickCallback_processA);  // 1000 ms
    TickSetTickEvent(5000, TickCallback_processB);  // 5000 ms
    #endif

    /*
        PC3_CAN_MODE , SET AS LOW (actually M2A23 EVB , R18 already fix to pull low)
        PC4_CANFD0_RXD
        PC5_CANFD0_TXD
    */
    CAN_Init();
    PWM_InitChannels();
    printf("UART key map:\r\n");
    printf("1/2: PWM1 FREQ/DUTY, 3/4: PWM2 FREQ/DUTY, 5/6: PWM3 FREQ/DUTY\r\n");
    printf("A/a: increment selected item, D/d: decrement selected item\r\n");
    printf("7: standby until CAN RX wake-up\r\n");
    printf("8: send CAN message:0x333, 16 bytes\r\n");
    printf("9: send CAN message:0x444, 32 bytes\r\n");
    printf("E/e: invalidate APP checksum + reset\r\n");
    
    TimerService_Init();    
    TimerService_CreateTask();

    /* Got no where to go, just loop forever */
    while(1)
    {
        loop();

    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
