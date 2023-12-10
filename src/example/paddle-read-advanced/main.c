#include <stdio.h>
#include "apple-ii-monitor.h"
#include "apple-ii-io.h"

char *PROGRAM_VERSION_NUMBER_LOCATION = (char *) 0xbffd;

unsigned char paddle_state_binary_search(unsigned char *paddle_state, unsigned char len) {
    unsigned char hi = len;
    unsigned char lo = 0;
    while (hi > lo) {
        unsigned char mid = (hi - lo) / 2 + lo;
        if (paddle_state[mid] < 128) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

// Read the first two paddle inputs both at once
// returning each in a range of 0-128
// (this accounts for the fact that all paddle timers
// start at the same time and can end up crosstalking
// if read too close in succession)
void paddles_2(unsigned char *paddle_out) {
    // NOTE: This uses a good deal of excess memory.
    // IIRC, there's a routine in "Apple Graphics and Arcade Game Design"
    // that addresses this issue more intelligently.

    // Read the states of both paddle inputs in arrays,
    // capturing the state of both strobes up to 128 times
    static unsigned char paddle_state_0[128];
    static unsigned char paddle_state_1[128];
    char dummy = *APPLEII_ANALOG_RESET;
    for (unsigned char i = 0; i < 128; i++) {
        paddle_state_0[i] = *APPLEII_ANALOG_INPUT_0;
        paddle_state_1[i] = *APPLEII_ANALOG_INPUT_1;
    }
    paddle_out[0] = paddle_state_binary_search(paddle_state_0, 128);
    paddle_out[1] = paddle_state_binary_search(paddle_state_1, 128);
}

int main(void) {
    // Set the version number for ProDOS
    *PROGRAM_VERSION_NUMBER_LOCATION = 0x01;
    
    // Display the values of all four paddles until a key is pressed
    *APPLEII_KEYBOARD_STROBE = 0;
    while(*APPLEII_KEYBOARD_DATA < 128) {
        unsigned char paddle_timers[2];
        paddles_2(paddle_timers);
        // move display to top left corner
        *APPLEII_MONITOR_CH = 0;
        appleii_vtab(0);
        for (int i = 0; i < 2; i++) {
            printf("Paddle %d: %3d \n", i, paddle_timers[i]);
        }
    }

    return 0; 
}