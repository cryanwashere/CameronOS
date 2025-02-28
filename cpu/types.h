#ifndef TYPES_H
#define TYPES_H
// This defines several non character bytes.
// this comes from: https://github.com/cfenollosa/os-tutorial/blob/master/19-interrupts-irqs/cpu/types.h

typedef unsigned int   u32;
typedef          int   s32;
typedef unsigned short u16;
typedef          short s16;
typedef unsigned char  u8;
typedef          char  s8;

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)


#endif