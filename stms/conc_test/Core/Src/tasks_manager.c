/*
 * tasks_manager.c
 *
 *  Created on: Jun 29, 2022
 *      Author: marco
 */
#include "tasks_manager.h"
#include "main.h"
#include "cobs.h"
#include <stdio.h>
#include <string.h>
#include "ringBuffer.h"
#include "usbd_cdc_if.h"
#include "acc_data.h"
#include "AsciiTools.h"

//#define STRING_RES 1
extern CRC_HandleTypeDef hcrc;

ring_buffer_t  rbuff;
uint8_t dequeBuf[512];

#ifdef STRING_RES
const char *scr_range_strings[4]={ "NL","2G","4G","8G"};
//static const char *scr_freq_strings[7]={ "NL","4KHz","2KHz","1KHz","0.5KHz", "0.25K","0.125KHz"};
const char *cmd_tag[15]={ "NL","Freq=","Rang=","GblSN=","SnglSN=","LDStat=","RLstat=","ReadDat=","","","GblStp=","","","","ErrDat="}; //TODO separar y homologar!!!
const char *ch_tag[9]={"CH0#","CH1#","CH2#","CH3#","CH4#","CH5#","CH6#","CH7#","CH8#"};
const char *serials = "GblSN=CH0#A0:CH1#A10:CH2#A1:CH3#B4:CH4#A2:CH5#A3:CH6#A6:CH7#A7?\0";

#define USB_MAX_BUFF 	512u
char outMsgBuff[USB_MAX_BUFF*2] = "";
uint8_t ucDataJoinBuffNum;
#endif

typedef struct rxItRawMsg
{
	uint8_t msgId;
	uint8_t payload[14];	/* full frame buffer, [x3,x2,x1,y3,y2,y1,z3,z2,z1,t1,t2,CRC2,CRC1] and COBS 0 EOF*/
}rxItRawMsg_t;


//[x3,x2,x1,y3,y2,y1,z3,z2,z1,t1,t2,CRC2,CRC1]
/*
 typedef union {
	struct {

		uint8_t x_axis[3];
		uint8_t y_axis[3];
		uint8_t z_axis[3];
		uint8_t timestamp[2];
		uint8_t crc[2];

	} fr;

	struct {
		uint8_t payload[11];
		uint8_t crc[2];
	} b;
} frame_t
*/

typedef struct outputFrm {

	uint8_t type;
	uint8_t len;

	struct sd {
		uint8_t sensorId;
		uint8_t accData[11];
	} sensorPayload[8];

} outputFrm_t;


typedef union uFrame
{
    struct
    {
        uint8_t payload[11]; 	/* frame buffer without CRC value  */
        uint8_t crc[2];     	/* frame buffer only CRC values */
    }fr;

    struct
    {
        uint8_t payload[11];    /* 12-byte payload */
        uint8_t crc_h;  		/* 1-byte crc16-High check */
        uint8_t crc_l;  		/* 1-byte crc16-Low check */
    }b;

} rxMsgFrame_t;
/*
typedef struct sensorData {
	uint8_t sensorId;
	uint8_t accData[11];
} sensorData_t;

typedef struct outputFrm {
	uint8_t type;
	uint8_t len;
	sensorData_t sensorPayload[8];
} outputFrm_t;
*/
TaskHandle_t scanChannels_xTaskHandle  = NULL;
TaskHandle_t dataJoiner_xTaskHandle = NULL;
QueueHandle_t xSerialRxQueue;
TimerHandle_t xTimer;

static void vScanChannelsTask(void *params);
static void vAccDastaJoinerTask(void *params);
static void timerCB(TimerHandle_t xTimer);

void Start_UARTrx_tasks() {

	const unsigned portBASE_TYPE uxQueueLength = 120;
	xSerialRxQueue = xQueueCreate(uxQueueLength, sizeof(rxItRawMsg_t));

	xTimer = xTimerCreate ( "Timer",
					pdMS_TO_TICKS(2),
					pdTRUE,
					( void * ) 0,
					timerCB
              	  );
    if (xTimer == NULL) {
        /* The timer was not created. */
    	while(1);
    }
    else {
        //if( xTimerStart(xTimer, 0) != pdPASS) {
            /* The timer could not be set into the Active
            state. */
        //}
    }
	xTaskCreate(	vScanChannelsTask,
					"ScanChannelsTask",
					configMINIMAL_STACK_SIZE,
					NULL,
					1,	/*Priority*/
					&scanChannels_xTaskHandle  );

	xTaskCreate(	vAccDastaJoinerTask,
					"AccDataJoinerTask",
					configMINIMAL_STACK_SIZE*15,
					NULL,
					1,	/*Priority*/
					&dataJoiner_xTaskHandle );

	vTaskSuspend(dataJoiner_xTaskHandle);
	vTaskSuspend(scanChannels_xTaskHandle);
}


int16_t size_acc = sizeof(acc_data) / sizeof(acc_data[0]) - 1;

static void timerCB (TimerHandle_t xTimer) {
	static rxItRawMsg_t x = {};
	static uint16_t cnt = 0;

	memcpy(&x.payload, &acc_data[cnt], sizeof(x.payload));
	cnt = (cnt >= size_acc) ? 0 : (cnt + 1);

	for (uint8_t i = 0; i < 8; ++i) {
		x.msgId = i;
		xQueueSend(xSerialRxQueue, (void*)&x,0);
	}
}

static void vScanChannelsTask (void *params) {

	for(;;) {
		//CDC_Transmit_FS((uint8_t*)serials, strlen(serials));
		vTaskSuspend(NULL);
		//HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
		//vTaskDelay(500);
		//taskYIELD();
	}
}

static void vAccDastaJoinerTask (void *params) {
	ring_buffer_init(&rbuff);
	rxItRawMsg_t  rxMsg = {0}; /*rx msg*/
	outputFrm_t oFrame;
	uint8_t i = 0;
	uint16_t cnt = 0;

	for (;;) {
		if (xQueueReceive(xSerialRxQueue, &(rxMsg), portMAX_DELAY)) {
 			rxMsgFrame_t dcdRxMsg = {0};
 			COBS_deCode(rxMsg.payload, sizeof(rxMsg.payload), (void*)&dcdRxMsg);
			uint16_t crc_hal  = (uint16_t)HAL_CRC_Calculate(&hcrc, (uint32_t*)&dcdRxMsg.fr.payload, sizeof(dcdRxMsg.fr.payload));

			if (crc_hal == (dcdRxMsg.b.crc_h << 8 | dcdRxMsg.b.crc_l)) {
#ifdef STRING_RES
					if (ucDataJoinBuffNum == 0x00) {
						strcpy(outMsgBuff, "ReadDat=");					/* add cmd tag at the begining of the string */
					}
					strcat(outMsgBuff, ch_tag[rxMsg.msgId]);		/* add channel tag */
			 		char hex2AsciiBuff[USB_MAX_BUFF*2];
						/*NOTA 1 La simulación no alcanza a hacer el overflow de 16bits y reinicia en cero, entonces modifico el payload para
						 * generar el counter localmente y generar continuidad/overflow */
						dcdRxMsg.fr.payload[9] =  0xff & cnt >> 8;
						dcdRxMsg.fr.payload[10] = 0xff & cnt;
						if (rxMsg.msgId == 0) {
							cnt++;
						}
						/* END NOTA 1*/
					hex2asc((void*)&dcdRxMsg.fr.payload[0], 22, 2, hex2AsciiBuff);
					strcat(hex2AsciiBuff, "|");
					strcat(outMsgBuff, hex2AsciiBuff);					/* add payload */
					ucDataJoinBuffNum++;
					if (ucDataJoinBuffNum > 16 && strlen(outMsgBuff) < USB_MAX_BUFF) {
						strcat(outMsgBuff,"?");
						taskENTER_CRITICAL();
						CDC_Transmit_FS((uint8_t*)&outMsgBuff[0], strlen(outMsgBuff));
						taskEXIT_CRITICAL();
						ucDataJoinBuffNum = 0x00;
					}
#else

				dcdRxMsg.fr.payload[9] =  0xff & cnt >> 8;
				dcdRxMsg.fr.payload[10] = 0xff & cnt;
				if (rxMsg.msgId == 0) {
					cnt++;
				}
				oFrame.sensorPayload[i].sensorId = rxMsg.msgId;
				memcpy(&oFrame.sensorPayload[i].accData, (void*)&dcdRxMsg.fr.payload[0], sizeof(dcdRxMsg.fr.payload));
				i++;
				if (i >= 8 ) {
					i = 0;
					oFrame.type = 1;
					oFrame.len = sizeof(outputFrm_t);
					uint8_t dest_cbs[sizeof(outputFrm_t) + 2] = {0};
					COBS_enCode((uint8_t*)&oFrame, sizeof(outputFrm_t), dest_cbs);
					memset(&oFrame, 0,sizeof(oFrame));
					if (!ring_buffer_is_full(&rbuff)) {
						ring_buffer_queue_arr(&rbuff, dest_cbs, sizeof(dest_cbs));
					}
					if(ring_buffer_num_items(&rbuff) >= sizeof(dequeBuf)) {
						ring_buffer_dequeue_arr(&rbuff, dequeBuf, sizeof(dequeBuf));
						CDC_Transmit_FS((uint8_t*)&dequeBuf[0], sizeof(dequeBuf));
					}
				}
#endif
			}
		}
		taskYIELD();
	}
}

/**
  * @brief
  * @param
  * @param
  * @retval
  */
void clearUSBtxBuffFromUARTtask(void)			//TODO: destruir y crear datajoiner task para no usar este horrible metodo de limpiar buffers
{
	//memset(outMsgBuff, 0, sizeof(outMsgBuff));
	//ucDataJoinBuffNum = 0u;
}
