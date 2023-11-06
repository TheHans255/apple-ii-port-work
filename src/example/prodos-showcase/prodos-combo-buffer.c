//
// Created by TheHans255 on 11/5/23.
//

#include <stdlib.h>
#include <stdio.h>
#include "prodos-combo-buffer.h"

PRODOS_COMBO_BUFFER *prodos_combo_buffer_malloc(size_t min_char_buffer_size) {
    size_t total_size = 1024 + 2 + min_char_buffer_size;
    void *candidate = malloc(total_size);
    printf("Candidate for size %d: %x", total_size, (unsigned int) candidate);
    size_t candidate_end;
    while ((candidate_end = (size_t) candidate + total_size) % 256 != 0) {
        size_t next_page_boundary = (candidate_end + 255) & 0xff00;
        size_t difference = next_page_boundary - candidate_end;
        total_size += difference;
        free(candidate);
        candidate = malloc(total_size);
        printf("New candidate for size %d: %x", total_size, (unsigned int) candidate);
    }
    PRODOS_COMBO_BUFFER *result = (PRODOS_COMBO_BUFFER *) candidate;
    result->user_buffer_length = total_size - 1024 - 2;
    return result;
}

char *prodos_combo_buffer_user_buffer(PRODOS_COMBO_BUFFER *buffer) {
    return ((char *) buffer) + 2;
}

char *prodos_combo_buffer_io_buffer(PRODOS_COMBO_BUFFER *buffer) {
    return ((char *) buffer) + 2 + buffer->user_buffer_length;
}
