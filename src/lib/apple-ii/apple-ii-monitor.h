// COUT: Output an ASCII character to the current output device.
// (This expects the character to have its high bit set for normal output)
void appleii_cout(unsigned char c);
// RDCHAR: Wait for the next character to be returned from the current input device.
// (This typically returns the character with the high bit set)
unsigned char appleii_rdchar();
// VTAB: Set the current vertical position to the given absolute line number
// (Note that there is no HTAB because it can be set directly)
void appleii_vtab(unsigned char line_number);

// The horizontal location of the current character in video output
// (stored as a displacement from the left edge of the text window)
#define APPLEII_MONITOR_CH ((volatile unsigned char *) 0x24)
// The vertical location of the current character in video output
// (stored as an absolute screen line number)
// NOTE: This should be set by calling appleii_vtab instead
// of setting this variable directly.
#define APPLEII_MONITOR_CV ((volatile unsigned char *) 0x25)
