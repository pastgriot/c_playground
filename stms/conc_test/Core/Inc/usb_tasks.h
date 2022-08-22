/*******************************************************************************
* Title                 :   USB commands header
* Filename              :   USB_cmd.h
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
*  10/06/21   1.0.0   Marco Casado   Refactoring and formatting.
*******************************************************************************/
/** @file TODO: MODULE.c
 *  @brief This is the source file for TODO: WHAT DO I DO?
 */
#ifndef INC_USB_TASKS_H_
#define INC_USB_TASKS_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "stm32f7xx_hal.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define     SET_PARAMS              0x01
#define     GET_ALL_SERIAL          0x03
#define     GET_SNGL_SERIAL         0x04
#define     START_ALL_READ          0x05
#define     SET_SNGL_ENABLE         0x06
#define     SET_SNGL_DISABLE        0x07
#define     GET_ALL_ENABLE          0x08
#define     STOP_ALL_READ           0x0E
#define     SET_LED                 0x0B
#define     SET_RELAY               0x0C
#define     GET_LED                 0x0D
#define     STOP_FIRST              0x0F
#define     REPEAT_DATA             0x10

#define    RANGE_2G                 0x01
#define    RANGE_4G                 0x02
#define    RANGE_8G                 0x03

#define    FREQ_4000                0x01
#define    FREQ_2000                0x02
#define    FREQ_1000                0x03
#define    FREQ_500                 0x04
#define    FREQ_250                 0x05
#define    FREQ_125                 0x06
#define    USB_FAIL                 0x00u
#define	   SAMPLE_500HZ				12800000ULL
#define	   SAMPLE_1000HZ			25600000ULL

#define GLOBAL_ID 0xFF      /* broadcast ID*/
/******************************************************************************
* Extern Definitions
*******************************************************************************/


/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void clearUSBtxBuffFromUARTtask(void);
void Start_USB_cmd_tasks(void);
#endif /*INC_CMD_IF_H_*/


