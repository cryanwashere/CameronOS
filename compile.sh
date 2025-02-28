i686-elf-as boot.s -o boot.o
nasm cpu/interrupt.asm -f elf -o cpu/interrupt.o
i686-elf-gcc -c cpu/idt.c -o cpu/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c cpu/isr.c -o cpu/isr.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c cpu/timer.c -o cpu/timer.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c drivers/ports.c -o drivers/ports.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c kernel/kernel.c -o kernel/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c kernel/util.c -o kernel/util.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c drivers/screen.c -o drivers/screen.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o bin/CameronOS.bin -ffreestanding -O2 -nostdlib boot.o cpu/timer.o drivers/ports.o drivers/screen.o cpu/idt.o cpu/isr.o kernel/util.o kernel/kernel.o cpu/interrupt.o -lgcc
