#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "screen.h"

/* Get the length of a string */
size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}


/* define constants regarding the dimensions of the terminal */
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
size_t terminal_index; // the index of the cursor in video memory

uint8_t terminal_color; 
uint16_t* terminal_buffer;

void terminal_initialize(void) 
{
	terminal_row = 0; 
	terminal_column = 0; 
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color; 
}

void terminal_put_entry_at_index(char c, size_t index)
{
	terminal_buffer[index] = vga_entry(c, terminal_color);
}

void terminal_putchar(char c)
{	
	// if the char is a new line character, then move to the next line
	if (c == '\n') {
		
		// how many spaces have been taken up in the current terminal row
		size_t cursor_mod = terminal_index % VGA_WIDTH;
		
		// increase the terminal index by the number of spaces that are left
		terminal_index += VGA_WIDTH - cursor_mod;
		
	} else {
		terminal_put_entry_at_index(c, terminal_index);
		terminal_index++;
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}
