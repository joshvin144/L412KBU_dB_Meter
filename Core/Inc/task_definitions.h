/*
 * task_definitions.h
 *
 *  Created on: May 18, 2023
 *      Author: jvincent
 */

#ifndef TASK_DEFINITIONS_H_
#define TASK_DEFINITIONS_H_

/* BEGIN INCLUDES */
#include "task.h"
/* END INCLUDES */

/* BEGIN TASK BLOCK DEFINITION */
// Task block to store all the variables necessary to create a task
typedef struct task_block_t
{
	TaskFunction_t p_task_function;
	char* task_name;
	uint32_t stack_depth;
	void* p_params;
	UBaseType_t priority;
	StackType_t* p_stack_buffer;
	StaticTask_t* p_task_buffer;
}task_block_t;
/* END TASK BLOCK DEFINITION */

/* BEGIN TASK DECLARATIONS */
void vSystemTask(void* pvParams);
void vAuxiliaryTask(void* pvParams);
/* END TASK DECLARATIONS */

/* BEGIN TASK STACK SIZE DEFINITIONS */
#define SYSTEM_TASK_STACK_SIZE 1024
#define AUXILIARY_TASK_STACK_SIZE 1024
/* END TASK STACK SIZE DEFINITIONS */

/* BEGIN TASK PRIORITY DEFINITIONS */
#define SYSTEM_TASK_PRIORITY 1
#define AUXILIARY_TASK_PRIORITY 1
/* END TASK PRIORITY DEFINITIONS */

/* BEGIN TASK STACK BUFFER DECLARATIONS */
StackType_t system_stack_buffer[SYSTEM_TASK_STACK_SIZE];
StackType_t auxiliary_stack_buffer[AUXILIARY_TASK_STACK_SIZE];
/* END TASK STACK BUFFER DECLARATIONS */

/* BEGIN TASK BUFFER */
StaticTask_t system_task_buffer;
StaticTask_t auxiliary_task_buffer;
/* END TASK BUFFER */

/* BEGIN TASK BLOCK DECLARATIONS */
task_block_t system_task_block;
task_block_t auxiliary_task_block;
/* END TASK BLOCK DECLARATIONS */

#endif /* TASK_DEFINITIONS_H_ */
