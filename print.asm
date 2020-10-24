; prints a null-terminated string pointed to by BX
print_string:
    push  ax
    push  bx
    mov   ah, 0x0e
  loop_thru_msg:
    mov   al, [bx]
    cmp   al, 0
    je    print_done

    int   0x10
    inc   bx
    jmp   loop_thru_msg
  print_done:
    pop   bx
    pop   ax
    ret

; function prints DX register, uses buffer passed in BX
print_dx:
    push  bx
    push  dx
    push  ax
    push  cx

    add   bx, 5
    mov   cx, 4

  loop:
    cmp   cx, 0
    je    print_dx_exit
    mov   ax, dx
    and   ax, 0xF
    shr   dx, 4
    cmp   ax, 9
    jg    hex
  decimal:
    add   ax, '0'
    jmp   save
  hex:
    add   ax, 'A' - 0xA
  save:
    mov   [bx], al
    dec   bx
    dec   cx
    jmp   loop


  print_dx_exit:
    dec   bx
    call  print_string
    pop   cx
    pop   ax
    pop   dx
    pop   bx
    ret


[bits 32]
; Constants
VIDEO_MEMORY    equ 0xb8000
WHITE_ON_BLACK  equ 0x0f

; prints a null-terminated string pointed to by EDX
print_string_pm:
    pusha
    mov   edx, VIDEO_MEMORY     ; EDX point to video memory
    mov   ah, WHITE_ON_BLACK    ; Set text color

  print_string_pm_loop:
    mov   al, [ebx]             ; Store char in AL
    cmp   al, 0
    je    print_string_pm_done

    mov   [edx], ax             ; Store char and color in video memory
    inc   ebx                   ; Point to next char in string
    add   edx, 2                ; Point to next char cell in video memory

    jmp   print_string_pm_loop

  print_string_pm_done:
    popa
    ret
    