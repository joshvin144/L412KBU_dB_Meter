/*
 * timer_task.h
 *
 *  Created on: Oct 17, 2023
 *      Author: jvincent
 */

#ifndef INC_TIMER_TASK_H_
#define INC_TIMER_TASK_H_

/* BEGIN INCLUDES */
#include "projdefs.h"
#include "timers.h"
/* BEGIN INCLUDES */

#define TIMER_PERIOD_MS 500

typedef struct timer_block_t
{
	char* timer_name;
	TickType_t timer_period;
	UBaseType_t auto_reload;
	void* p_timer_ID;
	StaticTimer_t* p_timer_buffer;
}timer_block_t;

#endif /* INC_TIMER_TASK_H_ */
