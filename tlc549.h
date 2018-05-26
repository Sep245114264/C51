#include <reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit ADIO = P3^5;
sbit ADOUT = P3^4;
sbit ADCS = P3^3;

uchar TLC549(void);