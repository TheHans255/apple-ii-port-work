#include <stdio.h>
#include "prodos-syscall.h"

char *PROGRAM_VERSION_NUMBER_LOCATION = (char *) 0xbffd;
volatile char *SYSTEM_BITMAP_LOCATION = (char *) 0xbf58;

static void print_system_bitmap() {
    // This program prints what's already in it so that we can inspect it
    for (unsigned int i = 0; i < 24; i += 2) {
        unsigned char bitmap1 = SYSTEM_BITMAP_LOCATION[i];
        unsigned char bitmap2 = SYSTEM_BITMAP_LOCATION[i + 1];
        printf("%04x: %02x%02x\n", i * 0x800, bitmap1, bitmap2);
    }
}

static void test_file_apis() {
    // NOTE: Normal ASCII is acceptable, but the string must be length-prefixed with a single byte
    // (Also, max pathnames are 64 characters)
    const char PATHNAME[] = {12, 'T', 'E', 'S', 'T', 'T', 'E', 'X', 'T', '.', 'T', 'X', 'T'};
    printf("Memory map before opening files:\n");
    print_system_bitmap();
    char ref_num;
    char error;
    if ((error = prodos_open((char *) PATHNAME, (char *) 0x6000, &ref_num))) {
        printf("Error opening: $%x\n", error);
        return;
    }
    printf("File opened with reference number %d\n", ref_num);
    char read_buffer[128];
    unsigned int read_count;
    if ((error = prodos_read(ref_num, read_buffer, 120, &read_count))) {
        printf("Error reading: $%x\n", error);
        return;
    }
    read_buffer[read_count] = '\0';
    printf("%s\n", read_buffer);
    getchar();
    printf("Memory map after reading, before closing:\n");
    print_system_bitmap();
    getchar();
    prodos_close(ref_num);
    printf("Memory map after closing:\n");
    print_system_bitmap();
    getchar();
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
    
    test_file_apis();
    getchar();

    return 0; 
}