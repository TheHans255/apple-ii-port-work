#include "apple-ii-io.h"

unsigned char paddle_read(unsigned char paddle_index) {
    volatile char *paddle_address = APPLEII_ANALOG_INPUT_0 + paddle_index;
    unsigned char i = 0;
    char dummy = *APPLEII_ANALOG_RESET;
    for (; i < 255; i++) {
        if (*paddle_address > 0) {
            break;
        }
    }
    return i;
}