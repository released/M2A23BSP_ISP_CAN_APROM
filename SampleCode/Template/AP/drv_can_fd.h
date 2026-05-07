#ifndef __DRV_CAN_FD_H__
#define __DRV_CAN_FD_H__

/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "NuMicro.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*  
	template
	typedef struct _peripheral_manager_t
	{
		uint16_t* pu16Far;
		uint8_t u8Cmd;
		uint8_t au8Buf[33];
		uint8_t u8RecCnt;
		uint8_t bByPass;
	}PERIPHERAL_MANAGER_T;

	volatile PERIPHERAL_MANAGER_T g_PeripheralManager = 
	{
		.pu16Far = NULL,	//.pu16Far = 0	
		.u8Cmd = 0,
		.au8Buf = {0},		//.au8Buf = {100U, 200U},
		.u8RecCnt = 0,
		.bByPass = FALSE,
	};
	extern volatile PERIPHERAL_MANAGER_T g_PeripheralManager;
*/

#define CANFD_MODULE       0

// #define ENABLE_MONITOR_MODE

/*
 * Test profile:
 * 0: Classical CAN only (FD frame TX will be blocked)
 * 1: CAN FD mode (can send both CAN and CAN FD frames)
 */
#define CAN_APP_ENABLE_FD_MODE        (1U)
#define CAN_APP_FD_NON_ISO_MODE       (0U)   /* 0: ISO CAN FD, 1: Non-ISO CAN FD */
#define CAN_APP_NOMINAL_BITRATE       (500000U)
#define CAN_APP_DATA_BITRATE          (2000000U)
/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/
extern CANFD_FD_MSG_T g_sRxMsgFrame;
extern CANFD_FD_MSG_T g_sTxMsgFrame;
extern volatile uint32_t g_u32CanIrqStatus;

extern uint8_t num_cnt;

void CAN_Rx_process(void);
void CAN_SendMessage(uint8_t en_can_fd, CANFD_FD_MSG_T *psTxMsg, E_CANFD_ID_TYPE eIdType, uint32_t u32Id, uint8_t u8Len);
void CAN_Init(void);

#endif //__DRV_CAN_FD_H__
