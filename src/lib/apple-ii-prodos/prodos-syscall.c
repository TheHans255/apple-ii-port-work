#include "prodos-syscall-core.h"
#include "prodos-syscall.h"
#include "apple-ii-monitor.h"

__attribute__((noreturn))
void prodos_quit ()  {
    // Before the actual _quit syscall,
    // we need to invalidate the powerup byte.
    // We also need to do any cleanup and close open files,
    // but we will just assume this has already happened.
    (*APPLEII_MONITOR_POWERUP_BYTE)--;

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

char prodos_create(const char *pathname, struct prodos_file_info *file_info) {
    struct prodos_create_param {
        char param_count;
        const char *pathname;
        unsigned char access;
        unsigned char file_type;
        unsigned int aux_type;
        unsigned char storage_type;
        struct prodos_date create_date;
        struct prodos_time create_time;
    } __attribute((packed)) p;
    p.param_count = 7;
    p.pathname = pathname;
    p.access = file_info->access;
    p.file_type = file_info->file_type;
    p.aux_type = file_info->aux_type;
    p.storage_type = file_info->storage_type;
    p.create_date = file_info->create_date;
    p.create_time = file_info->create_time;
    _prodos_syscall_number = PRODOS_SYSCALL_CREATE;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_destroy(const char *pathname) {
    struct prodos_destroy_param {
        char param_count;
        const char *pathname;
    } __attribute((packed)) p;
    p.param_count = 1;
    p.pathname = pathname;
    _prodos_syscall_number = PRODOS_SYSCALL_DESTROY;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_rename(const char *pathname, const char *new_pathname) {
    struct prodos_rename_param {
        char param_count;
        const char *pathname;
        const char *new_pathname;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.pathname = pathname;
    p.new_pathname = new_pathname;
    _prodos_syscall_number = PRODOS_SYSCALL_RENAME;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_set_file_info(const char *pathname, struct prodos_file_info *file_info){
    struct prodos_set_file_param {
        char param_count;
        const char *pathname;
        struct prodos_file_info body;
    } __attribute((packed)) p;
    p.param_count = 7;
    p.pathname = pathname;
    p.body = *file_info;
    _prodos_syscall_number = PRODOS_SYSCALL_SET_FILE_INFO;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_get_file_info(const char *pathname, struct prodos_file_info *file_info){
    struct prodos_set_file_param {
        char param_count;
        const char *pathname;
        struct prodos_file_info body;
    } __attribute((packed)) p;
    p.param_count = 7;
    p.pathname = pathname;
    _prodos_syscall_number = PRODOS_SYSCALL_GET_FILE_INFO;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    *file_info = p.body;
    return error;
}

char prodos_on_line(unsigned char unit_num, struct prodos_online_volume_info *volume_info) {
    struct prodos_on_line_param {
        char param_count;
        unsigned char unit_num;
        struct prodos_online_volume_info *data_buffer;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.unit_num = unit_num;
    p.data_buffer = volume_info;
    _prodos_syscall_number = PRODOS_SYSCALL_ON_LINE;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_set_prefix(const char *pathname) {
    struct prodos_set_prefix_param {
        char param_count;
        const char *pathname;
    } __attribute((packed)) p;
    p.param_count = 1;
    p.pathname = pathname;
    _prodos_syscall_number = PRODOS_SYSCALL_SET_PREFIX;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_get_prefix(const char **pathname) {
    struct prodos_set_prefix_param {
        char param_count;
        const char *pathname;
    } __attribute((packed)) p;
    p.param_count = 1;
    _prodos_syscall_number = PRODOS_SYSCALL_GET_PREFIX;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    *pathname = p.pathname;
    return error;
}

char prodos_open(const char *pathname, char *io_buffer, char *ref_num) {
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

char prodos_newline(char ref_num, char enable_mask, char newline_char) {
    struct prodos_newline_param {
        char param_count;
        char ref_num;
        char enable_mask;
        char newline_char;
    } __attribute((packed)) p;
    p.param_count = 3;
    p.ref_num = ref_num;
    p.enable_mask = enable_mask;
    p.newline_char = newline_char;
    _prodos_syscall_number = PRODOS_SYSCALL_NEWLINE;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
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
        char ref_num;
    } __attribute((packed)) p;
    p.param_count = 1;
    p.ref_num = ref_num;
    _prodos_syscall_number = PRODOS_SYSCALL_CLOSE;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_flush(char ref_num) {
    struct prodos_flush_param {
        char param_count;
        char ref_num;
    } __attribute((packed)) p;
    p.param_count = 1;
    p.ref_num = ref_num;
    _prodos_syscall_number = PRODOS_SYSCALL_FLUSH;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_set_mark(char ref_num, unsigned long position) {
    struct prodos_set_mark_param {
        char param_count;
        char ref_num;
        unsigned int position_lo;
        unsigned char position_hi;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.ref_num = ref_num;
    p.position_lo = position % 65536;
    p.position_hi = position / 65536 % 256;
    _prodos_syscall_number = PRODOS_SYSCALL_SET_MARK;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_get_mark(char ref_num, unsigned long *position) {
    struct prodos_set_mark_param {
        char param_count;
        char ref_num;
        unsigned int position_lo;
        unsigned char position_hi;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.ref_num = ref_num;
    _prodos_syscall_number = PRODOS_SYSCALL_GET_MARK;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    *position = p.position_hi * 65536 + p.position_lo;
    return error;
}

char prodos_set_eof(char ref_num, unsigned long position) {
    struct prodos_set_eof_param {
        char param_count;
        char ref_num;
        unsigned int position_lo;
        unsigned char position_hi;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.ref_num = ref_num;
    p.position_lo = position % 65536;
    p.position_hi = position / 65536 % 256;
    _prodos_syscall_number = PRODOS_SYSCALL_SET_EOF;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_get_eof(char ref_num, unsigned long *position) {
    struct prodos_set_eof_param {
        char param_count;
        char ref_num;
        unsigned int position_lo;
        unsigned char position_hi;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.ref_num = ref_num;
    _prodos_syscall_number = PRODOS_SYSCALL_GET_EOF;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    *position = p.position_hi * 65536 + p.position_lo;
    return error;
}

char prodos_set_buf(char ref_num, unsigned char *io_buffer) {
    struct prodos_set_buf_param {
        char param_count;
        char ref_num;
        unsigned char *io_buffer;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.ref_num = ref_num;
    p.io_buffer = io_buffer;
    _prodos_syscall_number = PRODOS_SYSCALL_SET_BUF;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_get_buf(char ref_num, unsigned char **io_buffer) {
    struct prodos_get_buf_param {
        char param_count;
        char ref_num;
        unsigned char *io_buffer;
    } __attribute((packed)) p;
    p.param_count = 2;
    p.ref_num = ref_num;
    _prodos_syscall_number = PRODOS_SYSCALL_GET_BUF;
    _prodos_syscall_param = (void *) &p;
    char error = _prodos_syscall();
    *io_buffer = p.io_buffer;
    return error;
}

void prodos_get_time() {
    // No parameter list
    _prodos_syscall_number = PRODOS_SYSCALL_GET_TIME;
    _prodos_syscall_param = (void *) 0;
    _prodos_syscall();
}

char prodos_alloc_interrupt(unsigned char int_num, void (*int_code)()) {
    struct prodos_alloc_interrupt_param {
        char param_count;
        unsigned char int_num;
        void (*int_code)();
    } __attribute((packed)) p;
    p.param_count = 2;
    p.int_num = int_num;
    p.int_code = int_code;
    _prodos_syscall_number = PRODOS_SYSCALL_ALLOC_INTERRUPT;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_dealloc_interrupt(unsigned char int_num) {
    struct prodos_alloc_interrupt_param {
        char param_count;
        unsigned char int_num;
    } __attribute((packed)) p;
    p.param_count = 1;
    p.int_num = int_num;
    _prodos_syscall_number = PRODOS_SYSCALL_DEALLOC_INTERRUPT;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_read_block(unsigned char unit_num, unsigned char *data_buffer, unsigned int block_num) {
    struct prodos_read_block_param {
        char param_count;
        unsigned char unit_num;
        unsigned char *data_buffer;
        unsigned int block_num;
    } __attribute((packed)) p;
    p.param_count = 3;
    p.unit_num = unit_num;
    p.data_buffer = data_buffer;
    p.block_num = block_num;
    _prodos_syscall_number = PRODOS_SYSCALL_READ_BLOCK;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}

char prodos_write_block(unsigned char unit_num, unsigned char *data_buffer, unsigned int block_num) {
    struct prodos_write_block_param {
        char param_count;
        unsigned char unit_num;
        unsigned char *data_buffer;
        unsigned int block_num;
    } __attribute((packed)) p;
    p.param_count = 3;
    p.unit_num = unit_num;
    p.data_buffer = data_buffer;
    p.block_num = block_num;
    _prodos_syscall_number = PRODOS_SYSCALL_WRITE_BLOCK;
    _prodos_syscall_param = (void *) &p;
    return _prodos_syscall();
}
