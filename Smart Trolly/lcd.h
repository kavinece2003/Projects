 #include <LPC21XX.H>
#include "delay.h"
#define LCD_D 0xf<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19

void lcd_init (void);
void lcd_cmd (unsigned char);
void lcd_data (unsigned char);
void lcd_str(char*);
void lcd_int(int);
void lcd_init(void)
{
IODIR1=LCD_D|RS|RW|E;
IOCLR1=RW;
lcd_cmd (0x01);
lcd_cmd (0x02);
lcd_cmd (0x0c);
lcd_cmd (0x28);
lcd_cmd (0x85);
}

void lcd_cmd(unsigned char cmd)
{
IOCLR1=LCD_D;
IOSET1=(cmd&0xf0)<<16;
IOCLR1=RS;
IOSET1=E;
delay_milliseconds(2);
IOCLR1=E;
IOCLR1=LCD_D;
IOSET1=(cmd&0x0f)<<20;
IOCLR1=RS;
IOSET1=E;
delay_milliseconds(2);
IOCLR1=E;
}

void lcd_data (unsigned char data)
{
IOCLR1=LCD_D;
IOSET1=(data&0xf0)<<16;
IOSET1=RS;
IOSET1=E;
delay_milliseconds(2);
IOCLR1=E;
IOCLR1=LCD_D;
IOSET1=(data&0x0f)<<20;
IOSET1=RS;
IOSET1=E;
delay_milliseconds(2);
IOCLR1=E;
}

void lcd_int(int n)
{
unsigned char a[7];
signed char i=0;
if(n==0)
  lcd_data('0');
else
{
  if(n<0)
   {

			lcd_data('-');

			n=-n;

		}
	while(n>0)
		{

			a[i++]=n%10;

			n=n/10;

		}

	for(i=i-1;i>=0;i--)

		lcd_data(a[i]+48);
		lcd_data(' ');
		lcd_data(' ');

}
}

void lcd_str(char* s)
{

	int i=0;
 	while(*s)
 	{

		lcd_data(*s++);

		i++;

		if(i==16)

		{

			lcd_cmd(0xc0);

		}

	}

}
