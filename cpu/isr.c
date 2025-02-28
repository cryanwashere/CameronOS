#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../drivers/ports.c"
#include <stdint.h>


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

    terminal_writestring("loading IDT\n");
    load_idt(); // Load the interrupt descriptor table
}

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */
}

void isr_handler(registers_t r)
{
	terminal_writestring("\n recieved interrupt: ");
	char s[3];
	int_to_ascii(r.int_no, s);
	terminal_writestring(exception_messages[r.int_no]);
	
}

void irq_handler(registers_t r)

{
    if (r.int_no >= 40) outb(0xA0, 0x20);
    outb(0x20, 0x20);

}