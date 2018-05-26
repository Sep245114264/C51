#include "curatins.h"
#include "main.h"

void delay1(uint i)
{
	while(i--);	
}

void delay(uint i)
{
	while(i--);	
}

void modelAuto(void)
{
	static uint pressDisplay = 0;
	static uint pressChange = 0;
	uint speed = FALSE;
	L1 = 0;
	L2 = 1;
	L3 = 1;
	
	switch( modelBright )
	{
		case DATA:
			parseData();
			break;
		case CLOCK:
			parseClock();
			break;
		case CHANGE:
			parseBrightChange();
			break;
		case SAVE:
			init();
			writeData();
			modelBright = CLOCK;
			break;
	} 
	smgDisplay();
	if( modelBright == CHANGE )		//只有在调整亮度时开关17，18才能调整亮度阈值
	{
		if( k17 == 0 )
		{
			delay(500);
			if( k17 == 0)
			{
				--brightLimit;
				if( brightLimit < 0 )
				{
					brightLimit = 0;
				}
				while(!k17);
			}
		
		}
		if( k18 == 0 )
		{
			delay(500);
			if( k18 == 0 )
			{
				++brightLimit;
				if( brightLimit > 600 )
				{
					brightLimit = 600;
				}
				while(!k18);
			}
		}
	}
	else
	{
		if( k17 == 0 )				 //在其它模式17用于停止电机
		{
			motorStop();
			checkBright = FALSE;
		}
		if(	k18 == 0 )				 //在显示时钟与显示日期之间切换
		{
			delay(500);
			if( k18 == 0 )
			{
				if( !pressDisplay )
				{
					modelBright = DATA;
					pressDisplay = TRUE;
					pressChange = FALSE; 	//保证在任意一种显示模式都可以进行亮度阈值的设置
				}
				else
				{
					modelBright = CLOCK;
					pressDisplay = FALSE;
					pressChange = FALSE;
				}
			}
		}
		while( !k18 );
	}
	if( k19 == 0 )						  //在任意一种模式下都可以进入亮度阈值的设置界面
	{
		delay(500);
		if( k19 == 0 )
		{
			if( !pressChange )
			{
				modelBright = CHANGE;
				pressChange = TRUE;
				checkBright = FALSE;
			}
			else
			{
				modelBright = SAVE;
				pressChange = FALSE;
				pressDisplay = FALSE;
				checkBright = TRUE;
			}
		}
		while(!k19);
	}
	if( checkBright )
	{
		if( (bright < brightLimit) )
		{
			
			motorZ();
		}
		else
		{
			motorF();
		}
	}
}

void modelManual(void)
{
	L1 = 1;
	L2 = 0;
	L3 = 1;
	parseClock();
	smgDisplay();
	if( k17 == 0 )
	{
		delay(500);
		if( k17 == 0 )
		{
			motorStop();
			modelMotorZ = STOP_Z;
			modelMotorF = STOP_F;
		}
		while(!k17);
	}
	if( k19 == 0 )
	{
		delay(500);
		if( k19 == 0 )
		{
			switch( modelMotorZ )
			{	
				case START_Z:
					modelMotorZ = STOP_Z;
					modelMotorF = STOP_F;
					break;
				case STOP_Z:
					modelMotorZ = START_Z;
					modelMotorF = STOP_F;
					break;
			}
		}
		while(!k19);
	}
	if( k18 == 0 )
	{
		delay(500);
		if( k18 == 0 )
		{
			switch( modelMotorF )
			{
				case START_F:
					modelMotorZ = STOP_Z;
					modelMotorF = STOP_F;
					break;
				case STOP_F:
					modelMotorZ = STOP_Z;
					modelMotorF = START_F;
					break;
			}
		}
		while(!k18);
	}
	if( modelMotorZ == START_Z && modelMotorF == STOP_F )
	{
		switch( modelMotorZ )
		{
			case START_Z:
				motorZ();
				break;
			case STOP_Z:
				motorStop();
				break;
		}
	}
	if( modelMotorZ == STOP_Z && modelMotorF == START_F)
	{
		switch( modelMotorF )
		{
			case START_F:
				motorF();
				break;
			case STOP_F:
				motorStop();
				break;
		}
	}
}

void modelTiming(void)
{
	L1 = 1;
	L2 = 1;
	L3 = 0;

	if( k19 == 0 )
	{
		delay(500);
		if( k19 == 0 )
		{
			switch( modelSettings )
			{
				case DISPLAY:
					modelSettings = STIME;
					break;
				case STIME:
					modelSettings = ETIME;
					break;
				case ETIME:
					modelSettings = RETURN;
					break;
				case RETURN:
					modelSettings = DISPLAY;
					break;
			}
		}
		while(!k19);
	}
	switch(  modelSettings )
	{
		case DISPLAY:
			parseSettings();
			if( !isStop )
			{
				if( judgeTime() )
				{
					motorZ();
				}
				else
				{
					motorF();
				}
			}
			if( k17 == 0 )
			{
				delay(500);
				if( k17 == 0 )
				{
					motorStop();
					isStop = TRUE;
				}
				while(!k17);
			}
			break;
		case STIME:
			parseSettings();
			if( k17 == 0 )
			{
				delay(500);
				if( k17 == 0 )
				{
					if( ++startTime[startTimeMinutes] == 60 )
					{
						startTime[startTimeMinutes] = 0;
						if( ++startTime[startTimeHours] == 24 )
						{
							startTime[startTimeHours] = 0;
						}
					}
				}
				while(!k17);
			}
			if( k18 == 0 )
			{
				delay(500);
				if( k18 == 0 )
				{
					if( ++startTime[startTimeHours] == 24 )
					{
						startTime[startTimeHours] = 0;
					}
				}
				while(!k18);
			}
			break;
		case ETIME:
			parseSettings();
			if( k17 == 0 )
			{
				delay(500);
				if( k17 == 0 )
				{
					if( ++endTime[endTimeMinutes] == 60 )
					{
						endTime[endTimeMinutes] = 0;
						if( ++endTime[endTimeHours] == 24 )
						{
							endTime[endTimeHours] = 0;
						}
					}
				}
				while(!k17);
			}
			if( k18 == 0 )
			{
				delay(500);
				if( k18 == 0 )
				{
					if( ++endTime[endTimeHours] == 24 )
					{
						endTime[endTimeHours] = 0;
					}
				}
				while(!k18);
			}
			break;
		case RETURN:
			init();
			writeData();
			modelSystem = AUTO;
			break;
	}
	smgDisplay();
}

//判断当前时间是否在设定时间之间
bit judgeTime()
{
	if( dataTime[hours] <= endTime[endTimeHours] && dataTime[hours] >= startTime[startTimeHours] )
	{
		if( dataTime[minutes] <= endTime[endTimeMinutes] &&	dataTime[minutes] >= startTime[startTimeMinutes] )
		{
			return TRUE;
		}
	}
	return FALSE;
}

// 日期时间格式化
void dataProcess(void)
{
	++dataTime[seconds];
	if( dataTime[seconds] == 60 )
	{
		dataTime[seconds] = 0;
		if( ++dataTime[minutes] == 60 )
		{
			dataTime[minutes] = 0;
			if( ++dataTime[hours] == 24 )
			{
				dataTime[hours] = 0;
				if( ++dataTime[days] == 30 )
				{
					dataTime[days] = 0;
					if( ++dataTime[months] == 12 )
					{
						dataTime[months] = 0;
						++dataTime[years];
					}
				}
			}
		}
	}
}

void parseData()
{
	disp[0] = smgDuan[dataTime[years] / 1000];
	disp[1] = smgDuan[dataTime[years] / 100 % 10];
	disp[2] = smgDuan[dataTime[years] / 10 % 100];
	disp[3] = smgDuan[dataTime[years] % 10] & 0x7F;
	disp[4] = smgDuan[dataTime[months] / 10];
	disp[5] = smgDuan[dataTime[months] % 10] & 0x7F;
	disp[6] = smgDuan[dataTime[days] / 10];
	disp[7] = smgDuan[dataTime[days] % 10];
}

void parseClock()
{
	disp[0] = smgDuan[dataTime[hours] / 10];
	if( flag )
	{
		disp[1] = smgDuan[dataTime[hours] % 10] & 0x7F;
	}
	else
	{
		disp[1] = smgDuan[dataTime[hours] % 10];
	}
	disp[2] = smgDuan[dataTime[minutes] / 10];
	disp[3] = smgDuan[dataTime[minutes] % 10];
	disp[4] = smgDuan[10];
	disp[5] = smgDuan[bright / 100];
	disp[6] = smgDuan[bright / 10 % 10];
	disp[7] = smgDuan[bright % 10];
	//disp[1] = smgDuan[dataTime[seconds] / 10];
	//disp[0] = smgDuan[dataTime[seconds] % 10];
}

void parseBrightChange(void)
{
	disp[0] = 0xFF;
	disp[1] = 0xFF;
	disp[2] = 0xFF;
	disp[3] = 0xFF;
	disp[4] = 0xFF;
	disp[5] = smgDuan[brightLimit / 100];
	disp[6] = smgDuan[brightLimit / 10 % 10];
	disp[7] = smgDuan[brightLimit % 10];
}

void parseSettings(void)
{
	uint startFlag = FALSE;
	uint endFlag = FALSE;
	switch( modelSettings )
	{
		case STIME:
			startFlag = flag;
			break;
		case ETIME:
			endFlag = flag;
			break;
	}
	if( !startFlag )
	{
		disp[0] = smgDuan[startTime[startTimeHours] / 10];
		disp[1] = smgDuan[startTime[startTimeHours] % 10] & 0x7F;
		disp[2] = smgDuan[startTime[startTimeMinutes] / 10];
		disp[3] = smgDuan[startTime[startTimeMinutes] % 10] & 0x7F;
	}
	else
	{
		disp[0] = 0xFF;
		disp[1] = 0xFF;
		disp[2] = 0xFF;
		disp[3] = 0xFF;
	}
	if( !endFlag )
	{
		disp[4] = smgDuan[endTime[endTimeHours] / 10];
		disp[5] = smgDuan[endTime[endTimeHours] % 10] & 0x7F;
		disp[6] = smgDuan[endTime[endTimeMinutes] / 10];
		disp[7] = smgDuan[endTime[endTimeMinutes] % 10];
	}
	else
	{
		disp[4] = 0xFF;
		disp[5] = 0xFF;
		disp[6] = 0xFF;
		disp[7] = 0xFF;	
	}
}

void smgDisplay(void)
{
	uchar i = 0;
	
	for( i = 0; i < 8; ++i )
	{
		P2= smgWei[i];
		P0 = disp[i];
		delay(100);
		P0 =0xFF; 		//数码管消影
	}
}
	
void writeData(void)
{
	init();
	writeAdd(BRIGHT_LIMIT, brightLimit);
	delay(500);
	writeAdd(START_TIME_HOURS, startTime[startTimeHours]);
	delay(500);
	writeAdd(START_TIME_MINUTES, startTime[startTimeMinutes]);
	delay(500);
	writeAdd(END_TIME_HOURS, endTime[endTimeHours]);
	delay(500);
	writeAdd(END_TIME_MINUTES, endTime[endTimeMinutes]);
	delay(500);	
}

void readData(void)
{
	uint yearsH, yearsT;
	init();
	brightLimit = readAdd(BRIGHT_LIMIT);
	delay(500);
	yearsH = readAdd(CURRENT_DATA_YEARS_H);
	delay(500);
	yearsT = readAdd(CURRENT_DATA_YEARS_T);
	delay(500);
	dataTime[years] = yearsH * 100 + yearsT;
	dataTime[months] = readAdd(CURRENT_DATA_MONTHS);
	delay(500);
	dataTime[days] = readAdd(CURRENT_DATA_DAYS);
	delay(500);
	dataTime[hours] = readAdd(CURRENT_DATA_HOURS);
	delay(500);
	dataTime[minutes] = readAdd(CURRENT_DATA_MINUTES);
	delay(500);
	startTime[startTimeHours] = readAdd(START_TIME_HOURS);
	delay(500);
	startTime[startTimeMinutes] = readAdd(START_TIME_MINUTES);
	delay(500);
	endTime[endTimeHours] = readAdd(END_TIME_HOURS);
	delay(500);
	endTime[endTimeMinutes] = readAdd(END_TIME_MINUTES);
	delay(500);
}

void saveData(void)
{
	init();
	writeAdd(CURRENT_DATA_YEARS_H, dataTime[years] / 100);
	delay(500);
	writeAdd(CURRENT_DATA_YEARS_T, dataTime[years] % 100);
	delay(500);
	writeAdd(CURRENT_DATA_MONTHS, dataTime[months]);
	delay(500);
	writeAdd(CURRENT_DATA_DAYS, dataTime[days]);
	delay(500);
	writeAdd(CURRENT_DATA_HOURS, dataTime[hours]);
	delay(500);
	writeAdd(CURRENT_DATA_MINUTES, dataTime[minutes]);
	delay(500);
}