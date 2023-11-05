/*
 * auxiliary_task.c
 *
 *  Created on: Sep 12, 2023
 *      Author: jvincent
 */

/* BEGIN INCLUDES */
#include "stm32l4xx_hal.h"
#include "cmsis_gcc.h"
#include "FreeRTOS.h"
#include "task_definitions.h"
#include "auxiliary_task.h"
#include "stdbool.h"
#include "assert.h"
/* END INCLUDES */

// What to do after obtaining the last known return address
// Run the following to convert the address to a line number
// arm-none-eabi-addr2line -e L412KBU_dB_Meter.elf 0x8000511
// /Users/jvincent/STM32CubeIDE/workspace_1.6.1/L412KBU_dB_Meter/Debug/../Core/Src/auxiliary_task.c:83 (discriminator 1)
// If there are problems running arm-none-abi-addr2line, make sure that the following is included in the PATH:
// /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.macos64_1.5.0.202011040924/tools/bin/
// For programming through CubeProgrammer, make sure the following is included in the PATH:
// /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.macos64_1.6.0.202101291314/tools/bin
// For debugging through gdb, make sure the following is included in the PATH:
// /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.macos64_1.6.0.202101291314/tools/bin/native/mac_x64
// /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.macos64_1.6.0.202101291314/tools/bin

// For forcing a Hard Fault
#define RESERVED_ADDRESS 0x08020001

/* BEGIN TEST FUNCTION DEFINITIONS */

void illegal_memory_access_attempt(void)
{
	// Pointer to reserved memory address
	uint32_t* p_reserved_address;
	p_reserved_address = RESERVED_ADDRESS;
	// Attempt to read; a Hard Fault will be caused here
	uint32_t contents = *p_reserved_address;
}

/*
 * The snake that devours itself
 * The ouroboris function recursively calls itself without a base case
 * It will consume memory on the stack
 */
void ouroboris(void)
{
	ouroboris();
}

/* END TEST FUNCTION DEFINITIONS */

/* TASK DEFINITIONS BEGIN */
void vAuxiliaryTask(void* pvParams)
{
	/* Note that the following segment of code is run while starting up the task, only */

	/* Create any mutexes, semaphores, gueues, or other intertask communication mechanisms, here */

	/* Write task specific code, here */
	// illegal_memory_access_attempt();

	/* Note that the following segment consists of code that the RTOS cycles through. */

	for(;;)
	{
		/* Write application specific code, here */
		// ouroboris();
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
