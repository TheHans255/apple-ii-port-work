#include <stdio.h>

char *PROGRAM_VERSION_NUMBER_LOCATION = (char *) 0xbffd;
char *SYSTEM_BITMAP_LOCATION = (char *) 0xbf58;

static void print_system_bitmap() {
    // This program prints what's already in it so that we can inspect it
    for (unsigned int i = 0; i < 24; i++) {
        unsigned char bitmap = SYSTEM_BITMAP_LOCATION[i];
        printf("%04x: %02x\n", i * 0x800, bitmap);
        getchar();
    }
}

static void print_fibonacci() {
    unsigned long a = 0;
    unsigned long b = 1;
    printf("%ld\n", a);
    printf("%ld\n", b);
    for (int i = 0; i < 30; i++) {
        unsigned long c = a + b;
        printf("%ld\n", c);
        a = b;
        b = c; 
    }
}

static unsigned long next = 1;
const unsigned long RAND_MAX = 65535;
int rand() {
    return ((next = next * 1103515245 + 12345) % ((unsigned long )RAND_MAX + 1));
}
void srand(unsigned int seed) {
    next = seed;
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
    
    print_fibonacci();
    getchar();
    print_system_bitmap();
    getchar();

    return 0; 
}