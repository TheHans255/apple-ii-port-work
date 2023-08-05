#ifndef __APPLE_II_MONITOR
#define __APPLE_II_MONITOR

// The top of the text window. Should range from 0 to 39 inclusive
#define APPLEII_MONITOR_WNDLFT ((volatile unsigned char *) 0x20)
// The width of the text window. This plus WNDLFT
// should not exceed 40.
#define APPLEII_MONITOR_WNDWDTH ((volatile unsigned char *) 0x21)
// The top line of the text window. Should range from 0 to 23 inclusive.
#define APPLEII_MONITOR_WNDTOP ((volatile unsigned char *) 0x22)
// The bottom line of the text window. Should range from 0 to 23 inclusive
// and should not be less than WNDTOP
#define APPLEII_MONITOR_WNDBTM ((volatile unsigned char *) 0x23)
// The horizontal location of the current character in video output
// (stored as a displacement from the left edge of the text window)
#define APPLEII_MONITOR_CH ((volatile unsigned char *) 0x24)
// The vertical location of the current character in video output
// (stored as an absolute screen line number)
// NOTE: This should be set by calling VTAB instead
// of setting this variable directly.
#define APPLEII_MONITOR_CV ((volatile unsigned char *) 0x25)
// The start of the current text line (normally set by text routines)
#define APPLEII_MONITOR_BAS ((volatile unsigned char * volatile *) 0x28)
// Second horizontal coordinate used for HLINE
// (set automatically by appleii_hline)
#define APPLEII_MONITOR_H2 ((volatile unsigned char *) 0x2c)
// Second horizontal coordinate used for VLINE
// (set automatically by appleii_hline)
#define APPLEII_MONITOR_V2 ((volatile unsigned char *) 0x2d)
// LORES color mask (set by SETCOL)
#define APPLEII_MONITOR_COLOR ((volatile unsigned char *) 0x30)
// Prompt character used by GETLN
#define APPLEII_MONITOR_PROMPT ((volatile unsigned char *) 0x33)
// A pointer to the routine for outputting characters to the current
// output device. This function should be called with the character
// in the accumulator with the high bit set
#define APPLEII_MONITOR_CSW ((void * * volatile) 0x36)
// A pointer to the routine for reading characters from the current
// input device. This function should return the read character
// in the accumulator.
#define APPLEII_MONITOR_KSW ((void * * volatile) 0x38)
// The current random number seed, incremented by KEYIN
#define APPLEII_MONITOR_RND ((volatile unsigned int *) 0x4e)

// The storage location for the input buffer written by GETLN
// (Note that appleii_getln returns this buffer pointer for you)
#define APPLEII_MONITOR_INPUT_BUFFER ((volatile unsigned char *) 0x200)

// The vector to jump to for BRK instructions
#define APPLEII_MONITOR_BRK_VECTOR ((void * * volatile) 0x3f0)
// The vector to jump to when the RESET key is pressed
#define APPLEII_MONITOR_RESET_VECTOR ((void * * volatile) 0x3f2)
// The "powerup byte" for validating the reset vector.
// If this value is not correct, the Apple II will initiate a cold start
// when the RESET key is pressed. The value can be set by calling
// SETPWRC.
#define APPLEII_MONITOR_POWERUP_BYTE ((volatile unsigned char *) 0x3f4)
// The vector to jump to for Non-Maskable Interrupts (NMI).
#define APPLEII_MONITOR_NMI_VECTOR ((void * * volatile) 0x3fb)
// The vector to jump to for Interrupt ReQuests (IRQ).
#define APPLEII_MONITOR_IRQ_VECTOR ((void * * volatile) 0x3fe)

// BELL: Print a BELL character to the current output device
void appleii_bell();
// BELL1: Send a beep to the speaker (that 1 KHz square wave we all love)
void appleii_bell1();
// CLREOL: Clear from the cursor to the end of the text line
void appleii_clreol();
// CLEOLZ: Clear from the location given by BAS to the end of the line
void appleii_cleolz();
// CLREOP: Clear from the cursor to the end of the text window
void appleii_clreop();
// COUT: Output an ASCII character to the current output device.
// (This expects the character to have its high bit set for normal output)
void appleii_cout(unsigned char c);
// COUT1: Output an ASCII character to the built-in 40-character terminal
// (with high bit set)
void appleii_cout1(unsigned char c);
// CROUT: Output a carriage return to the current output device
void appleii_crout();
// CROUT1: Calls CLREOL, then CROUT
void appleii_crout1();
// HOME: Clear the entire text window and put the cursor in the
// upper-left corner
void appleii_home();
// IOREST: Restore A, X, Y, P, and S from locations $45 through $49.
// (Note that many monitor routines use this, so do not rely on it to save registers)
void appleii_iorest();
// IOSAVE: Save A, X, Y, P, and S to locations $45 through $49.
// (Note that many monitor routines use this, so do not rely on it to save registers)
void appleii_iosave();
// PRBL2: Print the given number of blanks to the current output device.
// If 0 is passed in, this prints 256 blanks.
void appleii_prbl2(unsigned char count);
// PRBLNK: Print three blanks to the current output device
void appleii_prblnk();
// PRBYTE: Print a hexadecimal byte
void appleii_prbyte(unsigned char byte);
// PRERR: Prints the word "ERR", followed by a bell character,
// to the current output device.
void appleii_prerr();
// PRHEX: Print a hexadecimal digit
void appleii_prhex(unsigned char nybble);
// PRNTAX: Print a four-digit hexadecimal word
// (so named because it prints the contents of A and X)
void appleii_prntax(unsigned int word);
// SETINV: Causes all characters printed by COUT1 to be inverse
// (black text on white background)
void appleii_setinv();
// SETNORM: Causes all characters printed by COUT1 to appear normally
// (white text on black background)
void appleii_setnorm();
// VTAB: Set the current vertical position to the given absolute line number
// (Note that there is no HTAB because it can be set directly)
void appleii_vtab(unsigned char line_number);

// RDKEY: Read a character from the current input device, inserting a
// blinking cursor at the cursor location.
unsigned char appleii_rdkey();
// RDCHAR: Read a character from the current input device. This performs
// the functions of RDKEY and also interprets the eleven escape codes
// that allow access to cursor and screen control routines.
unsigned char appleii_rdchar();
// KEYIN: Read a character from the builtin keyboard, returning when a
// key is pressed. Also increments the RAND seed stored at 0x4e-0x4f.
unsigned char appleii_keyin();
// GETLN: Get a line of input with prompt.
// The prompt character is stored in APPLEII_MONITOR_PROMPT.
// Returns the length of the input line and its start location
// (which is always 0x200)
void appleii_getln(unsigned char *len, unsigned char **buf);
// GETLNZ: Get a line of input with prompt after printing a CR.
// The prompt character is stored in APPLEII_MONITOR_PROMPT (0x33).
// Returns the length of the input line and its start location
// (which is always 0x200)
void appleii_getlnz(unsigned char *len, unsigned char **buf);
// GETLN1: Get a line of input with no prompt.
// Returns the length of the input line and its start location
// (which is always 0x200)
void appleii_getln1(unsigned char *len, unsigned char **buf);

// WAIT: Delays for a specified amount of time.
// The delay time is (26 + 27A + 5A^2)/2 microseconds,
// where A is the given input.
void appleii_wait(unsigned char delay_time);
// SETPWRC: Sets the POWERUP_BYTE to the correct value
void appleii_setpwrc();

// PREAD: Read the given paddle input, returning an analog value from 0 to 255.
// Index should be between 0 to 3, or the behavior is undefined.
unsigned char appleii_pread(unsigned char index);

// READ: Read a range of data from the cassette player previously written by WRITE
unsigned char appleii_read(unsigned char *dest_start, unsigned char *dest_end);
// WRITE: Write a range of data to the cassette player
unsigned char appleii_write(unsigned char *src_start, unsigned char *src_end);

// The 16 colors available in LORES graphics
enum appleii_lores_color { LORES_BLACK, LORES_MAGENTA, LORES_DARK_BLUE, LORES_PURPLE,
  LORES_DARK_GREEN, LORES_GREY_1, LORES_MEDIUM_BLUE, LORES_LIGHT_BLUE,
  LORES_BROWN, LORES_ORANGE, LORES_GREY_2, LORES_PINK,
  LORES_LIGHT_GREEN, LORES_YELLOW, LORES_AQUAMARINE, LORES_WHITE };

// SETCOL: Set the color for future LORES graphics operations
void appleii_setcol(enum appleii_lores_color color);
// NEXTCOL: Adds 3 to the current color (set by SETCOL)
void appleii_nextcol();
// PLOT: Plot a single point on the LORES screen.
void appleii_plot(unsigned char x, unsigned char y);
// HLINE: Draw a horizontal line of blocks on the LORES screen,
// using the color previously set by SETCOL
void appleii_hline(unsigned char x1, unsigned char x2, unsigned char y);
// VLINE: Draw a vertical line of blocks on the LORES screen,
// using the color previously set by SETCOL
void appleii_vline(unsigned char x, unsigned char y1, unsigned char y2);
// CLRSCR: Clear the entire LORES screen to black, including the lower
// 8 lines.
void appleii_clrscr();
// CLRTOP: Clear the top 40 lines of the LORES screen to black (leaving
// the bottom 4 text lines visible in mixed mode)
void appleii_clrtop();
// SCRN: Read the color at the given position in the LORES screen
enum appleii_lores_color appleii_scrn(unsigned char x, unsigned char y);

// NOTE: Subroutines not included:
// - MOVE (because we already have a compiler intrinsic for it)
// - VERIFY (because it outputs to the compiler)

#endif // not __APPLE_II_MONITOR