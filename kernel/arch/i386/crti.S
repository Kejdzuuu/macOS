.section .init
.global _init
.type _init, @function
_init:
    /* gcc will put crtbegin.o .init section here. */
    push  %ebp
    movl  %esp, %ebp

.section .fini
.global _fini
.type _fini, @function
_fini:
    /* gcc will put crtbegin.o .fini section here. */
    push  %ebp
    movl  %esp, %ebp