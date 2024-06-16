#include "fs_controller.h"
#include "isr.h"
#include "types.h"

#ifndef SYSCALLS_H
#define SYSCALLS_H

#define MAX_SYSCALLS 450

/* Syscall Debugging: Comprehensive */
#define DEBUG_SYSCALLS 1
#define DEBUG_SYSCALLS_ARGS 1

/* Syscall Debugging: Important */
#define DEBUG_SYSCALLS_FAILS 1
#define DEBUG_SYSCALLS_STUB 1

/* Syscall Debugging: Essential */
#define DEBUG_SYSCALLS_MISSING 1

void syscallHandler(AsmPassedInterrupt *regs);
void initiateSyscalls();

/* System call registration */
void syscallRegFs();
void syscallRegMem();
void syscallRegSig();
void syscallsRegEnv();
void syscallsRegProc();
void syscallsRegClock();

void registerSyscall(uint32_t id, void *handler); // <- the master

/* Standard output handlers (io.c) */
int readHandler(OpenFile *fd, uint8_t *in, size_t limit);
int writeHandler(OpenFile *fd, uint8_t *out, size_t limit);
int ioctlHandler(OpenFile *fd, uint64_t request, void *arg);

size_t mmapHandler(size_t addr, size_t length, int prot, int flags,
                   OpenFile *fd, size_t pgoffset);

/* Defined in io.c */
extern SpecialHandlers stdio;

#endif
