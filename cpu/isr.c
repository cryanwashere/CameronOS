#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/ports.h"
#include <stdint.h>
#include "../kernel/util.h"

isr_t interrupt_handlers[256];
 
/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


/* Can't do this with a loop because we need the address
 * of the function names. Manually load each entry in the interrupt descriptor table */
void isr_install() {
    terminal_writestring("setting IDT entries\n");

    set_idt_entry(0, (void *)isr0);
    set_idt_entry(1, (void *)isr1);
    set_idt_entry(2, (void *)isr2);
    set_idt_entry(3, (void *)isr3);
    set_idt_entry(4, (void *)isr4);
    set_idt_entry(5, (void *)isr5);
    set_idt_entry(6, (void *)isr6);
    set_idt_entry(7, (void *)isr7);
    set_idt_entry(8, (void *)isr8);
    set_idt_entry(9, (void *)isr9);
    set_idt_entry(10, (void *)isr10);
    set_idt_entry(11, (void *)isr11);
    set_idt_entry(12, (void *)isr12);
    set_idt_entry(13, (void *)isr13);
    set_idt_entry(14, (void *)isr14);
    set_idt_entry(15, (void *)isr15);
    set_idt_entry(16, (void *)isr16);
    set_idt_entry(17, (void *)isr17);
    set_idt_entry(18, (void *)isr18);
    set_idt_entry(19, (void *)isr19);
    set_idt_entry(20, (void *)isr20);
    set_idt_entry(21, (void *)isr21);
    set_idt_entry(22, (void *)isr22);
    set_idt_entry(23, (void *)isr23);
    set_idt_entry(24, (void *)isr24);
    set_idt_entry(25, (void *)isr25);
    set_idt_entry(26, (void *)isr26);
    set_idt_entry(27, (void *)isr27);
    set_idt_entry(28, (void *)isr28);
    set_idt_entry(29, (void *)isr29);
    set_idt_entry(30, (void *)isr30);
    set_idt_entry(31, (void *)isr31);

    // Remap the PIC
    // I don't really understand what this does at the moment
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0); 



    // Install the IRQs
    set_idt_entry(32, (void *)irq0);
    set_idt_entry(33, (void *)irq1);
    set_idt_entry(34, (void *)irq2);
    set_idt_entry(35, (void *)irq3);
    set_idt_entry(36, (void *)irq4);
    set_idt_entry(37, (void *)irq5);
    set_idt_entry(38, (void *)irq6);
    set_idt_entry(39, (void *)irq7);
    set_idt_entry(40, (void *)irq8);
    set_idt_entry(41, (void *)irq9);
    set_idt_entry(42, (void *)irq10);
    set_idt_entry(43, (void *)irq11);
    set_idt_entry(44, (void *)irq12);
    set_idt_entry(45, (void *)irq13);
    set_idt_entry(46, (void *)irq14);
    set_idt_entry(47, (void *)irq15);


    terminal_writestring("loading IDT\n");
    load_idt(); // Load the interrupt descriptor table
}



// this is run when an interrupt is called
// this function gets called in interrupt.asm
void isr_handler(registers_t r)
{
    // communicate that there has been an interrupt
	terminal_writestring("\n(isr_handler) recieved interrupt: ");
    // get the interrupt number that is in the register
	char s[3];
	int_to_ascii(r.int_no, s);
    // print out the exception message that corresponds to the interrupt that has been called
	terminal_writestring(exception_messages[r.int_no]);

    terminal_writestring(" (message finished)");
	
}

void register_interrupt_handler(u8 n, isr_t handler) {
    interrupt_handlers[n] = handler; 
}

// IRQ stands for interrupt request

void irq_handler(registers_t r)
{
    // after the interrupt, we need to send an EOI (End Of Interrupt) to the PICs or they will not send another interrupt
    if (r.int_no >= 40) port_byte_out(0xA0,0x20); // slave
    port_byte_out(0x20,0x20); // master

    // handle the interrupt
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }

}