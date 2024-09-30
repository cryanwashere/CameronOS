C_SOURCES = $(wildcard kernel.c drivers/*.c cpu/*.c)
HEADERS   = $(wildcard drivers/*.h cpu/*.h)

C_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Generic ruls for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS}





%.o: %.asm: 
	nasm $< -f -elf -o $@	