#include <stdio.h>
char __getchar();

char *PROGRAM_VERSION_NUMBER_LOCATION = (char *) 0xbffd;
char *SYSTEM_BITMAP_LOCATION = (char *) 0xbf58;

// TODO: You've broken varargs somehow! Congratulations!
// See what you can do to get them working again:
// - You know it's something specifically wrong with your setup.
//   Running the same functions (including print_hex_byte) in
//   the 6502 simulator does cause them to work correctly.

__attribute__((noinline))
static void print_hex_byte(unsigned char x) {
    unsigned char hi = x / 16;
    hi += (hi < 10 ? '0' : 'a' - 10);
    putchar(hi);
    unsigned char lo = x % 16;
    lo += (lo < 10 ? '0' : 'a' - 10);
    putchar(lo);
}

__attribute__((noinline))
static void print_hex_word(unsigned int x) {
    print_hex_byte(x / 256);
    print_hex_byte(x % 256);
}

static void print_system_bitmap() {
    // This program prints what's already in it so that we can inspect it
    for (unsigned int i = 0; i < 24; i++) {
        unsigned char bitmap = SYSTEM_BITMAP_LOCATION[i];
        print_hex_word(i * 0x800);
        putchar(':');
        putchar(' ');
        print_hex_byte(bitmap);
        putchar('\n');
        __getchar();
    }
}

static void print_fibonacci() {
    unsigned long a = 0;
    unsigned long b = 1;
    print_hex_word(a);
    putchar('\n');
    print_hex_word(b);
    putchar('\n');
    for (int i = 0; i < 30; i++) {
        unsigned long c = a + b;
        print_hex_word(c);
        putchar('\n');
        a = b;
        b = c; 
    }
}

// expect a pointer to address 0x2000
static void var_args_test_1(const char *x, ...) {
    va_list argp;
    va_start(argp, x);
    void *i = va_arg(argp, void *);
    print_hex_word((unsigned int) i);
    putchar('\n');
    va_end(argp);
}

// expect two pointers, one to address 0x3000, one to address 0x3001
static void var_args_test_2(const char *x, ...) {
    va_list argp;
    va_start(argp, x);
    void *i = va_arg(argp, void *);
    print_hex_word((unsigned int) i);
    putchar('\n');
    void *j = va_arg(argp, void *);
    print_hex_word((unsigned int) j);
    putchar('\n');
    va_end(argp);
}

// expect two characters, each of which is printed
static void var_args_test_3(const char *x, ...) {
    va_list argp;
    va_start(argp, x);
    int i = va_arg(argp, int);
    putchar(i);
    putchar('\n');
    int j = va_arg(argp, int);
    putchar(j);
    putchar('\n');
    va_end(argp);
}

// expect a pointer 0x3080, a character 'x', and a pointer 0x4060
static void var_args_test_4(const char *x, ...) {
    va_list argp;
    va_start(argp, x);
    void *i = va_arg(argp, void *);
    print_hex_word((unsigned int) i);
    putchar('\n');
    int j = va_arg(argp, int);
    putchar(j);
    putchar('\n');
    void *k = va_arg(argp, void *);
    print_hex_word((unsigned int) k);
    putchar('\n');
    va_end(argp);
}

static void varargs_tests() {
    var_args_test_1("1", (void *) 0x2000);
    var_args_test_2("2", (void *) 0x3000, (void *) 0x3001);
    var_args_test_3("3", 'a', 'b');
    var_args_test_4("4", (void *) 0x3080, 'x', (void *) 0x4060);
}

int main(void) {
    // Set the version number for ProDOS
    *PROGRAM_VERSION_NUMBER_LOCATION = 0x01;
    // TODO: As our test confirms, set the system bitmap to signify the pages
    // that you want to use. This should be done in two locations:
    // 1. At the start of the program's bookkeeping (next to setting the version number).
    //    The program needs to have material access to the value of _end
    //    in order to set page values (though note that we need to start from
    //    0x800, since we're using that for our stack), and it also needs to
    //    include uninitialized static variables.
    // 2. During calls to morecore(). If we end up writing some sort of dynamic
    //    memory allocator, it should consult with the ProDOS bitmap to figure out
    //    where to allocate values.
    // 3. If we enable the HIRES graphics pages - simply black out those bits
    //    and also ensure that /RAM is protected.
    
    varargs_tests();
    __getchar();
    return 0; 
}