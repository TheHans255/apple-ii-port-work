.global _exit
_exit:
  jsr _fini
  dec 0x03f4
  jsr 0xbf00
  .byte 0x65
  .word QUIT_PARAMS
QUIT_PARAMS:
  .byte 4 ; 4 parameters
  .byte 0 ; 0 is the only quit type
  .word 0 ; Reserved
  .byte 0 ; Reserved
  .word 0 ; Reserved
