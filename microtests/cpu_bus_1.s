.include "header.inc"

main:
//-   jr -
  ld a, $55
  ld hl, $C003
- ld (hl), a
  jr -



/*
  ld a, 0
  ld ($FF40),a

  jp $7000

  ld hl, $F000

  ld a, $77  // ld (hl),a
  ld (hl+), a

  ld a, $18 // jr
  ld (hl+), a
  ld a, $FD // -3
  ld (hl+), a

  ld a, $88
  ld hl, $F010
  jp $F000
*/
