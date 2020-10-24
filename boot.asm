; boot sector that enters 32-bit protected mode
[org 0x7c00]  ; boot sector is loaded to this address by bios

  mov   bp, 0x9000      ; Set stack
  mov   sp, bp

  mov   bx, BOOT_STRING
  call  print_string

  mov   bx, MSG_REAL_MODE
  call  print_string

  call  switch_to_pm

  jmp   $


%include "print.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "switch_to_protected.asm"

[bits 32]
; After switch to protected mode
BEGIN_PM:
  mov   ebx, MSG_PROT_MODE
  call  print_string_pm
  mov   eax, 0x12345678

  jmp   $

; Globals
BOOT_STRING     db  "Booting macOS...", 10, 13, 0
MSG_REAL_MODE   db  "16-bit mode", 0
MSG_PROT_MODE   db  "32-bit protected mode", 0

; Pad boot sector
times 510-($-$$)  db 0
dw  0xAA55
