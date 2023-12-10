// Memory mapped locations for the Apple //e?

#ifndef __APPLE_IIE_IO
#define __APPLE_IIE_IO

// Turns on the Apple //e alternate character set.
// In this set, a character with its high bit cleared is
// the INVERSE version of the same character with the high
// bit set - FLASHING is removed.
#define APPLEIIE_ALTCHARSET_ON ((volatile char *) 0xC00F)
// Turns off the Apple //e alternate character set -
// the lower 128 characters is INVERSE and FLASHING
// uppercase characters.
#define APPLEIIE_ALTCHARSET_OFF ((volatile char *) 0xC00E)
// Reads the current state of the alternate character set switch
#define APPLEIIE_ALTCHARSET_READ ((volatile char *) 0xC01E)

// Reads the current state of the text switch
// (high bit set = text, low bit set = graphics)
#define APPLEIIE_TEXTMODE_READ ((volatile char *) 0xC01A)
// Reads the current state of the mixed mode switch
#define APPLEIIE_MIXEDMODE_READ ((volatile char *) 0xC01B)
// Reads the current state of the page switch
#define APPLEIIE_PAGE_READ ((volatile char *) 0xC01C)
// Reads the current state of the HIRES switch
#define APPLEIIE_HIRES_READ ((volatile char *) 0xC01D)

// Enables 80-column display on the Apple //e
#define APPLEIIE_80COLUMN_ON ((volatile char *) 0xC00D)
// Disables 80-column display on the Apple //e
#define APPLEIIE_80COLUMN_OFF ((volatile char *) 0xC00C)
// Reads the current state of the 80-column switch
#define APPLEIIE_80COLUMN_READ ((volatile char *) 0xC01F)
// Enables storing to the 80-column card auxillary memory
// on the Apple //e
#define APPLEIIE_80STORE_AUX ((volatile char *) 0xC001)
// Disables storing to the 80-column card auxillary memory
// on the Apple //e.
// (Note that this is write-only - reading this address
// yields keyboard data)
#define APPLEIIE_80STORE_MAIN ((volatile char *) 0xC000)
// Reads the current state of the 80STORE switch
#define APPLEIIE_80STORE_READ ((volatile char *) 0xC018)
// Reads the current state of VBlank on the Apple //e
// (if the bit is high, then the Apple is in VBlank)
#define APPLEIIE_VBLANK ((volatile char *) 0xC019)

// Reads the Open Apple key on the Apple //e keyboard
#define APPLEIIE_OPEN_APPLE ((volatile char *) 0xC061)
// Reads the Solid Apple key on the Apple //e keyboard
#define APPLEIIE_SOLID_APPLE ((volatile char *) 0xC062)

#endif