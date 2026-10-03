#include "process.h"

typedef struct {
	usize registers[16];
	usize status_register;
	byte* stack_top;
	usize stack_size;
	int (*entry_point)(void);
	pid_t pid;
} Process;

typedef struct {
	Process table[PROCESS_MAX];
	Process* current_process;
	usize length;
} ProcessTable;


static ProcessTable process_table;

/**
 * Creates a new process, that will start its execution at the given entry_point when scheduled for the first time.
 * Returns the process ID of the newly created process, or 0 on error.
**/
pid_t process_new(int (*entry_point)(void)) {
	extern byte user_stack_top[];
	static pid_t pid = 1;

	if (process_table.length >= PROCESS_MAX) return 0;

	Process* process = &process_table.table[process_table.length];
	usize stack_size = USER_STACK_SIZE / PROCESS_MAX;
	byte* stack_top = user_stack_top - stack_size * process_table.length;

	*process = (Process) {
			.registers = {0},
			.status_register = 0x40000050,	// nZcv, aiF, ARM mode, current mode = USR
			.stack_top = stack_top,
			.stack_size = stack_size,
			.entry_point = entry_point,
			.pid = pid,
	};

	process->registers[15] = (usize) process->entry_point;	// Set the program counter to the entry point
	process->registers[13] = (usize) process->stack_top;	// Set the stack for the program

	process_table.length++;
	pid++;

	return pid-1;
}

/**
 * Removes the process with the given process ID.
**/
void process_remove(pid_t pid) {
	for (int i = 0; i < process_table.length; i++) {
		if (process_table.table[i].pid == pid) {
			/* Switch with the last process in the table and remove it */
			process_table.table[i] = process_table.table[process_table.length - 1];
			process_table.table[process_table.length - 1] = (Process) {0};
			process_table.length--;
		}
	}
}

/**
 * Sets the given process for execution, and saves the currently executing process.
**/
void process_execute(pid_t pid) {
	extern usize saved_state[];
	Process* next = 0;

	for (int i = 0; i < process_table.length; i++) {
		if (process_table.table[i].pid == pid) {
			next = &process_table.table[i];
			break;
		}
	}
	if (!next) return;	// The requested process does not exist, so we will just keep executing the current one

	/* Save the state of the current process from saved_state to the process table, as long as we were executing some process */
	if (process_table.current_process) {
		for (int i = 0; i <= 15; i++) {
			process_table.current_process->registers[i] = saved_state[i];
		}
		process_table.current_process->status_register = saved_state[16];
	}

	/* Move the stored state from the process table to saved_state */
	for (int i = 0; i <= 15; i++) {
		saved_state[i] = next->registers[i];
	}
	saved_state[16] = next->status_register;

	process_table.current_process = next;	// Update current process
}
