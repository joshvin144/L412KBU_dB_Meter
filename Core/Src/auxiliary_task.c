/*
 * auxiliary_task.c
 *
 *  Created on: Sep 12, 2023
 *      Author: jvincent
 */

/* BEGIN INCLUDES */
#include "stm32l4xx_hal.h"
#include "FreeRTOS.h"
#include "task_definitions.h"
#include "auxiliary_task.h"
#include "stdbool.h"
#include "assert.h"
/* END INCLUDES */

// For reading the Link Register (LR)
#define __ASM __asm /*!< asm keyword for GNU Compiler */
#define __INLINE inline /*!< inline keyword for GNU Compiler */
#define __STATIC_INLINE static inline

// For forcing a Hard Fault
#define RESERVED_ADDRESS 0x08020001

// For tracking the number of recursive calls to ouroboris
static uint32_t entry_number;

/**
\brief Get Link Register
\details Returns the current value of the Link Register (LR).
\return LR Register value
*/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t __get_LR(void)
{
  register uint32_t result;

  __ASM volatile ("MOV %0, LR\n" : "=r" (result) );
  return(result);
}

/*
 * The snake that devours itself
 * The ouroboris function recursively calls itself without a base case
 * It will consume memory on the stack
 */
void ouroboris(uint32_t* p_entry_number)
{
	uint32_t entry_number = *p_entry_number;
	(*p_entry_number)++;
	ouroboris(p_entry_number);
}

void illegal_memory_access_attempt(void)
{
	// Store the lasst known return address
	uint32_t last_known_return_address = __get_LR();
	// Pointer to reserved memory address
	uint32_t* p_reserved_address;
	p_reserved_address = RESERVED_ADDRESS;
	// Attempt to read; a Hard Fault will be caused here
	uint32_t contents = *p_reserved_address;
	// Modify contents
	contents++;
	// Attempt to write
	*p_reserved_address = contents;
}

/* TASK DEFINITIONS BEGIN */
void vAuxiliaryTask(void* pvParams)
{
	/* Note that the following segment of code is run while starting up the task, only */

	/* Create any mutexes, semaphores, gueues, or other intertask communication mechanisms, here */

	/* Write task specific code, here */
	// entry_number = 0;
	illegal_memory_access_attempt();

	/* Note that the following segment consists of code that the RTOS cycles through. */

	for(;;)
	{
		/* Write application specific code, here */
		// ouroboris(&entry_number);
	}

	vTaskDelete(NULL);
}
/* TASK DEFINITIONS END */

/* BEGIN TASK BLOCKS */
void initialize_auxiliary_task_block(void)
{
	auxiliary_task_block.p_task_function = vAuxiliaryTask;
	auxiliary_task_block.task_name = auxiliary_task_name;
	auxiliary_task_block.stack_depth = AUXILIARY_TASK_STACK_SIZE;
	auxiliary_task_block.p_params = p_auxiliary_params;
	auxiliary_task_block.priority = AUXILIARY_TASK_PRIORITY;
	auxiliary_task_block.p_stack_buffer = auxiliary_stack_buffer;
	auxiliary_task_block.p_task_buffer = &auxiliary_task_buffer;
}
/* END TASK BLOCKS */

/* BEGIN TASK CREATION */

void create_auxiliary_task(void)
{
	initialize_auxiliary_task_block();
	auxiliaryTaskHandle = xTaskCreateStatic(auxiliary_task_block.p_task_function,
			auxiliary_task_block.task_name,
			auxiliary_task_block.stack_depth,
			auxiliary_task_block.p_params,
			auxiliary_task_block.priority,
			auxiliary_task_block.p_stack_buffer,
			auxiliary_task_block.p_task_buffer);
}

/* END TASK CREATION */
