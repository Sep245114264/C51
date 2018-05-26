#ifndef __CURATINS_H__
#define __CURATINS_H__

#include <reg52.h>
#include "24c02.h"
#include "tlc549.h" 
#include "ULN2003.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit k17 = P1^0;
sbit k18 = P1^1;
sbit k19 = P1^2;
sbit k20 = P1^3;
sbit L1 = P1^6;
sbit L2 = P1^5;
sbit L3 = P1^4;

#define BRIGHT_LIMIT 0x0
#define CURRENT_DATA_YEARS_H 0X01
#define CURRENT_DATA_YEARS_T 0x02
#define CURRENT_DATA_MONTHS 0x03
#define CURRENT_DATA_DAYS 0x04
#define CURRENT_DATA_HOURS 0x05
#define CURRENT_DATA_MINUTES 0x06
#define START_TIME_HOURS 0X07
#define START_TIME_MINUTES 0x08
#define END_TIME_HOURS 0x09
#define END_TIME_MINUTES 0x10


uint bright = 0;
uint checkBright = 1; 
uint brightLimit = 200;


void delay1(uint i);

void smgDisplay(void);

void Timer0Init(void);
void Timer1Init(void);

void dataProcess(void);
void parseData();
void parseClock();
void parseBrightChange(void);
void parseSettings(void);

void modelAuto(void);
void modelManual(void);
void modelTiming(void);
bit judgeTime(void);

void driveMotor(void);
void writeData(void);
void readData(void);
void saveData(void);

#endif