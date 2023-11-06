#include "io-buffer-alloc.h"
#include <stdlib.h>

#define BUFFER_LOCATIONS ((char *) 0x800)
static unsigned char bitmap = 0;

// Allocate an IO buffer from the $0800-$1FFF memory range
char *io_buffer_alloc() {
    unsigned char bitmap_index = 1;
    char *buffer = BUFFER_LOCATIONS;
    while (bitmap & bitmap_index) {
        bitmap_index <<= 1;
        buffer += 1024;
    }
    if (buffer >= ((char *) 0x2000)) {
        return NULL;
    }
    bitmap |= bitmap_index;
    return buffer;
}

// Free an IO buffer previously allocated by io_buffer_alloc
void io_buffer_free(char *buffer){
    unsigned char bitmap_index = 1 << (((unsigned int) (buffer - BUFFER_LOCATIONS)) / 1024);
    bitmap &= ~bitmap_index;
}
