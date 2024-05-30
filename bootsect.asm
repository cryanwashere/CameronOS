


mov ah, 0x0e		; int 10/ah = 0eh -> scrolling teletype BIOS routine

mov al, the_secret
int 0x10

mov al, [the_secret]
int 0x10


mov bx, the_secret
add bx, 0x7c00
mov al, [bx]
int 0x10

mov al, [0x7c1e]
int 0x10




jmp $			; Jump to the current address

the_secret:
	db "X"

times 510-($-$$) db 0	; Pad the boot sector with zeros
dw 0xaa55		; last two bytes form the magic number, so BIOS knows that it is a boot sector


