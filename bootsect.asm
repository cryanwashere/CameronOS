


mov ah, 0x0e		; int 10/ah = 0eh -> scrolling teletype BIOS routine


mov bp, 0x8000		; Set the base of the stack above where BIOS loads the boot sector
mov sp, bp


print_function:
	mov ah, 0x0e
	int 0x10
	ret 


jmp $			; Jump to the current address

times 510-($-$$) db 0	; Pad the boot sector with zeros
dw 0xaa55		; last two bytes form the magic number, so BIOS knows that it is a 
			; boot sector

