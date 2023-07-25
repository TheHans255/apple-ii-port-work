/* Apple //e ProDOS 2.4.2 Linked Script */

/* Available RAM goes from 0x0800 to 0xBF00.
 * The program is loaded at 0x2000, and the 6K
 * below that will be reserved for the soft stack.
 */
MEMORY { 
    ram (rw) : ORIGIN = 0x2000, LENGTH = 0x9F00
}



/* Use the first 32 bytes of zero page as imaginary registers.
 * Note that 0x20 thru 0x4F are used by the System Monitor
 * and ProDOS.
 */
__rc0 = 0x0000;
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x00, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

MEMORY { zp : ORIGIN = 0x0060, LENGTH = 0x0050 }

SECTIONS {
    INCLUDE c.ld
}

/* Set the operand stack to the 6K memory region behind our program */
__stack = 0x1fff;

OUTPUT_FORMAT { TRIM(ram) }