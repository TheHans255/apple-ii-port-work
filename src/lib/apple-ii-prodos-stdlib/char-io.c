#include "apple-ii-monitor.h"

char getchar() {
    // Use RDCHAR for character input, removing the high bit
    unsigned char c = appleii_rdchar();
    return c & 0x7f;
}

void __putchar(char c) {
    // Use COUT for character output, inserting the high bit
    if (__builtin_expect(c == '\n', 0)) c = '\r';
    appleii_cout(c | -128);
}