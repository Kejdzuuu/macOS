[bits 16]
; Switch to protected mode

switch_to_pm:
  cli                     ; Switch off interrupts until a new vector table is set up

  lgdt  [gdt_descriptor]  ; Load GDT

  mov   eax, cr0          ; Set first bit of control register CR0
  or    eax, 0x1
  mov   cr0, eax

  jmp   CODE_SEG:init_pm  ; Far jump to 32-bit code to force CPU to flush the cache
                          ; from real-mode instructions
  
[bits 32]
; Initialize registers and stack in protected mode
init_pm:

  mov   ax, DATA_SEG      ; Point segment registers to the data segment
  mov   ds, ax
  mov   ss, ax
  mov   es, ax
  mov   fs, ax
  mov   gs, ax

  mov   ebp, 0x90000      ; Point stack pointers to the top of free space
  mov   esp, ebp

  call  BEGIN_PM
