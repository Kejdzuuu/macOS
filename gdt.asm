; Global Description Table
gdt_start:

gdt_null: ; null descriptor
  dd  0x0
  dd  0x0

gdt_code: ; code segment descriptor
  dw  0xffff      ; Limit (bits  0-15)
  dw  0x0         ; Base  (bits  0-15)
  db  0x0         ; Base  (bits 16-23)
                  ; Flags:
  db  10011010b   ;   Present: 1, Privilege: 00, Descriptor type: 1
                  ;   Type:
                  ;     Code: 1, Conforming: 0, Readable: 1, Accessed: 0
  db  11001111b   ;   Granularity: 1, 32-bit: 1, 64-bit: 0, AVL: 0
                  ; Limit (bits 16-19)
  db  0x0         ; Base  (bits 24-31)

gdt_data: ; data segment descriptor
  dw  0xffff      ; Limit (bits  0-15)
  dw  0x0         ; Base  (bits  0-15)
  db  0x0         ; Base  (bits 16-23)
                  ; Flags:
  db  10010010b   ;   Present: 1, Privilege: 00, Descriptor type: 1
                  ;   Type:
                  ;     Code: 0, Expand down: 0, Writeable: 1, Accessed: 0
  db  11001111b   ;   Granularity: 1, 32-bit: 1, 64-bit: 0, AVL: 0
                  ; Limit (bits 16-19)
  db  0x0         ; Base  (bits 24-31)

gdt_end:  ; label for GDT size calculation


; GDT descriptor
gdt_descriptor:
  dw  gdt_end - gdt_start - 1 ; Size of GDT
  dd  gdt_start               ; Address of GDT

CODE_SEG equ gdt_code - gdt_start ; Code segment address offset from GDT start
DATA_SEG equ gdt_data - gdt_start ; Data segment address offset from GDT start