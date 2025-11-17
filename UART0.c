 #include<lpc21xx.h>
 #include<stdio.h> 


 
 #define THRE 5
 #define RDR 0

 void delay(int sec);
 void UART0_CONFIG(void) ;
 void UART0_TX(unsigned char);
 void UART0_TXSTR(unsigned char *);
 void UART0_TXINT(int);
 void UART0_TXFLOAT(float );


void UART0_CONFIG()
 {
 PINSEL0=5;//p0.0 as TXD0 & p0.1 as RXD0
 U0LCR=0x83;// DLAB bit =1, to access the U0DLL & U0DLM register
 U0DLL=97;  // to set the baud rate
 U0DLM=0;   // to set the baud rate
 U0LCR=0x03; // DLAB bit =0 , to access the data buffer registers(U0THR & U0RBR)

 }
 
 void UART0_TX(unsigned char ch)
 {
 U0THR = ch;                        // set the character value to the U0THR register  
 while(((U0LSR>>THRE)&1)==0);	    // wait until UOTHR register becames 
                                     // empty using the staus register U0LSR

 }

 void UART0_TXSTR(unsigned char *p)
 {
    unsigned char i;
    for(i=0;p[i];i++)
    UART0_TX(p[i]);	  // passing character to the UART_TX()

 }

 void UART0_TXINT(int x)
 {
 unsigned char a[10];	     //declare 1 character array for sprintf()
 sprintf((char *)a,"%d",x);
 UART0_TXSTR(a);	      // passing starting array address to the str ()


 }

 void UART0_TXFLOAT(float f)
 {
 unsigned char a[20];	      //declare 1 character array for sprintf()
 sprintf((char *)a,"%.3f",f);
 UART0_TXSTR(a);	      // passing starting array address to the str ()


 }
 UART0_TXHEX(int n)
 {
char a[10];
sprintf(a,"%x",n);
UART0_TXSTR(a);
 }
 void delay(int s)
 {
 T0PR=15000000-1;   // set the prescale value
 T0TCR=1;	    // enable the timer  
 while(T0TC<s);	    //wait until the T0TC = sec
 T0TCR=3;	    // RESET the timer
 T0TCR=0;	    // disable the timer 

 }
