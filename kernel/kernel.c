#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"


/* make sure the compiler does not think you are targeting the wrong operating system */
#if defined(__linux__)
#error "You are not using a cross compiler, you will most certainly run into trouble"
#endif

/* This will only work with 32-bit ix86 targets */
#if !defined(__i386__)
#error "This kernel needs to be compiled with an ix86-elf compiler"
#endif



void kernel_main(void)
{
	/* Initialize the terminal interface */
	terminal_initialize();

	/* Write a message to the terminal */
	terminal_writestring("Welcome to CameronOS!\n");

	terminal_writestring("Attempting to load IDT table\n");

	isr_install();

	init_keyboard();
    /* Test the interrupts */
    //__asm__ __volatile__("int $2");
    //__asm__ __volatile__("int $3");

}
