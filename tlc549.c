#include "tlc549.h"

uchar TLC549(void)
{
	uchar i, sData;
	ADIO = 0;
	ADOUT = 1;
	ADCS = 0;
	for( i = 0; i < 8; ++i )
	{
		ADIO = 1;
		sData <<= 1;
		if( ADOUT == 1)
		{
			++sData;
		}
		ADIO = 0;
	}
	ADCS = 1;
	return sData;
}
