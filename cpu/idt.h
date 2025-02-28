#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "types.h"


// Segment selectors
#define KERNEL_CS 0x08


// 'IDT' means 'interrupt descriptor table'

typedef struct 
{
   u16 low_offset; // lower 16 bits of handler function address
   u16 sel; // kernel segment selector
   u8 always0;

   /*
        bit 7: "interrupt is present"
        bits 5-6: privilege level of caller (0=kernel..3=user)
        bit 4: set to 0 for interrupt gates
        bits 3-0: 1110 = 14 = "32 bit interrupt gate"
   */
   u8 flags;
   u16 high_offset; // higher 16 bits of handler function address
} __attribute__((packed)) interrupt_gate_t;

// A pointer to the array of interrupt handlers
// The assembly instruction 'lidt' will read it
typedef struct
{
	u16 limit;
	u32 base;
} __attribute__((packed)) idtr;




// set a specific entry in the IDT table
void set_idt_entry(int n, void* handler);

// load the IDT
void load_idt();

#endif