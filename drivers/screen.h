#ifndef SCREEN_H
#define SCREEN_H

/* Hardware text mode color contants */
enum vga_color {
	VGA_COLOR_BLACK			= 0,
	VGA_COLOR_BLUE			= 1,
	VGA_COLOR_GREEN			= 2,
	VGA_COLOR_CYAN			= 3, 
	VGA_COLOR_RED			= 4, 
	VGA_COLOR_MAGENTA		= 5, 
	VGA_COLOR_BROWN			= 6, 
	VGA_COLOR_LIGHT_GREY	= 7, 
	VGA_COLOR_DARK_GREY 	= 8, 
	VGA_COLOR_LIGHT_BLUE	= 9, 
	VGA_COLOR_LIGHT_GREEN	= 10,
	VGA_COLOR_LIGHT_CYAN	= 11,
	VGA_COLOR_LIGHT_RED		= 12, 
	VGA_COLOR_LIGHT_MAGENTA	= 13, 
	VGA_COLOR_LIGHT_BROWN	= 14, 
	VGA_COLOR_WHITE			= 15, 
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


size_t strlen(const char* str);

void terminal_initialize(void);

void terminal_setcolor(uint8_t color);

void terminal_put_entry_at_index(char c, size_t index);

void terminal_putchar(char c);

void terminal_write(const char* data, size_t size);

void terminal_writestring(const char* data);

#endif