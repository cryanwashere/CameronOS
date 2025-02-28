#ifndef PORTS_H
#define PORTS_H

#include "../cpu/types.h"
unsigned char port_byte_in (u16 port);
void port_byte_out (u16 port, u8 data);

#endif