#ifndef PROCESS_H
#define PROCESS_H

#define USER_STACK_SIZE		0x10000L	// 64 kB
#define PROCESS_MAX			4

typedef unsigned int usize;
typedef unsigned char byte;
typedef int pid_t;

/**
 * Creates a new process, that will start its execution at the given entry_point when scheduled for the first time.
 * Returns the process ID of the newly created process, or 0 on error.
**/
pid_t process_new(int (*entry_point)(void));

/**
 * Removes the process with the given process ID.
**/
void process_remove(pid_t pid);

/**
 * Sets the given process for execution, and saves the currently executing process.
**/
void process_execute(pid_t pid);

#endif // PROCESS_H
