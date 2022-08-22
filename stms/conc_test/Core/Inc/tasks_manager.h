/*
 * tasks_manager.h
 *
 *  Created on: Jun 29, 2022
 *      Author: marco
 */

#ifndef INC_TASKS_MANAGER_H_
#define INC_TASKS_MANAGER_H_

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"


void Start_UARTrx_tasks(void);

#endif /* INC_TASKS_MANAGER_H_ */
