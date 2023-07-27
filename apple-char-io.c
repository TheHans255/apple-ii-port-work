void __chrout(char c) {
    // Use COUT for character output
    __attribute__((leaf)) asm volatile(
        "jsr\t0xfded" 
        : 
        : "a" (c)
        :);
}

void __putchar(char c) {
  if (__builtin_expect(c == '\n', 0)) c = '\r';
  __chrout(c ^ -128);
}

char __chrin() {
    // Use RDCHAR for character input
    char c;
    __attribute__((leaf)) asm volatile("jsr\t0xfd35" 
    : "=a" (c)
    : 
    : "a", "y", "p");
    return c;
}

char getchar() {
    return __chrin();
}