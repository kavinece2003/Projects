	#include <string.h>

#include "lcd.h"

#include "uart.h"


void lcd_display(void);

char pen_tag[] = "0600670ECFA0";

char book_tag[] = "0600031D948C";


char pen_count = 0, book_count = 0, rfid =0;

int pen_price = 20, book_price = 50;

int total_price = 0, no_of_items=0 , pen_tot=0, book_tot=0; 

char rfid_tag[12];

void add_isr(void) __irq 

{

	

    while ((IOPIN0 & (1 << 14)) == 0); 

    delay_milliseconds(100);


    if (strcmp(rfid_tag, pen_tag) == 0)

        pen_count++;

    else if (strcmp(rfid_tag, book_tag) == 0)

        book_count++;


    lcd_display();

    EXTINT |= (1 << 1);

    VICVectAddr = 0;

}


void remove_isr(void) __irq

{

    while ((IOPIN0 & (1 << 15)) == 0); 

    delay_milliseconds(100);


    if (strcmp(rfid_tag, pen_tag) == 0 && pen_count > 0)

        pen_count--;

    else if (strcmp(rfid_tag, book_tag) == 0 && book_count > 0)

        book_count--;


    lcd_display();

    EXTINT |= (1 << 2);

    VICVectAddr = 0;

}

void total_isr(void) __irq 

{
   

    while ((IOPIN0 & (1 << 16)) == 0); 

    delay_milliseconds(100);
	total_price = pen_tot + book_tot;
	no_of_items = pen_count + book_count;
	lcd_cmd(0x01);
	lcd_cmd (0x80);
	lcd_str("total_Rs : ");
	lcd_int(total_price);
	lcd_cmd(0xc0);
	lcd_str("Total items:");
	lcd_int(no_of_items); 
	EXTINT |= (1<<3);
	VICVectAddr = 0;

	}


int main(void)

{

    lcd_init();

    uart_config();


    PINSEL1 |= (1 << 0);  

	PINSEL0 |= (2 << 28);
	PINSEL0 |= (1 << 31);

    EXTINT = 0x07;

    EXTMODE = 0x07;

    EXTPOLAR = 0x00;

    VICIntEnable |= (1<<14) | (1<<15) | (1<<16);

    VICVectCntl0 = (1<<5) | 14;

    VICVectAddr0 = (int)add_isr;

    VICVectCntl1 = (1<<5) | 15;

    VICVectAddr1 = (int)remove_isr;
	VICVectCntl2 = (1<<5) | 16;

    VICVectAddr2 = (int)total_isr;
    lcd_cmd(0x80);

    lcd_str("SMART TROLLEY USING RFID");
	 delay_seconds(2);

	lcd_cmd(0x01);
	lcd_cmd(0x80);

	lcd_str("Scan RFID Tag");

	delay_seconds(1);

	while (1)

	{

    UARTRX_STRING(rfid_tag);       

    UARTTX_STRING(rfid_tag);      


    if (strcmp(rfid_tag, pen_tag) == 0)

    {

        rfid = 1;

        pen_count = 1;

        lcd_display();

    }

    else if (strcmp(rfid_tag, book_tag) == 0)

    {

        rfid = 2;

        book_count = 1;

        lcd_display();

    }

    else

    {

        lcd_cmd(0x01);

		delay_milliseconds(2);

        lcd_str("Invalid Tag");

        delay_seconds(2);

        lcd_cmd(0x01);

		delay_milliseconds(2);

    }
     lcd_str("Scan RFID Tag");

	}

}




void lcd_display()

{

  lcd_cmd(0x01);

	delay_milliseconds(2);


    if (rfid == 1)  

    {

	    pen_tot = pen_count * pen_price;;

        lcd_str("Item: Pen");

        lcd_cmd(0xC0);

        lcd_str("Qty: ");

        lcd_int(pen_count);

        lcd_str(" Rs: ");

        lcd_int(pen_tot);

    }

    else if (rfid == 2)  

    {

		book_tot = book_count * book_price;

        lcd_str("Item: Book");

        lcd_cmd(0xC0);

        lcd_str("Qty: ");

        lcd_int(book_count);

        lcd_str(" Rs: ");

        lcd_int(book_tot);

    }

		

}

