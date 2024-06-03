#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


/* make sure the compiler does not think you are targeting the wrong operating system */
#if defined(__linux__)
#error "You are not using a cross compiler, you will most certainly run into trouble"
#endif

/* This will only work with 32-bit ix86 targets */
#if !defined(__i386__)
#error "This kernel needs to be compiled with an ix86-elf compiler"
#endif



/* Hardware text mode color contants */
enum vga_color {
	VGA_COLOR_BLACK		= 0,
	VGA_COLOR_BLUE		= 1,
	VGA_COLOR_GREEN		= 2,
	VGA_COLOR_CYAN		= 3, 
	VGA_COLOR_RED		= 4, 
	VGA_COLOR_MAGENTA	= 5, 
	VGA_COLOR_BROWN		= 6, 
	VGA_COLOR_LIGHT_GREY	= 7, 
	VGA_COLOR_DARK_GREY 	= 8, 
	VGA_COLOR_LIGHT_BLUE	= 9, 
	VGA_COLOR_LIGHT_GREEN	= 10,
	VGA_COLOR_LIGHT_CYAN	= 11,
	VGA_COLOR_LIGHT_RED	= 12, 
	VGA_COLOR_LIGHT_MAGENTA	= 13, 
	VGA_COLOR_LIGHT_BROWN	= 14, 
	VGA_COLOR_WHITE		= 15, 
};


/* define the foreground and background of a character with an 8 bit integer. moving right to left, the first 4 bits define the foreground, and the second 4 bits define the background*/
static inline uint8_t vga_entry_color(enum vga_color foreground, enum vga_color background)
{
	return foreground | background << 4;
}

/* create and entry in VGA video memory with a 16 bit integer. Moving right to left, the first 8 bits define the character, and the second 8 bits define the character's foreground and background color*/
static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

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

void terminal_put_entry_at_index(char c, size_t index) {
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

void kernel_main(void)
{
	/* Initialize the terminal interface */
	terminal_initialize();

	/* Write a message to the terminal */
	terminal_writestring("Welcome to CameronOS\nHere is some more text that I am just writing to see if it will eventually just be put on a new line!");
}













