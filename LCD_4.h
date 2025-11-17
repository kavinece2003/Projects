#ifndef ___LCD4_H__
#define ___LCD4_H__
#include<lpc21xx.h>
#include<stdio.h>
typedef unsigned char u8;
#define lcd_d 0xf <<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19
void delay_MS(int);
void lcd_in(void);
void lcd_com(u8 );
void lcd_data(u8 );
void lcd_iprint(int );
void lcd_sprint(u8* );
void lcd_fprint(float );
void lcd_int(int );
void lcd_float(float );
void lcd_time(u8 ,u8 ,u8 ,u8 );
void lcd_calender(u8 ,u8 ,u8 ,u8 );
void lcd_2dig(u8 );
void TITLE(unsigned char *s1,unsigned char* s2);
void lcd_rot_str(unsigned char *s);

#endif


