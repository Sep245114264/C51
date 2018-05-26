#ifndef __24C02_H__
#define __24C02_H__
#include <reg52.h>
sbit SCL = P3^6;
sbit SDA = P3^7;

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

void delay();
void start();
void stop();
void response();
void noack();
void init();
void writeByte(uchar sData);
uchar readByte();
void writeAdd(uchar address, uchar sData);
uchar readAdd(uchar address);

#endif
