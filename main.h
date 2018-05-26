#ifndef __MAIN_H_
#define __MAIN_H_


#include <reg52.h>
#include "curatins.h"

enum {NOACTION, CLOCK, DATA, CHANGE, SAVE} modelBright = CLOCK;
enum {START_Z, STOP_Z} modelMotorZ = STOP_Z;
enum {START_F, STOP_F} modelMotorF = STOP_F;
enum {AUTO=1, MANUAL=2, TIMING=3} modelSystem = AUTO;
enum {DISPLAY, STIME, ETIME, RETURN} modelSettings = DISPLAY;

const uint years = 0;
const uint months = 1;
const uint days = 2;
const uint hours = 3;
const uint minutes = 4;
const uint seconds = 5;
const uint startTimeHours = 0;
const uint startTimeMinutes = 1;
const uint endTimeHours = 0;
const uint endTimeMinutes = 1;
const bit TRUE = 1;
const bit FALSE = 0;

bit isStop = 0;
bit saveDataTime = 0;

uint dataTime[6] = {2017, 3, 8, 8, 29, 30};
uint startTime[2] = {8, 30};
uint endTime[2] = {8, 35};
uchar disp[8] = {0};
uint temp = 0;

uint flag = 0; 		//ÉÁË¸Ð¡Êýµã

uchar code smgDuan[11]=
{
	0xC0, 0xF9, 0xA4, 0xB0,
	0x99, 0x92, 0x82, 0xF8,
	0x80, 0x90, 0xBF
};
/*uchar code smgWei[8] = 	
{
	0x7F, 0xBF, 0xDF, 0xEF,
	0xF7, 0xFB, 0xFD, 0xFE
};*/
uchar code smgWei[8] = 
{
	0x80, 0x40, 0x20, 0x10,
	0x08, 0x04, 0x02, 0x01
};

#endif