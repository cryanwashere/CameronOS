// The keyboard buffer stores the characters that have been entered in the keyboard 
/*
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

#include "keyboard.h"
#include "ports.h"