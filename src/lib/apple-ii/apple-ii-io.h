// Memory mapped locations for the Apple II

#ifndef __APPLE_II_IO
#define __APPLE_II_IO

// Apple II keyboard data. If the high bit is set, then the
// lower seven bits contain the last key that was pressed
// since the keyboard strobe was cleared.
#define APPLEII_KEYBOARD_DATA ((volatile char *) 0xC000)
// Apple II keyboard strobe. Clear this to prepare to read
// the next key from the keyboard.
#define APPLEII_KEYBOARD_STROBE ((volatile char *) 0xC010)

// Disables graphics and displays full-screen text
#define APPLEII_TEXTMODE_TEXT ((volatile char *) 0xC051)
// Enables graphics
#define APPLEII_TEXTMODE_GRAPHICS ((volatile char *) 0xC050)
// Turns on the Apple II mixed mode - when graphics mode
// is enabled, the lower 4 lines of text will still appear.
// (This switch has no effect when graphics are disabled)
#define APPLEII_MIXEDMODE_ON ((volatile char *) 0xC053)
// Turns off the Apple II mixed mode - any active graphics mode
// will take up the entire screen
#define APPLEII_MIXEDMODE_OFF ((volatile char *) 0xC052)
// Enables Page 2 - all graphics and text will be taken
// from the alternate second page.
// If the 80STORE flag is set to AUX, this switch instead
// sets memory access to the buffers in the 80-column text card
#define APPLEII_PAGE_PAGE2 ((volatile char *) 0xC055)
// Enables Page 1 - all graphics and text will be taken
// from the default first page.
#define APPLEII_PAGE_PAGE1 ((volatile char *) 0xC054)
// Enables the Apple II HIRES graphics mode
#define APPLEII_HIRES_ON ((volatile char *) 0xC055)
// Disables the Apple II HIRES graphics mode
// (LORES graphics are displayed instead)
#define APPLEII_HIRES_OFF ((volatile char *) 0xC054)

// Turns the Annunciator 0 output off
#define APPLEII_ANNUNCIATOR0_OFF ((volatile char *) 0xC058)
// Turns the Annunciator 0 output on
#define APPLEII_ANNUNCIATOR0_ON ((volatile char *) 0xC059)
// Turns the Annunciator 1 output off
#define APPLEII_ANNUNCIATOR1_OFF ((volatile char *) 0xC05A)
// Turns the Annunciator 1 output on
#define APPLEII_ANNUNCIATOR1_ON ((volatile char *) 0xC05B)
// Turns the Annunciator 2 output off
#define APPLEII_ANNUNCIATOR2_OFF ((volatile char *) 0xC05C)
// Turns the Annunciator 2 output on
#define APPLEII_ANNUNCIATOR2_ON ((volatile char *) 0xC05D)
// Turns the Annunciator 3 output off
#define APPLEII_ANNUNCIATOR3_OFF ((volatile char *) 0xC05E)
// Turns the Annunciator 3 output on
#define APPLEII_ANNUNCIATOR3_ON ((volatile char *) 0xC05F)

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
// Reads the gamepad button 1 input
#define APPLEII_BUTTON_1 ((volatile char *) 0xC062)
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

// The 1K memory region for the primary Apple II text or LORES Graphics page
#define APPLEII_TEXT_PAGE_1 ((char *) 0x0400)
// The 1K memory region for the secondary Apple II text or LORES Graphics page.
// Note that this memory region is also usually the first part of a BASIC
// program and hence needs special care to use
#define APPLEII_TEXT_PAGE_2 ((char *) 0x0800)
// The 8K memory region for the first HIRES graphics page
#define APPLEII_HIRES_PAGE_1 ((char *) 0x2000)
// The 8K memory region for the second HIRES graphics page
#define APPLEII_HIRES_PAGE_2 ((char *) 0x4000)

#endif // __APPLE_II_IO