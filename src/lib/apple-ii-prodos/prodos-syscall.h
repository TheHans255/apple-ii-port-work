// Defines a high-level, C interface for making calls to ProDOS

#ifndef __PRODOS_SYSCALL
#define __PRODOS_SYSCALL

#define PRODOS_ACCESS_DESTROY 0x80
#define PRODOS_ACCESS_RENAME 0x40
#define PRODOS_ACCESS_BACKUP 0x20
#define PRODOS_ACCESS_WRITE 0x02
#define PRODOS_ACCESS_READ 0x01
#define PRODOS_ACCESS_FULL 0xE3

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

// TODO: Include the ProDOS concept of file levels in this library/documentation

// A creation or modification date for a ProDOS file
struct prodos_date {
    unsigned int day : 5;
    unsigned int month: 4;
    unsigned int year: 7;
} __attribute((packed));

// A creation or modification time for a ProDOS file
struct prodos_time {
    unsigned char minute;
    unsigned char hour;
} __attribute((packed));

// A set of ProDOS file info
struct prodos_file_info {
    // The access types that are permitted for this file.
    // This should be set to PRODOS_ACCESS_FULL
    // or a bitwise OR of one or more of the other PRODOS_ACCESS macros.
    unsigned char access;
    // The file's type. Should be set to one of the PRODOS_FILETYPE macros.
    unsigned char file_type;
    // An extra two bytes to mark the file, specific to the
    // system program that opens it. For instance, BASIC uses it to store
    // text-file record size or binary-file load address.
    unsigned int aux_type;
    // The file's storage type. Should be 0x0D for directories, 0x01 for standard files
    unsigned char storage_type;
    // The number of blocks used by the file
    unsigned int blocks_used;
    // The date the file was last modified
    struct prodos_date mod_date;
    // The time the file was last modified
    struct prodos_time mod_time;
    // The date the file was created
    struct prodos_date create_date;
    // The time the file was created
    struct prodos_time create_time;
} __attribute((packed));

// Exit to ProDOS immediately
// This should only be called from _exit()
__attribute__((noreturn))
void prodos_quit(void);

// Create a new ProDOS file or directory
// pathname: The path to the file. Should be a length-prefixed ASCII string.
// file_info: A pointer to information describing the file. The modification
//            time and blocks used are ignored.
char prodos_create(const char *pathname, struct prodos_file_info *file_info);

// Deletes the ProDOS file with the given pathname
// pathname: The path to the file. Should be a length-prefixed ASCII string.
char prodos_destroy(const char *pathname);

// Renames the file with the given pathname to have the new pathname.
// Both filenames must be in the same directory (i.e. this is not a file move)
// pathname: The path to the file. Should be a length-prefixed ASCII string.
// new_pathname: The new path the file should have.
char prodos_rename(const char *pathname, const char *new_pathname);

// Modifies the given file's metadata.
// pathname: The path to the file. Should be a length-prefixed ASCII string.
// file_info: A pointer to information describing the file. The creation time,
//            storage type, and blocks used are ignored.
char prodos_set_file_info(const char *pathname, struct prodos_file_info *file_info);

// Returns the given file's metadata.
// pathname: The path to the file. Should be a length-prefixed ASCII string.
// file_info: A pointer in which to store the given file's metadata
char prodos_get_file_info(const char *pathname, struct prodos_file_info *file_info);

// Information about an online volume
struct prodos_online_volume_info {
    // The length of the volume name
    unsigned int name_len: 4;
    // The slot the volume is in
    unsigned int slot : 3;
    // The drive the volume is in (0 for slot 1, 1 for slot 2)
    unsigned int drive : 1;
    // The name of the volume (without a '/' prefix)
    unsigned char name[15];
} __attribute((packed));

// Returns the list of either the specified volumes or all volumes currently online.
// unit_num: If zero, retrieves all drives. Otherwise, the highest bit indicates the
//           drive number, and the three bits below that indicate the slot number.
// volume_info: The buffer to store the online volume output. If specifying a specific
//              drive, this can point to only one struct, but if retrieving information on
//              all volumes, this should point to an array of 16 of them (256 bytes total).
//              The last valid record will be followed by one with the first byte set to zero.
char prodos_on_line(unsigned char unit_num, struct prodos_online_volume_info *volume_info);

// Set the current prefix (working directory)
// pathname: The path to the file. Should be a length-prefixed ASCII file
char prodos_set_prefix(const char *pathname);

// Get the current prefix (working directory)
// pathname: A data buffer to output the prefix. Outputs a length byte
//           and brackets the path with slashes (e.g. "$D/APPLE/BYTES").
//           This buffer should be at least 64 bytes long.
char prodos_get_prefix(const char **pathname);

// Open a ProDOS file with the given pathname
// pathname: The path to the file. Should be a length-prefixed ASCII file
// io_buffer: A pointer to a 1024-byte, page-aligned buffer for managing the file.
// ref_num: Outputs a reference number.
char prodos_open(const char *pathname, char *io_buffer, char *ref_num);

// Set newline read settings for the given file. When enabled,
// file reads will terminate when the given character is encountered.
// ref_num: The file number to read from
// enable_mask: When non-zero, all characters read will be ANDed against
//              this mask before being tested against newline_char
//              (e.g. 0x7F can be used to only test bits 0 through 6).
//              When zero, newline mode is disabled.
// newline_char: When newline is enabled, ProDOS will terminate reads for
//               this file when it encounters this character. (Reads
//               will include the character).
char prodos_newline(char ref_num, char enable_mask, char newline_char);

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

// Closes the ProDOS file with the given reference number.
// If that number is 0, all files at or above the current level are closed.
char prodos_close(char ref_num);

// Flushes all data in the write buffer for the file with the given reference number.
// If that number is 0, all files at or above the current level are flushed.
char prodos_flush(char ref_num);

// Seeks the given file to the given position (MARK)
// ref_num: The reference number for the file
// position: The position to seek to. Only the lower 3 bytes are used.
//           Cannot exceed the file's EOF.
char prodos_set_mark(char ref_num, unsigned long position);

// Returns the given file's current seek position (MARK)
// ref_num: The reference number for the file
// position: The position the file is currently reading at
char prodos_get_mark(char ref_num, unsigned long *position);

// Sets the logical size of the given file (its EOF)
// ref_num: The reference number for the file
// position: The new logical size of the file. Only the lower 3 bytes are used.
//           If the new EOF is smaller, blocks past the EOF are released.
//           If the new EOF is greater, no new blocks are allocated.
char prodos_set_eof(char ref_num, unsigned long eof);

// Returns the logical size of the given file (its EOF)
// ref_num: The reference number for the file
// eof: The current logical size of the file
char prodos_get_eof(char ref_num, unsigned long *eof);

// Reassigns the IO buffer for the given file
// ref_num: The reference number for the file
// io_buffer: A pointer to a 1024-byte, page-aligned buffer to use.
//            The contents of the previous buffer will be copied to this
//            buffer and the previous buffer will be released.
char prodos_set_buf(char ref_num, unsigned char *io_buffer);

// Returns the IO buffer for the given file
// ref_num: The reference number for the file
// io_buffer: Returns the pointer to the 1024-byte IO buffer for the file
char prodos_get_buf(char ref_num, unsigned char **io_buffer);

#define PRODOS_SYSTEM_DATE ((struct prodos_date *) 0xBF90)
#define PRODOS_SYSTEM_TIME ((struct prodos_time *) 0xBF92)

// Updates the current date and time in the system date and time locations
// at PRODOS_SYSTEM_DATE and PRODOS_SYSTEM_TIME
// if a clock/calendar routine is installed.
void prodos_get_time();

// Allocates a routine for handling interrupts. This should be set up
// before the interrupt-creating device is enabled.
// int_num: The interrupt priority of the given code
// int_code: The code to run when an interrupt occurs. The code should have
//           the following properties:
//           - Begins with a CLD instruction
//           - Uses the registers, zero page 0xFA through 0xFF, and
//             up to 16 bytes of stack space, as scratch
//           - Returns (via RTS) with the carry flag clear if the interrupt
//             is handled, with the carry flag set otherwise.
char prodos_alloc_interrupt(unsigned char int_num, void (*int_code)());

// Deallocated the routine with the given interrupt.
char prodos_dealloc_interrupt(unsigned char int_num);

// Read a logical block directly from a disk. This is intended to be used
// by utility (e.g. copying) and diagnostic programs, or to read DOS 3.3 disk.
// It should NOT be used by most programs.
// unit_num: The device to read. The high bit is the drive number,
//           the 3 bits below that are the slot number.
// data_buffer: A buffer to read to - should be at least 512 bytes in length
// block_num: The block number to read.
char prodos_read_block(unsigned char unit_num, unsigned char *data_buffer, unsigned int block_num);

// Read a logical block directly from a disk. This is intended to be used
// by utility (e.g. copying) and diagnostic programs, or to read DOS 3.3 disk.
// It should REALLY, VERY MUCH NOT be used by most programs, ESPECIALLY
// on properly-working ProDOS volumes!
// unit_num: The device to write to. The high bit is the drive number,
//           the 3 bits below that are the slot number.
// data_buffer: A buffer to write from, containing the data for the 512-byte block.
// block_num: The block number to write.
char prodos_write_block(unsigned char unit_num, unsigned char *data_buffer, unsigned int block_num);

#endif