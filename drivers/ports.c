
/* functions for reading and writing to serial ports */
extern inline unsigned char inb (int portnum)
{
	unsigned char data=0;
  	__asm__ __volatile__ ("inb %%dx, %%al" : "=a" (data) : "d" (portnum));
  	return data;
}
extern inline void outb (int portnum, unsigned char data)
{
  	__asm__ __volatile__ ("outb %%al, %%dx" :: "a" (data),"d" (portnum));
}

/* initialize serial communication */
#define PORT 0x3f8
static int init_serial() {
	outb(PORT + 1, 0x00);	 // Disable all interrupts
	outb(PORT + 3, 0x80);	 // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);    //                  (hi byte)
	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
	outb(PORT + 0, 0xAE);    // Send a test byte
	
	// Check that we received the same test byte we sent
	if(inb(PORT + 0) != 0xAE) {
		return 1;
	}
	
	// If serial is not faulty set it in normal operation mode:
	// not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled
	outb(PORT + 4, 0x0F);
	return 0;
}
