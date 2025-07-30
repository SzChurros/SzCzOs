section .multiboot
align 4
    dd 0x1BADB002         ; Magic
    dd 0x00               ; Flags
    dd -(0x1BADB002 + 0)  ; Checksum

section .text
global start
start:
    extern kernel_main
    call kernel_main
    hlt