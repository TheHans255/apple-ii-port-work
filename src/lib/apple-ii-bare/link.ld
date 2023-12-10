/* Apple //e Bare Deployment Linker Script */

/* Use the first 32 bytes of zero page as imaginary registers.
 */
__rc0 = 0x0000;
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x00, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

/* Available RAM goes from 0x0800 to 0xBFFF.
 * The program is loaded at 0x0800.
 */
/* TODO: If we can integrate Language Card activation, then the Language Card
 * RAM (0xD000-0xFFFF) can be used for auxilliary data and stack.
 * 0x200-0x3ff can also be used freely.
 */
MEMORY { 
    zp : ORIGIN = 0x0020, LENGTH = (0x0100 - 0x0020)
    ram (rw) : ORIGIN = 0x0800, LENGTH = 0xB800
}

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

/* Set the operand stack to the top of usable memory */
__stack = 0xbfff;

SECTIONS {
    INCLUDE c.ld
}

OUTPUT_FORMAT { 
    TRIM(ram)
}
