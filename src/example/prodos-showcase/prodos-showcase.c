//
// Created by TheHans255 on 9/9/23.
//

#include "prodos-syscall.h"
#include "stdio.h"

void * memcpy(void *dest, const void *src, unsigned short count);

const char TEST_PATHNAME[] = "\x09""TEST1.TXT";

void list_volumes() {
    struct prodos_online_volume_info volume_info[16];
    char error = prodos_on_line(0, volume_info);
    if (error) {
        printf("Error during ON_LINE: %x\n", error);
        return;
    }
    for (char i = 0; i < 16; i++) {
        struct prodos_online_volume_info record = volume_info[i];
        if (record.name_len == 0) {
            break;
        }
        char filename_buf[16];
        memcpy(filename_buf, record.name, record.name_len);
        filename_buf[record.name_len] = '\0';
        printf("S%dD%d: %s\n", record.slot, record.drive, filename_buf);
    }
}

void write_and_read_file() {
    // start by destroying the file if it exists
    prodos_destroy(TEST_PATHNAME);
    // then create it and start working
    {
        struct prodos_file_info file_info;
        file_info.access = PRODOS_ACCESS_FULL;
        file_info.file_type = PRODOS_FILETYPE_ASCII;
        file_info.aux_type = 0;
        file_info.storage_type = 0x01;
        file_info.create_date = *PRODOS_SYSTEM_DATE;
        file_info.create_time = *PRODOS_SYSTEM_TIME;
        prodos_create(TEST_PATHNAME, &file_info);
    }
    char ref_num;
    {
        char open_error = prodos_open(TEST_PATHNAME, (char *) 0x800, &ref_num);
        if (open_error) {
            printf("Error during OPEN: %x\n", open_error);
            return;
        }
    }
    for (unsigned int i = 0; i < 20; i++) {
        unsigned int square = i * i;
        char line[12];
        int write_count = snprintf(line, 12, "%d\r", square);
        // TODO: All the high bits should be set when actually writing to a ProDOS file
        unsigned int final_write_count;
        prodos_write(ref_num, line, write_count, &final_write_count);
    }
    prodos_set_mark(ref_num, 0);
    prodos_newline(ref_num, 0x7F, '\n');
    {
        char read_error;
        char line[41];
        while (1) {
            unsigned int final_read_count;
            read_error = prodos_read(ref_num, line, 40, &final_read_count);
            if (read_error) {
                if (read_error != PRODOS_ERROR_END_OF_FILE) {
                    printf("Error during READ: %x\n", read_error);
                }
                break;
            }
            line[final_read_count] = '\0';
            printf("%s", line);
        }
    }
    {
        unsigned long file_eof;
        prodos_get_eof(ref_num, &file_eof);
        printf("%ld total bytes written", file_eof);
    }
    prodos_close(ref_num);
}

int main() {
    list_volumes();
    getchar();
    write_and_read_file();
    getchar();
    return 0;
}