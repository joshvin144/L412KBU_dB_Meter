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
char* const timer_1_name = "TIMER 1";
char* const timer_2_name = "TIMER 2";
/* END TASK NAMES */

/* BEGIN TIMER PERIOD */
TickType_t timer_1_period = pdMS_TO_TICKS(TIMER_PERIOD_MS);
TickType_t timer_2_period = pdMS_TO_TICKS(TIMER_PERIOD_MS);
/* END TIMER PERIOD */

/* BEGIN AUTO-RELOAD */
UBaseType_t auto_reload = pdTRUE;
/* END AUTO-RELOAD */

/* BEGIN TASK HANDLE DECLARATIONS */
TimerHandle_t timer1TaskHandle = NULL;
TimerHandle_t timer2TaskHandle = NULL;
/* END TASK HANDLE DECLARATIONS */

StaticTimer_t timer_buffer_1;
StaticTimer_t timer_buffer_2;

timer_block_t timer_block_1;
timer_block_t timer_block_2;

void vTimer1Callback(TimerHandle_t xTimerHandle)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
}

void vTimer2Callback(TimerHandle_t xTimerHandle)
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
}

void init_timer_block(void)
{
	timer_block_1.timer_name = timer_1_name;
	timer_block_1.timer_period = TIMER_PERIOD_MS;
	timer_block_1.auto_reload = auto_reload;
	timer_block_1.p_timer_ID = (void*) 0;
	timer_block_1.p_timer_buffer = &timer_buffer_1;

	timer_block_2.timer_name = timer_2_name;
	timer_block_2.timer_period = TIMER_PERIOD_MS;
	timer_block_2.auto_reload = auto_reload;
	timer_block_2.p_timer_ID = (void*) 0;
	timer_block_2.p_timer_buffer = &timer_buffer_2;
}

void create_timer_task(void)
{
	init_timer_block();
	timer1TaskHandle = xTimerCreateStatic(timer_block_1.timer_name,
			                              timer_block_1.timer_period,
								          timer_block_1.auto_reload,
										  timer_block_1.p_timer_ID,
								          vTimer1Callback,
								          timer_block_1.p_timer_buffer);
	timer2TaskHandle = xTimerCreateStatic(timer_block_2.timer_name,
				                          timer_block_2.timer_period,
									      timer_block_2.auto_reload,
								          timer_block_2.p_timer_ID,
									      vTimer2Callback,
									      timer_block_2.p_timer_buffer);
}

void start_timer_task(void)
{
	xTimerStart(timer1TaskHandle, 0);
//	xTimerStart(timer2TaskHandle, 0);
}

