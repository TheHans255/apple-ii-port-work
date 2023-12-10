#include "apple-ii-io.h"

void square_wave(unsigned int length, unsigned char wavelength) {

    unsigned char half_wavelength = wavelength / 2;
    unsigned char tweak_timer = 1;
    for (unsigned int t = 0; t < length; t++) {
        tweak_timer--;
        if (tweak_timer == 0) {
            tweak_timer = half_wavelength;
            char dummy = *APPLEII_SPEAKER_OUT;
        }
    }
}