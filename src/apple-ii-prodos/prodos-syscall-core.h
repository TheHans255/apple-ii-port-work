// Describes the low-level interface for issuing syscalls to ProDOS.

#ifndef __PRODOS_SYSCALL_CORE
#define __PRODOS_SYSCALL_CORE

// Because ProDOS syscall parameters must immediately follow the JSR
// syscall instruction in the code, the prodos-syscall-core module
// maintains a "syscall gadget" that is dynamically modified to produce
// the correct syscall instruction each time a syscall is needed,
// similar to how BASIC.SYSTEM handles syscalls.
// This means that to make a call, you must first set _prodos_syscall_number,
// then set _prodos_syscall_param, and finally call _prodos_syscall.
// This also means that _prodos_syscall is neither reentrant nor thread-safe.

// The index of the ProDOS syscall
extern unsigned char _prodos_syscall_number;
// The pointer to the ProDOS syscall parameters
extern void *_prodos_syscall_param;
// Issues the ProDOS syscall specified by _prodos_syscall_number
// and _prodos_syscall_param. Returns 0 if successful or an error
// code if there is an error.
extern char _prodos_syscall(void);

#define PRODOS_SYSCALL_QUIT 0x65
#define PRODOS_SYSCALL_CREATE 0xC0
#define PRODOS_SYSCALL_DESTROY 0xC1
#define PRODOS_SYSCALL_RENAME 0xC2
#define PRODOS_SYSCALL_SET_FILE_INFO 0xC3
#define PRODOS_SYSCALL_GET_FILE_INFO 0xC4
#define PRODOS_SYSCALL_ON_LINE 0xC5
#define PRODOS_SYSCALL_SET_PREFIX 0xC6
#define PRODOS_SYSCALL_GET_PREFIX 0xC7
#define PRODOS_SYSCALL_OPEN 0xC8
#define PRODOS_SYSCALL_NEWLINE 0xC9
#define PRODOS_SYSCALL_READ 0xCA
#define PRODOS_SYSCALL_WRITE 0xCB
#define PRODOS_SYSCALL_CLOSE 0xCC
#define PRODOS_SYSCALL_FLUSH 0xCD
#define PRODOS_SYSCALL_SET_MARK 0xCE
#define PRODOS_SYSCALL_GET_MARK 0xCF
#define PRODOS_SYSCALL_SET_EOF 0xD0
#define PRODOS_SYSCALL_GET_EOF 0xD1
#define PRODOS_SYSCALL_SET_BUF 0xD2
#define PRODOS_SYSCALL_GET_BUF 0xD3
#define PRODOS_SYSCALL_ALLOC_INTERRUPT 0xD4
#define PRODOS_SYSCALL_DEALLOC_INTERRUPT 0xD5
#define PRODOS_SYSCALL_READ_BLOCK 0xD6
#define PRODOS_SYSCALL_WRITE_BLOCK 0xD7

#endif // not __PRODOS_SYSCALL_CORE