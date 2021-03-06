/*.intel_syntax noprefix */
/* Multiboot header constants */
.set ALIGN,     1<<0                /* align loaded modules on page boundries */
.set MEMINFO,   1<<1                /* memory map */
.set FLAGS,     ALIGN | MEMINFO     /* multiboot flag field */
.set MAGIC,     0x1BADB002          /* magic number for bootloader */
.set CHECKSUM,  -(MAGIC + FLAGS)    /* checksum */


/* Declare a multiboot header */
.section .multiboot
.align  4
.long   MAGIC
.long   FLAGS
.long   CHECKSUM

/* Reserve a stack */
.section .bss
.align  16
stack_bottom:
.skip   16384 # 16 KiB
stack_top:

/* Kernel entry point */
.section .text
.global _start
.type _start, @function
_start:
    /* The bootloader has loaded us into 32-bit protected mode */
  
    /* We set the esp register to point to the top of the stack */
    movl $stack_top, %esp
  
    /*
    This is a good place to initialize crucial processor state before the
    high-level kernel is entered. It's best to minimize the early
    environment where crucial features are offline. Note that the
    processor is not fully initialized yet: Features such as floating
    point instructions and instruction set extensions are not initialized
    yet. The GDT should be loaded here. Paging should be enabled here.
    C++ features such as global constructors and exceptions will require
    runtime support to work as well.
    */

    /* Calling global constructors */
    call _init
  
    /* Transfering control to kernel */
    call kernel_main
  
    /* Hang if kernel unexpectedly returns */
    cli
1:	
    hlt
	jmp 1b


/* Set up GDT */
.global gdt_flush
.extern gdt_ptr
gdt_flush:
  lgdt  gdt_ptr
  ljmpl $0x08,$seg_reg_flush  /* load code GDT entry to cs register */
seg_reg_flush:
  mov $0x10,  %ax           /* load data GDT entry to registers */
  mov %ax, %ds        
  mov %ax, %es
  mov %ax, %gs
  mov %ax, %fs
  mov %ax, %ss
  ret

/* Load page directory */
.global load_page_directory
load_page_directory:
  push  %ebp
  mov   %esp, %ebp
  mov   8(%esp), %eax
  mov   %eax, %cr3
  mov   %ebp, %esp
  pop   %ebp
  ret

/* Enable paging */
.global paging_start
paging_start:
  mov %cr0, %eax
  or  $0x80000000, %eax
  mov %eax, %cr0
  ret

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start
