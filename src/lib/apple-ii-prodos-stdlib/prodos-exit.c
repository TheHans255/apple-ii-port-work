// In ProDOS, _exit is implemented as a QUIT syscall
// along with a smattering of housekeeping

#include "prodos-syscall.h"

void _fini(void);

__attribute__((noreturn))
void _exit (int exit_code)  {
    // Call _fini to clean things up, then go to ProDOS QUIT
    _fini();
    prodos_quit();
}