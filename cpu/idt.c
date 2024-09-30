#include "idt.h"
#include <stdint.h>
#include "../drivers/screen.h"


// This is the interrupt descriptor table. It contains 256 entries.
interrupt_descriptor idt[256];


// put an entry into the interrupt descriptor table 
void set_idt_entry(uint8_t vector, void* handler)
{
	
	//uint8_t dpl = 0;

	// convert the address of the handler function
	uint64_t handler_addr = (uint32_t) handler;

	interrupt_descriptor* entry = &idt[vector];
	entry->address_low = handler_addr & 0xFFFF;
	entry->address_mid = (handler_addr >> 16) & 0xFFFF;
	entry->address_high = handler_addr >> 32;
	entry->selector = 0x8;
	//entry->flags = 0b1110 | ((dpl & 0b11) << 5) | (1 << 7);
	entry->flags = 0x8E;
	entry->ist = 0;
}



// Load the interrupt descriptor table
void load_idt()
{	
	void * idt_addr = &idt;
	
	idtr idt_reg; 
    idt_reg.limit = 0xFFF;
    idt_reg.base = (uint32_t)idt_addr;
    //asm volatile("lidt %0" :: "m"(&idt_reg));
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
	terminal_writestring("finished loading IDT\n");
}
