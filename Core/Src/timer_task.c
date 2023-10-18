/*
 * timer_task.c
 *
 *  Created on: Oct 17, 2023
 *      Author: jvincent
 */

#include "FreeRTOS.h"
#include "timer_task.h"
#include "stm32l4xx_hal.h"

/* BEGIN TASK NAMES */
char* const timer_name = "TIMER TASK";
/* END TASK NAMES */

/* BEGIN TIMER PERIOD */
TickType_t timer_period = pdMS_TO_TICKS(TIMER_PERIOD_MS);
/* END TIMER PERIOD */

/* BEGIN AUTO-RELOAD */
UBaseType_t auto_reload = pdTRUE;
/* END AUTO-RELOAD */

/* BEGIN TASK HANDLE DECLARATIONS */
TimerHandle_t timerTaskHandle = NULL;
/* END TASK HANDLE DECLARATIONS */

StaticTimer_t timer_buffer;

timer_block_t timer_task;

void vTimerCallback(TimerHandle_t xTimerHandle)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
}

void init_timer_task_block(void)
{
	timer_task.timer_name = timer_name;
	timer_task.timer_period = TIMER_PERIOD_MS;
	timer_task.auto_reload = auto_reload;
	timer_task.p_timer_ID = (void*) 0;
	timer_task.p_timer_buffer = &timer_buffer;
}

void create_timer_task(void)
{
	init_timer_task_block();
	timerTaskHandle = xTimerCreateStatic(timer_task.timer_name,
			                             timer_task.timer_period,
								         timer_task.auto_reload,
										 timer_task.p_timer_ID,
								         vTimerCallback,
								         timer_task.p_timer_buffer);
}

void start_timer_task(void)
{
	xTimerStart(timerTaskHandle, 0);
}

