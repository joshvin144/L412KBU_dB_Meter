/*
 * system_task.c
 *
 *  Created on: May 18, 2023
 *      Author: jvincent
 */

/* BEGIN INCLUDES */
#include "stm32l4xx_hal.h"
#include "FreeRTOS.h"
#include "task_definitions.h"
#include "stdbool.h"
#include "assert.h"
/* END INCLUDES */

/* BEGIN SYSTEM SPECIFIC DEFINITIONS */
#define HEARTBEAT_HALF_PERIOD_MS 500
/* END SYSTEM TASK SPECIFIC DEFINITIONS */

/* TASK DEFINITIONS BEGIN */
void vSystemTask(void* pvParams)
{
	/* Note that the following segment of code is run while starting up the task, only */

	/* Create any mutexes, semaphores, gueues, or other intertask communication mechanisms, here */

	/* Write task specific code, here */

	/* Note that the following segment consists of code that the RTOS cycles through. */

	for(;;)
	{
		/* Write application specific code, here */

		// Heartbeat LED
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		HAL_Delay(HEARTBEAT_HALF_PERIOD_MS);
	}

	vTaskDelete(NULL);
}
/* TASK DEFINITIONS END */

/* BEGIN TASK BLOCKS */
void initialize_system_task_block(void)
{
	system_task_block.p_task_function = vSystemTask;
	system_task_block.task_name = system_task_name;
	system_task_block.stack_depth = SYSTEM_TASK_STACK_SIZE;
	system_task_block.p_params = p_system_params;
	system_task_block.priority = SYSTEM_TASK_PRIORITY;
	system_task_block.p_stack_buffer = system_stack_buffer;
	system_task_block.p_task_buffer = &system_task_buffer;
}
/* END TASK BLOCKS */

/* BEGIN TASK CREATION */

void create_system_task(void)
{
	initialize_system_task_block();
	systemTaskHandle = xTaskCreateStatic(system_task_block.p_task_function,
			  system_task_block.task_name,
			  system_task_block.stack_depth,
			  system_task_block.p_params,
			  system_task_block.priority,
			  system_task_block.p_stack_buffer,
			  system_task_block.p_task_buffer);
}

/* END TASK CREATION */
