#include "curatins.c"

void main(void)
{
	Timer0Init();
	bright = TLC549();
	//writeData();
	//saveData();
	readData();
	temp = dataTime[minutes];
	while(1)
	{
		if( dataTime[minutes] != temp )
		{
			saveData();
			temp = dataTime[minutes];
		}
		if( k20 == 0 )
		{
			delay1(500);
			if( k20 == 0 )
			{
				switch( modelSystem )
				{
					case TIMING:
						checkBright = TRUE;
						modelSystem = AUTO;
						break;
					case AUTO:
						checkBright = FALSE;
						modelMotorZ = STOP_Z;
						modelMotorF = STOP_F;
						modelSystem = MANUAL;
						break;
					case MANUAL:
						checkBright = FALSE;
						isStop = FALSE;
						modelSystem = TIMING;
						break;
				}
			}
			while(!k20);
		}

		switch( modelSystem )
		{
			case AUTO:
				modelAuto();
				break;
			case MANUAL:
				modelManual();
				break;
			case TIMING:
				modelTiming();
				break;
		}
	}
}

void Timer0Init(void)
{
	TMOD |= 0x01;
	TH0 = 0xFC;
	TL0 = 0x18;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

void Timer0() interrupt 1
{
	static uint count;
	static uint i;
	TH0 = 0xFC;
	TL0 = 0x18;
	++i;
	if( i == 500 )
	{
		flag = !flag;
	}
	if( i == 1000 )
	{
		i = 0;
		dataProcess();
		if(checkBright )
		{
			bright = TLC549();
		}
		if( ++count == 60 )
		{
			count = 0;
			temp = dataTime[minutes];
		}
	}
} 	