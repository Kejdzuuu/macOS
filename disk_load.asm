; load DH sectors to ES:BX from drive DL
disk_load:
    push  dx

    mov   ah, 0x2     ; BIOS read sector function
    mov   al, dh
    mov   ch, 0x0     ; Cylinder 0
    mov   dh, 0x0     ; Head 0
    mov   cl, 0x2     ; Start read from second sector (after boot sector)
    int   0x13        ; BIOS interrupt

    jc    disk_error

    pop   dx
    cmp   dh, al      ; if sectors read count not as expected
    jne   disk_error
    ret

  disk_error:
    mov   bx, DISK_ERROR_MSG
    call  print_string
    jmp   $

  ; Var
  DISK_ERROR_MSG:
    db "Disk read error!", 0

  DISK_ERROR_MSG2:
    db "sector count!", 0