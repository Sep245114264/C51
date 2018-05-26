#include <reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#define A_M {a = 0; b = 1; c = 1; d = 1;}
#define B_M {a = 1, b = 0; c = 1; d = 1;}
#define C_M {a = 1; b = 1; c = 0; d = 1;}
#define D_M {a = 1; b = 1; c = 1; d = 0;}

sbit a = P1^7;
sbit b = P3^0;
sbit c = P3^1;
sbit d = P3^2;

void delayM(uint z);
void motorZ();
void motorF();
void motorStop();