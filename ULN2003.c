#include "ULN2003.h"

void delayM(uint z)
{
    uint i, j;
    for( i = z; i > 0; --i )
    {
        for( j = 110; j > 0; --j );
    }
}

void motorZ()
{
    A_M;
    delayM(3);
    B_M;
    delayM(3);
    C_M;
    delayM(3);
    D_M;
    delayM(3);
}

void motorF()
{																												 
    D_M;																										 
    delayM(3);
    C_M;																											
    delayM(3);																							
    B_M;
    delayM(3);
    A_M;
    delayM(3);
}

void motorStop()
{
    a = 1; b = 1; c = 1; d = 1;
}