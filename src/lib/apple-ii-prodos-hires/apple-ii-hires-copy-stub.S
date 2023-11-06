; Start-of-program stub to copy a ProDOS program from $2000 to $6000

; Note that this code will be considered to begin at address $6000,
; even though it will actually be running at address $2000.
; This works just fine since the program uses entirely relative
; addressing until the final jump.

.section .apple_ii_hires_copy_stub,"aR",@progbits
  lda #$7e
  sta $1
  lda #$be
  sta $3
  lda #0
  sta $0
  sta $2
__copy_stub_loop_outer:
  ldy #0
__copy_stub_loop_inner:
  lda ($0),y
  sta ($2),y
  iny
  bne __copy_stub_loop_inner
  dec $3
  dec $1
  lda $1
  cmp #$20
  bcs __copy_stub_loop_outer
  jmp __copy_stub_end
__copy_stub_end:
