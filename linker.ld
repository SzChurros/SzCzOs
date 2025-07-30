ENTRY(kernel_main)  /* Entry point = kernel_main() */

SECTIONS {
    . = 0x100000;  /* Kernel loads at 1MB (GRUB convention) */
    .text : { *(.text) }  /* Code */
    .data : { *(.data) }  /* Initialized data */
    .bss  : { *(.bss)  }  /* Uninitialized data */
}