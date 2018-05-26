#include <reg52.h>
#include <intrins.h>
#include "24c02.h"



void delay()        //
{ ;;;}

void start()        //
{  
	SDA=1;
    delay();         //
    SCL=1;
    delay();
    SDA=0;
    delay();
}

void stop()         //
{  
	SDA=0;             //
    delay();
    SCL=1;
    delay();
    SDA=1;
    delay();
}

void response()
{  
	uchar i;
    SCL=1;
    delay();
    if((SDA==1)&&i<250) i++;        //
    SCL=0;                          //
    delay();
}

void  noack()
{  
	SCL=1;
    delay();
    SCL=1;
    delay();
    SCL=0;
    delay();
    SDA=0;
    delay();
}
void init()                      
{  
	SDA=1;
    delay();
    SCL=1;
    delay();
}
void writeByte(uchar sData)     //
{  
	uchar i,temp;
    temp=sData;
    for(i=0;i<8;i++)
    {   
		temp=temp<<1;
        SCL=0;                    //
        delay();
        SDA=CY;                   //
        delay();
        SCL=1;
        delay();
		SCL=0;
		delay();
    }
    SCL=0;
    delay();
	SDA=1;
	delay();
}
uchar readByte()
{  
	uchar i,k;
    SCL=0;
    delay();
    SDA=1;
    delay();
    for(i=0;i<8;i++)
    {  
		SCL=1;
        delay();
        k=(k<<1)|SDA;
        SCL=0;
        delay();
    }   
    return k;
}

void writeAdd(uchar address,uchar sData)
{  
    start();
    writeByte(0xa0);                    //
    response();
    writeByte(address);
    response();
    writeByte(sData);
    response();
    stop();
}

uchar readAdd(uchar address)
{  
	uchar sData;
    start();
    writeByte(0xa0);
    response();
    writeByte(address);
    response();
    start();
    writeByte(0xa1);                //
    response();
    sData=readByte();
    noack();
    stop();
    return sData;
}