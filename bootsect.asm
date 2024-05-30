


mov ah, 0x0e

mov al, 'H'
int 0x10
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10 
mov al, 'l' 
int 0x10 
mov al, 'o' 
int 0x10

jmp $			; Jump to the current address



times 510-($-$$) db 0	; Pad the boot sector with zeros

dw 0xaa55		; last two bytes form the magic number, so BIOS knows that it is a boot sector


