// COUT: Output an ASCII character to the current output device.
// (This expects the character to have its high bit set for normal output)
void appleii_cout(unsigned char c);
// RDCHAR: Wait for the next character to be returned from the current input device.
// (This typically returns the character with the high bit set)
unsigned char appleii_rdchar();