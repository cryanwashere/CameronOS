#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "drivers/screen.h"


/* make sure the compiler does not think you are targeting the wrong operating system */
#if defined(__linux__)
#error "You are not using a cross compiler, you will most certainly run into trouble"
#endif

/* This will only work with 32-bit ix86 targets */
#if !defined(__i386__)
#error "This kernel needs to be compiled with an ix86-elf compiler"
#endif



/* functions for reading and writing to serial ports */
extern inline unsigned char inb (int portnum)
{
	unsigned char data=0;
  	__asm__ __volatile__ ("inb %%dx, %%al" : "=a" (data) : "d" (portnum));
  	return data;
}
extern inline void outb (int portnum, unsigned char data)
{
  	__asm__ __volatile__ ("outb %%al, %%dx" :: "a" (data),"d" (portnum));
}

/* initialize serial communication */
#define PORT 0x3f8
static int init_serial() {
	outb(PORT + 1, 0x00);	 // Disable all interrupts
	outb(PORT + 3, 0x80);	 // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);    //                  (hi byte)
	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
	outb(PORT + 0, 0xAE);    // Send a test byte
	
	// Check that we received the same test byte we sent
	if(inb(PORT + 0) != 0xAE) {
		return 1;
	}
	
	// If serial is not faulty set it in normal operation mode:
	// not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled
	outb(PORT + 4, 0x0F);
	return 0;
}


/*
typedef struct
{
    uint16_t address_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t address_mid;
    uint32_t address_high;
    uint32_t reserved;
} __attribute__((packed)) interrupt_descriptor;

// This is the interrupt descriptor table 
interrupt_descriptor idt[256];

// put an entry into the interrupt descriptor table 
void set_idt_entry(uint8_t vector, void* handler, uint8_t dpl)
{
	uint64_t handler_addr = (uint64_t)handler;

	interrupt_descriptor* entry = &idt[vector];
	entry->address_low = handler_addr & 0xFFFF;
	entry->address_mid = (handler_addr >> 16) & 0xFFFF;
	entry->address_high = handler_addr >> 32;
	entry->selector = 0x8;
	entry->flags = 0b1110 | ((dpl & 0b11) << 5) | (1 << 7);
	entry->ist = 0;
}

// Interrupt desriptor table register 
typedef struct
{
	uint16_t limit;
	uint64_t base;
} __attribute__((packed)) idtr;

// Load the interrupt descriptor table
void load_idt(void* idt_addr)
{
    idtr idt_reg;
    idt_reg.limit = 0xFFF;
    idt_reg.base = (uint64_t)idt_addr;
    asm volatile("lidt %0" :: "m"(&idt_reg));
}



// The keyboard buffer stores the characters that have been entered in the keyboard 
#define MAX_KEYBOARD_BUFFER_SIZE 255

uint8_t keyboard_buffer[MAX_KEYBOARD_BUFFER_SIZE];
uint8_t buf_position = 0;

// Handle an interrupt from the keyboard
void keyboard_driver_irq_handler()
{
	uint8_t scancode = inb(0x60);	// Read byte from the keyboard data port
	
	keyboard_buffer[buf_position] = scancode;
	buf_position = (buf_position + 1) % MAX_KEYBOARD_BUFFER_SIZE;	
}
*/


void kernel_main(void)
{
	/* Initialize the terminal interface */
	terminal_initialize();

	/* Write a message to the terminal */
	terminal_writestring("Welcome to CameronOS\n");

	int serial_status = init_serial();
	if (serial_status == 0) {
		terminal_writestring("Successfullly initialized serial communication\n");
		
	} else {
		terminal_writestring("Failed to initialize serial communiation\n");
	}
}
