/*******************************************************************************
* Title                 :   USB freertos Tasks
* Filename              :   USB_tasks.c
* Author                :   Marco Casado
* Origin Date           :   04/06/2021
* Version               :   1.0.0
* Compiler              :   ARM GCC
* Target                :   STM32F7
* Notes                 :   None
*
* THIS SOFTWARE IS PROVIDED BY RBA ENGINEERING "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL RBA ENGINEERING OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/
/*************** SOURCE REVISION LOG *****************************************
*
*    Date    Version   Author         Description
*  09/06/21   1.0.0   Marco Casado   Initial Release.
*  10/06/21   1.0.1   Marco Casado   Refactoring and formatting.
*******************************************************************************/
/** @file TODO: MODULE.c
 *  @brief This is the source file for TODO: WHAT DO I DO?
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "usb_tasks.h"

#include "usb_device.h"

/******************************************************************************
* Macro
*******************************************************************************/
/******************************************************************************
* Variables
*******************************************************************************/
TaskHandle_t cmdDataProc_xTaskHandle = NULL;
QueueHandle_t xCMDRxQueue;

extern TaskHandle_t dataJoiner_xTaskHandle;
extern TaskHandle_t scanChannels_xTaskHandle;
extern QueueHandle_t xSerialRxQueue;
extern TimerHandle_t xTimer;
extern void Error_Handler(void); /* Error Handler from main*/
/******************************************************************************
* Private Function Prototypes
*******************************************************************************/
static void vCmdDataProcessTask(void *params);
static void txBroadcast_startA3rs(void);
static void txBroadcast_stopSensorRd(void);
static void txBroadcast_getSensorID(void);
/******************************************************************************
* Public Function Definitions
*******************************************************************************/
/**
  * @brief
  * @param None
  * @retval None
  */
void Start_USB_cmd_tasks(void)
{

	int8_t cmdBuffer[3] = {0};
	const unsigned portBASE_TYPE  uxCmdLength = 50;
	xCMDRxQueue = xQueueCreate( uxCmdLength, sizeof( cmdBuffer ));

	xTaskCreate(vCmdDataProcessTask,
			"CmdDataProcessTask",
			configMINIMAL_STACK_SIZE,
			NULL,
			5,
			&cmdDataProc_xTaskHandle
			);

	if (cmdDataProc_xTaskHandle == NULL)
		Error_Handler();
}

/******************************************************************************
* Private Function Definitions
*******************************************************************************/
/**
  * @brief
  * @param void pointer unused
  * @retval None
  */
static void vCmdDataProcessTask(void *params)
{
	MX_USB_DEVICE_Init();
	txBroadcast_startA3rs();
	while(1)
	{
		uint8_t newCmd[3] = {0};
		xQueueReceive(xCMDRxQueue, (void*)&newCmd, portMAX_DELAY);
		switch(newCmd[0])
		{
		   case SET_PARAMS:
			   //txBroadcast_setParameters((uint8_t*)&newCmd[1]);
			   break;
		   case GET_ALL_SERIAL:
			   txBroadcast_getSensorID();
			   break;
		   case START_ALL_READ:
			   txBroadcast_startA3rs();
			   break;
		   case STOP_ALL_READ:
			   txBroadcast_stopSensorRd();
			   break;
		   case 0x0F:
			   break;
		}
	}
}

/**
  * @brief sends a broadcast stoping signal to all sensors and stops the sync pulse clock
  * @param 	None
  * @retval None
  */
static void txBroadcast_stopSensorRd(void)
{
	/*stop the sync clock*/
	xTimerStop(xTimer, 0);

	/* suspend A3RS Rx task*/
	vTaskSuspend(dataJoiner_xTaskHandle);

	/*clear all buffers related to A3RS acceleration data*/
    xQueueReset(xSerialRxQueue);
    //clearUSBtxBuffFromUARTtask();
}

/**
  * @brief  sends a broadcast signal asking all sensors ID
  * @param 	None
  * @retval None
  */
static void txBroadcast_getSensorID(void)
{
	/*disable timer!!!!*/
	xTimerStop(xTimer, 0);
	/*disable and clear acceleration data Rx*/
    xQueueReset(xSerialRxQueue);
    vTaskSuspend(dataJoiner_xTaskHandle);

	/*Clear uart Rx buffer*/
    xQueueReset(xSerialRxQueue);
    /* enable scan sensor task */
    vTaskResume(scanChannels_xTaskHandle);
}

/**
  * @brief  sends a broadcast staring signal to all sensors and starts the sync pulse clock
  * @param 	None
  * @retval None
  */
static void txBroadcast_startA3rs(void)
{
	/* disable and clear sensor scan Rx tasks*/
	vTaskSuspend(scanChannels_xTaskHandle );
    xQueueReset(xSerialRxQueue);
	/*give some time for the A3RS to prepare*/
	vTaskDelay(pdMS_TO_TICKS(500));

	/*start clock sync pulse*/
	xTimerStart(xTimer, 0);
	/*enable A3RS acceleration data read task */
	vTaskResume( dataJoiner_xTaskHandle );
}
/*************** END OF FUNCTIONS ***************************************************************************/
