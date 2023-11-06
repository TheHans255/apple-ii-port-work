/* Apple //e ProDOS 2.4.2 Linked Script */

/* Use the first 32 bytes of zero page as imaginary registers.
 * Note that 0x20 thru 0x4F are used by the System Monitor
 * and ProDOS.
 */
__rc0 = 0x0000;
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x00, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

/* Available RAM goes from 0x0800 to 0xBF00.
 * The program is loaded at 0x2000, and the 6K below is
 * used for the soft stack.
 * Zero page is available from 0x50 to the end 
 * (0x3A to 0x4F is reserved by ProDOS).
 */
MEMORY { 
    zp : ORIGIN = 0x0050, LENGTH = (0x1000 - 0x0050)
    ram (rw) : ORIGIN = 0x6000, LENGTH = 0x5F00
}

INPUT(apple-ii-hires-copy-stub.o)

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

/* Set the operand stack to the top of usable memory */
__stack = 0xbf00;

SECTIONS {
    .apple_ii_hires_copy_stub : { *(.apple_ii_hires_copy_stub) }

    INCLUDE c.ld
}

OUTPUT_FORMAT { 
    TRIM(ram)
}
