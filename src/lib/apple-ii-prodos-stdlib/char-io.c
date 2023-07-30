#include "apple-ii-monitor.h"

char getchar() {
    // Use RDCHAR for character input, removing the high bit
    unsigned char c = appleii_rdchar();
    return c & 0x7f;
}

// TODO: You may want to consider a decent VT100 emulator here,
// where control characters affect display positions.
// In particular, you may want to consider the alternate character set
// that displays the entire normal character set (including lowercase)
// in inverse if the high bit is off.

void __putchar(char c) {
    // Use COUT for character output, inserting the high bit
    if (__builtin_expect(c == '\n', 0)) c = '\r';
    appleii_cout(c | -128);
}