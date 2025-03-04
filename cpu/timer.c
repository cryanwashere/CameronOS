#include "timer.h"
#include "../drivers/screen.h"
#include "isr.h"
#include "../kernel/util.h"
#include "types.h"
#include "../drivers/ports.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
    // increment the ticks on the clock, and print out that the clock has progressed
    tick ++;
    terminal_writestring("tick: ");

    char tick_ascii[256];
    int_to_ascii(tick, tick_ascii);
    terminal_writestring(tick_ascii);
    terminal_writestring("\n");
}

void init_timer(u32 freq) 
{   
    // install the timer callback function
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
     /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);

}