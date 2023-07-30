#include "apple-ii-monitor.h"

void appleii_cout(unsigned char c) {
    __attribute__((leaf)) asm volatile(
        "jsr\t0xfded" 
        : 
        : "a" (c)
        :);
}

unsigned char appleii_rdchar() {
    char c;
    __attribute__((leaf)) asm volatile("jsr\t0xfd35" 
    : "=a" (c)
    : 
    : "a", "y", "p");
    return c;
}