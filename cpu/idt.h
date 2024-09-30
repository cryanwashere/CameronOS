#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// 'IDT' means 'interrupt descriptor table'

typedef struct
{
    uint16_t address_low; 	// Lower 16 bits of handler function address
    uint16_t selector;		// kernel segment selector		
    uint8_t ist;
    uint8_t flags;
    uint16_t address_mid;
    uint32_t address_high;
    uint32_t reserved;
} __attribute__((packed)) interrupt_descriptor;

// Interrupt desriptor table register 
// The assembly instruction 'lidt' will read it
typedef struct
{
	uint16_t limit;
	uint64_t base;
} __attribute__((packed)) idtr;



// set a specific entry in the IDT table
void set_idt_entry(uint8_t vector, void* handler);

// load the IDT
void load_idt();

#endif