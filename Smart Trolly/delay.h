#include<LPC21XX.H>

typedef unsigned int uint;

void delay_seconds(uint);

void delay_milliseconds(uint);

void delay_microseconds(uint);


void delay_seconds(uint s)

{

	T0PR=15000000-1;

	T0TCR=0X01;

	while(T0TC<s);

	T0TCR=0X03;

	T0TCR=0X00;

}

void delay_milliseconds(uint ms)

{

	T0PR=15000-1;

	T0TCR=0X01;

	while(T0TC<ms);

	T0TCR=0X03;

	T0TCR=0X00;

}

void delay_microseconds(uint mcs)

{

	T0PR=15-1;

	T0TCR=0X01;

	while(T0TC<mcs);

	T0TCR=0X03;

	T0TCR=0X00;

}
