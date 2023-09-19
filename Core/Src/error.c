/*
 * error.c
 *
 *  Created on: Sep 12, 2023
 *      Author: jvincent
 */

#include "FreeRTOS.h"
#include "task.h"

void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{
	while(1)
	{
		continue;
	}
}
