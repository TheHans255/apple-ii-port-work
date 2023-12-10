#include "apple-ii-io.h"

// A small library for plotting on the HIRES page 2 graphics screen

// TODO: See if the program size is better controlled by prepopulating
// this line
static char *get_line_address(unsigned int y) {
    unsigned int line_num = y / 8;
    return APPLEII_HIRES_PAGE_2 
        + (line_num % 8 * 128 + line_num / 8 * 40)
        + y % 8 * 0x400;
}

void hires_clear() {
    for (unsigned int y = 0; y < 192; y++) {
        char *line_address = get_line_address(y);
        for (unsigned int i = 0; i < 40; i++) {
            line_address[i] = 0;
        }
    }
}

void hires_plot_on(unsigned int x, unsigned int y) {
    char *line_address = get_line_address(y);
    char *screen_byte = line_address + (x / 7);
    char plot_byte = 0x01 << (x % 7);
    *screen_byte |= plot_byte;
}

void hires_plot_off(unsigned int x, unsigned int y) {
    char *line_address = get_line_address(y);
    char *screen_byte = line_address + (x / 7);
    char plot_byte = 0xff ^ (0x01 << (x % 7));
    *screen_byte &= plot_byte;
}

void hires_plot_xor(unsigned int x, unsigned int y) {
    char *line_address = get_line_address(y);
    char *screen_byte = line_address + (x / 7);
    char plot_byte = 0x01 << (x % 7);
    *screen_byte ^= plot_byte;
}