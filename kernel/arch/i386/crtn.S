.section .init
  /* gcc will put crtend.o .init section here */
  popl  %ebp
  ret

.section .fini
  /* gcc will put crtend.o .fini section here */
  poplp %ebp
  ret