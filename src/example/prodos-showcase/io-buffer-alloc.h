#ifndef __PRODOS_SHOWCASE__IO_BUFFER_ALLOC
#define __PRODOS_SHOWCASE__IO_BUFFER_ALLOC

// Allocate an IO buffer from the $0800-$1FFF memory range
char *io_buffer_alloc();

// Free an IO buffer previously allocated by io_buffer_alloc
void io_buffer_free(char *);

#endif // __PRODOS_SHOWCASE__IO_BUFFER_ALLOC
