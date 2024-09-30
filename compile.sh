i686-elf-as boot.s -o boot.o
nasm cpu/interrupt.asm -f elf -o cpu/interrupt.o
i686-elf-gcc -c cpu/idt.c -o cpu/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c cpu/isr.c -o cpu/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c kernel/kernel.c -o kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c drivers/screen.c -o drivers/screen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o CameronOS.bin -ffreestanding -O2 -nostdlib boot.o kernel/kernel.o drivers/screen.o cpu/idt.o cpu/isr.o cpu/interrupt.o -lgcc
