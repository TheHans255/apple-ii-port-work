// Memory mapped locations for the Apple II

// Apple II keyboard data. If the high bit is set, then the
// lower seven bits contain the last key that was pressed
// since the keyboard strobe was cleared.
#define APPLEII_KEYBOARD_DATA ((volatile char *) 0xC000)
// Apple II keyboard strobe. Clear this to prepare to read
// the next key from the keyboard.
#define APPLEII_KEYBOARD_STROBE ((volatile char *) 0xC010)

// Turns on the Apple //e alternate character set.
// In this set, a character with its high bit cleared is
// the INVERSE version of the same character with the high
// bit set - FLASHING is removed.
#define APPLEIIE_ALTCHARSET_ON ((volatile void *) 0xC00F)
// Turns off the Apple //e alternate character set -
// the lower 128 characters is INVERSE and FLASHING
// uppercase characters.
#define APPLEIIE_ALTCHARSET_OFF ((volatile void *) 0xC00E)
// Reads the current state of the alternate character set switch
#define APPLEIIE_ALTCHARSET_READ ((volatile char *) 0xC01E)
// Disables graphics and displays full-screen text
#define APPLEII_TEXTMODE_TEXT ((volatile void *) 0xC051)
// Enables graphics
#define APPLEII_TEXTMODE_GRAPHICS ((volatile void *) 0xC050)
// Reads the current state of the text switch
// (high bit set = text, low bit set = graphics)
#define APPLEIIE_TEXTMODE_READ ((volatile char *) 0xC01A)
// Turns on the Apple II mixed mode - when graphics mode
// is enabled, the lower 4 lines of text will still appear.
// (This switch has no effect when graphics are disabled)
#define APPLEII_MIXEDMODE_ON ((volatile void *) 0xC053)
// Turns off the Apple II mixed mode - any active graphics mode
// will take up the entire screen
#define APPLEII_MIXEDMODE_OFF ((volatile void *) 0xC052)
// Reads the current state of the mixed mode switch
#define APPLEIIE_MIXEDMODE_READ ((volatile char *) 0xC01B)
// Enables Page 2 - all graphics and text will be taken
// from the alternate second page.
// If the 80STORE flag is set to AUX, this switch instead
// sets memory access to the buffers in the 80-column text card
#define APPLEII_PAGE_PAGE2 ((volatile void *) 0xC055)
// Enables Page 1 - all graphics and text will be taken
// from the default first page.
#define APPLEII_PAGE_PAGE1 ((volatile void *) 0xC054)
// Reads the current state of the page switch
#define APPLEIIE_PAGE_READ ((volatile char *) 0xC01C)
// Enables the Apple II HIRES graphics mode
#define APPLEII_HIRES_ON ((volatile void *) 0xC055)
// Disables the Apple II HIRES graphics mode
// (LORES graphics are displayed instead)
#define APPLEII_HIRES_OFF ((volatile void *) 0xC054)
// Reads the current state of the HIRES switch
#define APPLEIIE_HIRES_READ ((volatile char *) 0xC01D)
// Enables 80-column display on the Apple //e
#define APPLEIIE_80COLUMN_ON ((volatile void *) 0xC00D)
// Disables 80-column display on the Apple //e
#define APPLEIIE_80COLUMN_OFF ((volatile void *) 0xC00C)
// Reads the current state of the 80-column switch
#define APPLEIIE_80COLUMN_READ ((volatile char *) 0xC01F)
// Enables storing to the 80-column card auxillary memory
// on the Apple //e
#define APPLEIIE_80STORE_AUX ((volatile void *) 0xC001)
// Disables storing to the 80-column card auxillary memory
// on the Apple //e.
// (Note that this is write-only - reading this address
// yields keyboard data)
#define APPLEIIE_80STORE_MAIN ((volatile void *) 0xC000)
// Reads the current state of the 80STORE switch
#define APPLEIIE_80STORE_READ ((volatile char *) 0xC018)
// Reads the current state of VBlank on the Apple //e
// (if the bit is high, then the Apple is in VBlank)
#define APPLEIIE_VBLANK ((volatile char *) 0xC019)

// Turns the Annunciator 0 output off
#define APPLEII_ANNUNCIATOR0_OFF ((volatile void *) 0xC058)
// Turns the Annunciator 0 output on
#define APPLEII_ANNUNCIATOR0_ON ((volatile void *) 0xC059)
// Turns the Annunciator 1 output off
#define APPLEII_ANNUNCIATOR1_OFF ((volatile void *) 0xC05A)
// Turns the Annunciator 1 output on
#define APPLEII_ANNUNCIATOR1_ON ((volatile void *) 0xC05B)
// Turns the Annunciator 2 output off
#define APPLEII_ANNUNCIATOR2_OFF ((volatile void *) 0xC05C)
// Turns the Annunciator 2 output on
#define APPLEII_ANNUNCIATOR2_ON ((volatile void *) 0xC05D)
// Turns the Annunciator 3 output off
#define APPLEII_ANNUNCIATOR3_OFF ((volatile void *) 0xC05E)
// Turns the Annunciator 3 output on
#define APPLEII_ANNUNCIATOR3_ON ((volatile void *) 0xC05F)

// Clicks the Apple II speaker
#define APPLEII_SPEAKER_OUT ((volatile char *) 0xC030)
// Clicks the Apple II cassette output
#define APPLEII_CASSETTE_OUT ((volatile char *) 0xC020)
// Reads from the Apple II cassette input
#define APPLEII_CASSETTE_IN ((volatile char *) 0xC060)
// Outputs to the Apple II utility strobe
#define APPLEII_STROBE_OUT ((volatile void *) 0xC040)

// Reads the gamepad button 0 input
#define APPLEII_BUTTON_0 ((volatile char *) 0xC061)
// Reads the Open Apple key on the Apple //e keyboard
#define APPLEIIE_OPEN_APPLE ((volatile char *) 0xC061)
// Reads the gamepad button 1 input
#define APPLEII_BUTTON_1 ((volatile char *) 0xC062)
// Reads the Solid Apple key on the Apple //e keyboard
#define APPLEIIE_SOLID_APPLE ((volatile char *) 0xC062)
// Reads the gamepad button 2 input
#define APPLEII_BUTTON_2 ((volatile char *) 0xC063)

// Resets the analog timers on the four analog gamepad inputs
#define APPLEII_ANALOG_RESET ((volatile char *) 0xC070)
// Reads the gamepad analog 0 input.
// To read this input, first write to the APPLEII_ANALOG_RESET strobe,
// then track time until the high bit of this input turns off.
// The amount of time it takes to reach this (up to 3 milliseconds)
// is directly proportional to how far the analog input has advanced
// (from 0 Ohms to 150K ohms)
#define APPLEII_ANALOG_INPUT_0 ((volatile char *) 0xC064)
// Reads the gamepad analog 1 input.
// To read this input, first write to the APPLEII_ANALOG_RESET strobe,
// then track time until the high bit of this input turns off.
// The amount of time it takes to reach this (up to 3 milliseconds)
// is directly proportional to how far the analog input has advanced
// (from 0 Ohms to 150K ohms)
#define APPLEII_ANALOG_INPUT_1 ((volatile char *) 0xC065)
// Reads the gamepad analog 2 input.
// To read this input, first write to the APPLEII_ANALOG_RESET strobe,
// then track time until the high bit of this input turns off.
// The amount of time it takes to reach this (up to 3 milliseconds)
// is directly proportional to how far the analog input has advanced
// (from 0 Ohms to 150K ohms)
#define APPLEII_ANALOG_INPUT_2 ((volatile char *) 0xC066)
// Reads the gamepad analog 3 input.
// To read this input, first write to the APPLEII_ANALOG_RESET strobe,
// then track time until the high bit of this input turns off.
// The amount of time it takes to reach this (up to 3 milliseconds)
// is directly proportional to how far the analog input has advanced
// (from 0 Ohms to 150K ohms)
#define APPLEII_ANALOG_INPUT_3 ((volatile char *) 0xC067)
