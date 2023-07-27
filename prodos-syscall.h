// Defines a high-level, C interface for making calls to ProDOS

#ifndef __PRODOS_SYSCALL
#define __PRODOS_SYSCALL

#define PRODOS_ERROR_NONE 0
#define PRODOS_ERROR_BAD_CALL_NUMBER 0x01
#define PRODOS_ERROR_BAD_CALL_PARAM_COUNT 0x04
#define PRODOS_ERROR_INTERRUPT_TABLE_FULL 0x25
#define PRODOS_ERROR_IO_ERROR 0x27
#define PRODOS_ERROR_NO_DEVICE_CONNECTED 0x28
#define PRODOS_ERROR_DISK_WRITE_PROTECTED 0x2B
#define PRODOS_ERROR_DISK_SWITCHED 0x2E
#define PRODOS_ERROR_INVALID_PATHNAME 0x40
#define PRODOS_ERROR_MAX_FILES_OPEN 0x42
#define PRODOS_ERROR_INVALID_REF_NUM 0x43
#define PRODOS_ERROR_DIRECTORY_NOT_FOUND 0x44
#define PRODOS_ERROR_VOL_NOT_FOUND 0x45
#define PRODOS_ERROR_FILE_NOT_FOUND 0x46
#define PRODOS_ERROR_DUPLICATE_FILENAME 0x47
#define PRODOS_ERROR_VOLUME_FULL 0x48
#define PRODOS_ERROR_DIRECTORY_FULL 0x49
#define PRODOS_ERROR_INCOMPATIBLE_FORMAT 0x4A
#define PRODOS_ERROR_IS_A_DIRECTORY 0x4A
#define PRODOS_ERROR_UNSUPPORTED_STORAGE_TYPE 0x4B
#define PRODOS_ERROR_END_OF_FILE 0x4C
#define PRODOS_ERROR_POSITION_OUT_OF_RANGE 0x4D
#define PRODOS_ERROR_FILE_ACCESS_ERROR 0x4E
#define PRODOS_ERROR_FILE_LOCKED 0x4E
#define PRODOS_ERROR_FILE_IS_OPEN 0x50
#define PRODOS_ERROR_DIRECTORY_STRUCTURE_CHANGED 0x51
#define PRODOS_ERROR_NOT_A_PRODOS_VOLUME 0x52
#define PRODOS_ERROR_INVALID_SYSCALL_PARAM 0x53
#define PRODOS_ERROR_VOLUME_CONTROL_BLOCK_TABLE_FULL 0x55
#define PRODOS_ERROR_BAD_BUFFER_ADDRESS 0x56
#define PRODOS_ERROR_DUPLICATE_VOLUME 0x57
#define PRODOS_ERROR_FILE_STRUCTURE_DAMAGED 0x5A

#define PRODOS_FILETYPE_TYPELESS 0x00
#define PRODOS_FILETYPE_BADBLOCK 0x01
#define PRODOS_FILETYPE_ASCII 0x04
#define PRODOS_FILETYPE_BINARY 0x06
#define PRODOS_FILETYPE_GRAPHICS_SCREEN 0x08
#define PRODOS_FILETYPE_DIRECTORY 0x0F
#define PRODOS_FILETYPE_APPLEWORKS_DATABASE 0x19
#define PRODOS_FILETYPE_APPLEWORKS_WORD_PROCESSOR 0x1A
#define PRODOS_FILETYPE_APPLEWORKS_SPREADSHEET 0x1B
#define PRODOS_FILETYPE_PASCAL_AREA 0xEF
#define PRODOS_FILETYPE_PRODOS_COMMAND 0xF0
#define PRODOS_FILETYPE_USER_DEFINED_1 0xF1
#define PRODOS_FILETYPE_USER_DEFINED_2 0xF2
#define PRODOS_FILETYPE_USER_DEFINED_3 0xF3
#define PRODOS_FILETYPE_USER_DEFINED_4 0xF4
#define PRODOS_FILETYPE_USER_DEFINED_5 0xF5
#define PRODOS_FILETYPE_USER_DEFINED_6 0xF6
#define PRODOS_FILETYPE_USER_DEFINED_7 0xF7
#define PRODOS_FILETYPE_USER_DEFINED_8 0xF8
#define PRODOS_FILETYPE_INTEGER_BASIC_PROGRAM 0xFA
#define PRODOS_FILETYPE_INTEGER_BASIC_VARIABLE 0xFB
#define PRODOS_FILETYPE_APPLESOFT_BASIC_PROGRAM 0xFC
#define PRODOS_FILETYPE_APPLESOFT_BASIC_VARIABLE 0xFD
#define PRODOS_FILETYPE_RELOCATABLE_CODE_FILE 0xFE
#define PRODOS_FILETYPE_SYSTEM_PROGRAM 0xFF

// Open a ProDOS file with the given pathname
// pathname: The path to the file
// io_buffer: A pointer to a buffer for input
// ref_num: Outputs a reference number
char prodos_open(char *pathname, char *io_buffer, char *ref_num);

// Read from a ProDOS file, starting at its current position
// ref_num: The file number to read from
// data_buffer: A buffer to read to
// request_count: The maximum number of characters to read
// trans_count: Outputs the number of characters actually read
char prodos_read(char ref_num, char *data_buffer, unsigned int request_count, unsigned int *trans_count);

// Write to a ProDOS file, starting at its current position
// ref_num: The file number to write to
// data_buffer: A buffer to write from
// request_count: The maximum number of characters to write
// trans_count: Outputs the number of characters actually written
char prodos_write(char ref_num, char *data_buffer, unsigned int request_count, unsigned int *trans_count);

// Closes a ProDOS file
char prodos_close(char ref_num);

#endif