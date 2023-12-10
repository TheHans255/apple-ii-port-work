#include "apple-ii-io.h"
#include "apple-iie-io.h"
#include "text-lores-io.h"

void *memcpy(void *dest, const void *src, size_t count);

// Implement a simple text windowing system

static unsigned char text_x = 0;
static unsigned char text_y = 0;
static unsigned char text_top = 0;
static unsigned char text_bot = 24;
static unsigned char text_left = 0;
static unsigned char text_width = 40;

static enum appleii_lores_color lores_color = LORES_BLACK;

static char *get_line_address(unsigned char line_num) {
    return &(APPLEII_TEXT_PAGE_1[line_num % 8 * (unsigned int) 128 + line_num / 8 * (unsigned int) 40]);
}

static void scroll_window_once() {
    for (unsigned char y = text_top + 1; y < text_bot; y++) {
        char *prev_line_address = get_line_address(y - 1);
        char *cur_line_address = get_line_address(y);
        memcpy(prev_line_address + text_left, cur_line_address + text_left, text_width);
    }
    char *bot_line_address = get_line_address(text_bot - 1);
    for (unsigned char x = 0; x < text_width; x++) {
        bot_line_address[text_left + x] = 0xA0;
    }
    text_y--;
}

void lores_set_color(enum appleii_lores_color color) {
    lores_color = color;
}

void lores_plot(unsigned char x, unsigned char y) {
    char *line_address = get_line_address(y / 2);
    if (y % 2) {
        line_address[x] &= 0x0f;
        line_address[x] |= lores_color << 4;
    } else {
        line_address[x] &= 0xf0;
        line_address[x] |= lores_color;
    }
}

void lores_vline(unsigned char x, unsigned char y1, unsigned char y2) {
    // For now, do the stupid thing of plotting from a to b.
    // LLVM might be able to tell
    for (unsigned char y = y1; y <= y2; y++) {
        lores_plot(x, y);
    }
}

void lores_hline(unsigned char x1, unsigned char x2, unsigned char y) {
    // For now, do the stupid thing of plotting from a to b.
    // LLVM might be able to tell
    for (unsigned char x = x1; x <= x2; x++) {
        lores_plot(x, y);
    }
}

enum appleii_lores_color lores_scrn(unsigned char x, unsigned char y) {
    char *line_address = get_line_address(y / 2);
    if (y % 2) {
        return line_address[x] / 16;
    } else {
        return line_address[x] % 16;
    }
}

void text_set_htab(unsigned char x) {
    text_x = x;
}

void text_set_vtab(unsigned char y) {
    text_y = y;
}

void text_set_window_left(unsigned char left) {
    text_left = left;
}

void text_set_window_width(unsigned char width) {
    text_width = width;
}

void text_set_window_top(unsigned char top) {
    text_top = top;
}

void text_set_window_bottom(unsigned char bottom) {
    text_bot = bottom;
}

void text_home() {
    // wipe text window to 0xA0 (normal space)
    for (unsigned char y = text_top; y < text_bot; y++) {
        char *line_address = get_line_address(y);
        for (unsigned char x = 0; x < text_width; x++) {
            line_address[text_left + x] = 0xa0;
        }
    }
    text_x = text_left;
    text_y = text_top;
}

size_t text_getln(char *buffer, size_t buffer_len) {
    size_t input_size = 0;
    while (1) {
        // TODO: Flashing cursor
        char c = getchar();
        // RUB character
        if (c == 0x7f) { 
            if (input_size > 0) {
                input_size--;
                text_x--;
                if (text_x < text_left) {
                    text_x = text_left + text_width - 1;
                    text_y--;
                }
            }
        } else {
            __putchar(c);
            if (input_size < buffer_len - 1) {
                buffer[input_size] = c;
            }
            input_size++;
            if (c == '\r' || c == '\n') {
                break;
            }
        }
    }
    buffer[(input_size < buffer_len ? input_size : buffer_len) - 1] = '\0';
    return input_size;
}

int getchar() {
    *APPLEII_KEYBOARD_STROBE = 0;
    unsigned char c;
    while ((c = *APPLEII_KEYBOARD_DATA) < 128) ;
    return c & 0x7f;
}

// TODO: You may want to consider a decent VT100 emulator here,
// where control characters affect display positions.
// In particular, you may want to consider the alternate character set
// that displays the entire normal character set (including lowercase)
// in inverse if the high bit is off.

void __putchar(char c) {
    if (c >= ' ') {
        char *line_address = get_line_address(text_y);
        line_address[text_x] = c | 0x80;
        text_x++;
        if (text_x > text_left + text_width) {
            text_y++;
            text_x = text_left;
        }
    } else if (c == '\n') {
        text_y++;
        text_x = 0;
    }
    // TODO: Handle other control characters here
    while (text_y >= text_bot) {
        scroll_window_once();
    }
}