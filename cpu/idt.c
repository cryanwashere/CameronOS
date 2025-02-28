#include "idt.h"
#include "types.h"
#include <stdint.h>
#include "../drivers/screen.h"



// This is where we declare the IDT
interrupt_gate_t idt[256];
// create the pointer of the IDT
idtr idt_reg; 



// Get the high and low offsets from an address
#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)


// put an entry into the interrupt descriptor table 
void set_idt_entry(int n, void * handler)
{
	
	

	// convert the address of the handler function to u32
	u32 handler_addr = (u32) handler;

	// set the IDT gate
	idt[n].low_offset = low_16(handler_addr);
	idt[n].sel = KERNEL_CS;
	idt[n].always0 = 0;
	idt[n].flags = 0x8E;
	idt[n].high_offset = high_16(handler_addr);

	
}


// Load the interrupt descriptor table
void load_idt()
{	
	// idt_reg is declared in idt.h
    idt_reg.limit = 256 * sizeof(interrupt_gate_t) - 1;
    idt_reg.base = (u32) &idt;
    //asm volatile("lidt %0" :: "m"(&idt_reg));
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
	terminal_writestring("(load_idt) finished loading IDT\n");
}
