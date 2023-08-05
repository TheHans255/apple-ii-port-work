#include "apple-ii-monitor.h"

void appleii_bell() { __attribute__((leaf)) asm volatile ("jsr 0xff3a": : : "a"); }

void appleii_bell1() { __attribute__((leaf)) asm volatile ("jsr 0xfbdd": : : "a", "x"); }

void appleii_clreol() { __attribute__((leaf)) asm volatile ("jsr 0xfc9c": : : "a", "y"); }

void appleii_cleolz() { __attribute__((leaf)) asm volatile ("jsr 0xfc9e": : : "a", "y"); }

void appleii_clreop() { __attribute__((leaf)) asm volatile ("jsr 0xfc42": : : "a", "y"); }

void appleii_cout(unsigned char c) { __attribute__((leaf)) asm volatile ("jsr 0xfded": : "a" (c) :); }

void appleii_cout1(unsigned char c) { __attribute__((leaf)) asm volatile ("jsr 0xfdf0": : "a" (c) :); }

void appleii_crout() { __attribute__((leaf)) asm volatile ("jsr 0xfd8e": : :); }

void appleii_crout1() { __attribute__((leaf)) asm volatile ("jsr 0xfd8b": : :); }

void appleii_home() { __attribute__((leaf)) asm volatile ("jsr 0xfc58": : :); }

void appleii_iorest() { __attribute__((leaf)) asm volatile ("jsr 0xff3f": : : "a", "x", "y", "p"); }

void appleii_iosave() { __attribute__((leaf)) asm volatile ("jsr 0xff4a": : : "a", "x"); }

void appleii_prbl2(unsigned char count) { __attribute__((leaf)) asm volatile ("jsr 0xf94a": : "x" (count) :); }

void appleii_prblnk() { __attribute__((leaf)) asm volatile ("jsr 0xf948": : : "a", "x"); }

void appleii_prbyte(unsigned char byte) { __attribute__((leaf)) asm volatile ("jsr 0xfdda": : "a" (byte) : "a"); }

void appleii_prerr() { __attribute__((leaf)) asm volatile ("jsr 0xff2d": : : "a"); }

void appleii_prhex(unsigned char nybble) { __attribute__((leaf)) asm volatile ("jsr 0xfde3": : "a" (nybble) : "a"); }

void appleii_prntax(unsigned int word) {
    unsigned char lo = word % 256;
    unsigned char hi = word / 256;
    __attribute__((leaf)) asm volatile ("jsr 0xf941": : "a" (hi), "x" (lo) : "a"); 
}

void appleii_setinv() { __attribute__((leaf)) asm volatile ("jsr 0xfe80": : : "y"); }

void appleii_setnorm() { __attribute__((leaf)) asm volatile ("jsr 0xfe84": : : "y"); }

void appleii_vtab(unsigned char line_number) { __attribute__((leaf)) asm volatile ("jsr 0xfc24": : "a" (line_number) :); }

unsigned char appleii_rdkey() { 
    unsigned char c;
    __attribute__((leaf)) asm volatile ("jsr 0xfd0c": "=a" (c) : :);
    return c;
}

unsigned char appleii_rdchar() { 
    unsigned char c;
    __attribute__((leaf)) asm volatile ("jsr 0xfd35": "=a" (c) : :);
    return c;
}

unsigned char appleii_keyin() {
    unsigned char c;
    __attribute__((leaf)) asm volatile ("jsr 0xfd1b": "=a" (c) : :);
    return c;
}

void appleii_getln(unsigned char *len, unsigned char **buf) {
    __attribute__((leaf)) asm volatile ("jsr 0xfd6a": "=x" (*len) : :); 
    *buf = APPLEII_MONITOR_INPUT_BUFFER;
}

void appleii_getlnz(unsigned char *len, unsigned char **buf) { 
    __attribute__((leaf)) asm volatile ("jsr 0xfd67": "=x" (*len) : :); 
    *buf = APPLEII_MONITOR_INPUT_BUFFER;
}

void appleii_getln1(unsigned char *len, unsigned char **buf) { 
    __attribute__((leaf)) asm volatile ("jsr 0xfd6f": "=x" (*len) : :); 
    *buf = APPLEII_MONITOR_INPUT_BUFFER;
}

void appleii_wait(unsigned char delay_time) { __attribute__((leaf)) asm volatile ("jsr 0xfca8": : "a" (delay_time) : "a"); }

void appleii_setpwrc() { __attribute__((leaf)) asm volatile ("jsr 0xfb6f": : : "a"); }

unsigned char appleii_pread(unsigned char index) {
    unsigned char result;
    __attribute__((leaf)) asm volatile ("jsr 0xfb1e": "=y" (result) : "x" (index) : "a");
    return result; 
}

unsigned char appleii_read(unsigned char *dest_start, unsigned char *dest_end) {
    *((unsigned char * * volatile) 0x3c) = dest_start;
    *((unsigned char * * volatile) 0x3e) = dest_end;
    __attribute__((leaf)) asm volatile ("jsr 0xfefd": : :); 
}

unsigned char appleii_write(unsigned char *src_start, unsigned char *src_end) {
    *((unsigned char * * volatile) 0x3c) = src_start;
    *((unsigned char * * volatile) 0x3e) = src_end;
    __attribute__((leaf)) asm volatile ("jsr 0xfecd": : :); 
}

void appleii_setcol(enum appleii_lores_color color) {
    unsigned char c = (unsigned char) color;
    __attribute__((leaf)) asm volatile ("jsr 0xf864": : "a" (c) :); 
}

void appleii_nextcol() { __attribute__((leaf)) asm volatile ("jsr 0xf85f": : :); }

void appleii_plot(unsigned char x, unsigned char y) { __attribute__((leaf)) asm volatile ("jsr 0xf800": : "a" (y), "y" (x) :); }

void appleii_hline(unsigned char x1, unsigned char x2, unsigned char y) { 
    *APPLEII_MONITOR_H2 = x2;
    __attribute__((leaf)) asm volatile ("jsr 0xf819": : "a" (y), "y" (x1) : "a", "y"); 
}

void appleii_vline(unsigned char x, unsigned char y1, unsigned char y2) { 
    *APPLEII_MONITOR_V2 = y2;
    __attribute__((leaf)) asm volatile ("jsr 0xf828": : "a" (y1), "y" (x) : "a", "y"); 
}

void appleii_clrscr() { __attribute__((leaf)) asm volatile ("jsr 0xf832": : : "a", "y"); }

void appleii_clrtop() { __attribute__((leaf)) asm volatile ("jsr 0xf836": : : "a", "y"); }

enum appleii_lores_color appleii_scrn(unsigned char x, unsigned char y) {
    unsigned char c;
    __attribute__((leaf)) asm volatile ("jsr 0xf871": "=a" (c) : "a" (y), "y" (x) :);
    return (enum appleii_lores_color) c;
}