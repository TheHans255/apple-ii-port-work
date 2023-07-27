; Core gadget for making syscalls to ProDOS
; Set the number and param variables, then call _prodos_syscall.
; Note that none of these symbols should be used
; outside of the module that calls _prodos_syscall.
.global _prodos_syscall
.global _prodos_syscall_number
.global _prodos_syscall_param

; NOTE: PC, S, D, I, RS0, and RS10-RS15 need to be saved by us
; according to LLVM-MOS's C calling convention:
; https://llvm-mos.org/wiki/C_calling_convention
; We don't use any of those, so we're good for now.

_prodos_syscall:
    jsr 0xBF00
_prodos_syscall_number:
    .byte 0x00
_prodos_syscall_param:
    .byte 0x00, 0x00
__prodos_syscall_end:
    rts