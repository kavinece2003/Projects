#include<lpc21xx.h>
#include "CAN.h"
#include "LCD_4.h"
#include "UART0.c"
#define L_INDICATOR 1<<17
#define ID M.id
#define MG M.byteA
#define LI_ID 0x1FF
#define LI_ON 0xAAAAAAAA
#define LI_OFF 0x11111111

int main()
{
	CAN2_MSG M;
	CAN2_INIT(1);
	lcd_in();
	UART0_CONFIG();
	IODIR0|=L_INDICATOR;
	IOSET0=L_INDICATOR;
	UART0_TXSTR("HELLO\r\n");
	lcd_com(0x80);
	lcd_sprint("LEFT INDICATOR");

	while(1)
	{
		CAN2_RX(&M);

		if(ID==LI_ID)
		{
		UART0_TXSTR("MESSAGE RECIEVED\r\n");
			ifif(MG==LI_ON) {
			
			lcd_com(0xc0);
			lcd_sprint("      ");
			lcd_com(0xc0);
			lcd_sprint("ON");
				IOCLR0=L_INDICATOR;}
			else if(MG==LI_OFF)
			{	lcd_com(0xc0);
			lcd_sprint("OFF");
				IOSET0=L_INDICATOR;
				}
		}
	}
}
