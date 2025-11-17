
#include "LCD_4.h"

#include "delay.h"



   /*---------------------definition----------------------*/


void lcd_in(void)
{
IODIR1|=lcd_d|RS|RW|E;
IOCLR1=RW;
lcd_com(0X01);
lcd_com(0X02);
lcd_com(0X0C);
lcd_com(0x28);

}

void lcd_com(unsigned char cmd )
{
IOCLR1=lcd_d;
IOSET1=((0xf0) & cmd)<<16;
IOCLR1=RS;
IOSET1=E;
delay_MS(2);
IOCLR1=E;

IOCLR1=lcd_d;
IOSET1=((0x0f)& cmd)<<20;
IOCLR1=RS;
IOSET1=E;
delay_MS(2);
IOCLR1=E;

}

void lcd_data(unsigned char d)
{
IOCLR1=lcd_d;
IOSET1=((0xF0) & d)<<16;
IOSET1=RS;
IOSET1=E;
delay_MS(2);
IOCLR1=E;

IOCLR1=lcd_d;
IOSET1=((0x0f) & d)<<20;
IOSET1=RS;
IOSET1=E;
delay_MS(2);
IOCLR1=E;

}

void delay_MS(int sec)
{
T0PR=15000-1;
T0TCR=1;
while(T0TC<sec);
T0TCR=3;
T0TCR=0;

}

 void lcd_sprint(unsigned char* s)
   {
   int count =0;
   while(*s)
   {
   lcd_data(*s++);
   count++;
   if(count ==16)
   lcd_com(0x0c);}}


 void lcd_iprint(int n)
   {
   unsigned char arr[5];
   signed char i=0;
   if(n==0)
   lcd_data('0');
   else
   {
   if(n<0){
   lcd_data('-');
   n=-n;   }
   while(n!=0)
   {
   arr[i++]=n%10;
   n=n/10;
   }
   for(--i;i>=0;i--)
   lcd_data(arr[i]+48);

   }
   }
void lcd_int(int n)
{
	char a[5];
	unsigned char i=0;
	sprintf(a,"%d",n);
	for(i=0;a[i];i++)
		lcd_data(a[i]);
}

void lcd_2dig(u8 n)
{
	lcd_data((n/10)+48);
	lcd_data((n%10)+48);

}

void lcd_float(float n)
{
	char a[10];
	unsigned char i=0;
	sprintf(a,"%.3f",n);
	for(i=0;a[i];i++)
		lcd_data(a[i]);
}

void lcd_fprint(float f)
{
	int n;
	n=f;
	lcd_int(n);
	lcd_data('.');
	n=(f-n)*1000;
	lcd_int(n);
}
void lcd_time(u8 hr,u8 min,u8 sec,u8 am)
{
	lcd_2dig(hr);
	lcd_data(':');
	lcd_2dig(min);
	lcd_data(':');
	lcd_2dig(sec);
	lcd_data(' ');
	if(am==1)
	lcd_sprint("AM");
	else
		lcd_sprint("PM");

}
void lcd_calender(u8 day,u8 date,u8 month,u8 year)
{
	char *a[]={"\0","MON","TUES","WED","THURS","FRI","SAT","SUN"};
	lcd_sprint((u8 *)a[day]);
	lcd_data(' ');
	lcd_2dig(date);
	lcd_data('-');
	lcd_2dig(month);
	lcd_data('-');
	lcd_2dig(year);


}
void TITLE(unsigned char *s1,unsigned char* s2)
{
	//lcd_sprint("PROJECT NO 1:");
delay_seconds(1);
 lcd_rot_str(s1);
 lcd_com(0x80);
 lcd_sprint("                                 ");
 lcd_com(0x80);
 lcd_sprint(s2);
    delay_milliseconds(200);
 lcd_com(0x01);
}

void lcd_rot_str(unsigned char *s)
{
 int len,i;
 for(len=0;s[len];len++);
  for(i=0;i<=len-15;i++)
  {
  lcd_com(0x80);
  lcd_sprint(s+i);
  lcd_com(0x0c);
   lcd_sprint("                                 ");
  if(i>(len-15)){
   lcd_sprint("                                   ");
   
   delay_milliseconds(200);
  }
  else
  delay_milliseconds(200);
	
  } 
}
