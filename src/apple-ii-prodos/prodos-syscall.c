#include "prodos-syscall-core.h"
#include "prodos-syscall.h"

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