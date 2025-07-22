	  #include<LPC21XX.H>

#define rdr 0

#define thre 5

typedef unsigned char u8;

void UARTRX_STRING(char*);

void UARTTX_STRING(char*);

void uart_config(void);

void uart_tx(u8);

u8 uart_rx(void);

void uart_config(void)

{

	PINSEL0|=0x05; // to set rx and tx for uart 0;

	U0LCR=0x83;// to enable dlab in lcr and 8bit data frame (8=dlab,3=8 bit frame)

	U0DLL=97;// to set baudrate

	U0LCR=0x03;// to disale the dlab in lcr

}

void uart_tx(u8 ch)

{

	U0THR=ch;

	while(((U0LSR>>thre)&1)==0);

}

u8 uart_rx(void)

{

	while(((U0LSR>>rdr)&1)==0);

	return U0RBR;

}


 void UARTRX_STRING(char*p)

 {

  unsigned int i;

  for(i=0;i<12;i++)

  p[i]=uart_rx();

 }


 void UARTTX_STRING(char*p)

 {

  unsigned int i;

  for(i=0;i<12;i++)

  uart_tx(p[i]);

 }
