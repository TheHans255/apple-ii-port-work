//
// Created by TheHans255 on 11/5/23.
//

// A utility for allocating IO and character buffers in ProDOS.
//
// The IO buffers that ProDOS uses to maintain a file's internal state
// have two primary limitations: they must be aligned to 256-byte pages
// (which most malloc implementations do not have the power to guarantee),
// and the allocation system used to protect them requires that read
// and write buffers must be kept separate from these IO buffers.
// This utility class solves both of those problems by allocating extra
// space to ensure a page-aligned buffer and providing the extra
// space as a character buffer to the user.

#ifndef APPLE_II_PRODOS_PRODOS_COMBO_BUFFER_H
#define APPLE_II_PRODOS_PRODOS_COMBO_BUFFER_H

#include <stdlib.h>

// A structure that contains an IO buffer for ProDOS files,
// plus a character buffer for the READ and WRITE syscalls.
// ProDOS IO buffers must be aligned to 256-byte pages,
// so this function offers the unaligned space as buffer
// space for reading and writing.
typedef struct prodos_combo_buffer {
    size_t user_buffer_length;
} PRODOS_COMBO_BUFFER;

// Allocate a new PRODOS_COMBO_BUFFER using malloc, with a scratch buffer of at least the given size.
// This buffer should be freed using normal free() once you are done with it
// (i.e. after any associated file has been closed).
PRODOS_COMBO_BUFFER *prodos_combo_buffer_malloc(size_t min_user_buffer_length);

// Get a pointer to the scratch space character buffer represented by this PRODOS_COMBO_BUFFER
char *prodos_combo_buffer_user_buffer(PRODOS_COMBO_BUFFER *buffer);

// Get a pointer to the ProDOS IO buffer represented by this PRODOS_COMBO_BUFFER
char *prodos_combo_buffer_io_buffer(PRODOS_COMBO_BUFFER *buffer);

#endif //APPLE_II_PRODOS_PRODOS_COMBO_BUFFER_H
