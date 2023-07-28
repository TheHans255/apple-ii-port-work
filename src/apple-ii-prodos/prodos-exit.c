// In ProDOS, _exit is implemented as a QUIT syscall
// along with a smattering of housekeeping

#include "prodos-syscall-core.h"

#define POWERUP_BYTE ((char *) 0x3f4)

void _fini(void);

__attribute__((noreturn))
void _exit (int exit_code)  {
    // Before the actual _quit syscall,
    // we need to call _fini and invalidate the powerup byte
    _fini();
    (*POWERUP_BYTE)--;

    struct prodos_quit_param {
        char param_count;
        char quit_type;
        void *reserved_1;
        char reserved_2;
        void *reserved_3;
    } __attribute((packed)) p;
    p.param_count = 4;
    p.quit_type = 0;
    p.reserved_1 = (void *) 0;
    p.reserved_2 = 0;
    p.reserved_3 = (void *) 0;
    _prodos_syscall_number = PRODOS_SYSCALL_QUIT;
    _prodos_syscall_param = (void *) &p;
    _prodos_syscall();

    __builtin_unreachable();
}