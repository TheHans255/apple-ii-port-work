#include "prodos-syscall-core.h"
#include "prodos-syscall.h"

#define POWERUP_BYTE ((char *) 0x3f4)

__attribute__((noreturn))
void prodos_quit ()  {
    // Before the actual _quit syscall,
    // we need to invalidate the powerup byte.
    // We also need to do any cleanup and close open files,
    // but we will just assume this has already happened.
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

char prodos_open(char *pathname, char *io_buffer, char *ref_num) {
    struct prodos_open_param {
        char param_count;
        char *pathname;
        char *io_buffer;
        char ref_num;
    } __attribute((packed)) p;
    p.param_count = 3;
    p.io_buffer = io_buffer;
    p.pathname = pathname;
    p.ref_num = 64;
    _prodos_syscall_number = PRODOS_SYSCALL_OPEN;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    if (error == PRODOS_ERROR_NONE) {
        *ref_num = p.ref_num;
    }
    return error;
}

char prodos_read(char ref_num, char *data_buffer, unsigned int request_count, unsigned int *trans_count) {
    struct prodos_read_param {
        char param_count;
        char ref_num;
        char *data_buffer;
        unsigned int request_count;
        unsigned int trans_count;
    } __attribute((packed)) p;
    p.param_count = 4;
    p.ref_num = ref_num;
    p.data_buffer = data_buffer;
    p.request_count = request_count;
    p.trans_count = 0;
    _prodos_syscall_number = PRODOS_SYSCALL_READ;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    if (error == PRODOS_ERROR_NONE) {
        *trans_count = p.trans_count;
    }
    return error;
}

char prodos_write(char ref_num, char *data_buffer, unsigned int request_count, unsigned int *trans_count) {
    struct prodos_write_param {
        char param_count;
        char ref_num;
        char *data_buffer;
        unsigned int request_count;
        unsigned int trans_count;
    } __attribute((packed)) p;
    p.param_count = 4;
    p.ref_num = ref_num;
    p.data_buffer = data_buffer;
    p.request_count = request_count;
    p.trans_count = 0;
    _prodos_syscall_number = PRODOS_SYSCALL_WRITE;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    if (error == PRODOS_ERROR_NONE) {
        *trans_count = p.trans_count;
    }
    return error;
}

char prodos_close(char ref_num) {
    struct prodos_close_param {
        char param_count;
        char *pathname;
        char *io_buffer;
        char ref_num;
    } __attribute((packed)) p;
    p.param_count = 1;
    p.ref_num = ref_num;
    _prodos_syscall_number = PRODOS_SYSCALL_CLOSE;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}