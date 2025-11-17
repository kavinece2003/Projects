#ifndef __CAN_TX_H__
#define __CAN_TX_H__
#include<lpc21xx.h>


/*----------------------C1MOD/C2MOD-------------------------------*/

#define RM 1<<0   // reset mode select


/*----------------------C1CMR/C1CMR--------------------------------*/

#define TX 1<<0
#define RRB 1<<2
#define TX_B1 1<<5
#define TX_B2 1<<6
#define TX_B3 1<<7

/*---------------------C1GSR/C2GSR---------------------------------*/

#define TCS 3    // trasmission complete status
#define RBS 0    // receive buffer status
/*---------------------AFMR----------------------------------*/

#define ALL_MSG 1<<1
#define ENABLED_IDs 0


#define dlc(x) x<<16
#define SF     0<<31
#define EF     1<<31
#define RTR    1<<30

typedef struct msg
{
	int id;
	char dlc;
	char rtr;
	int byteA;
	int byteB;
	
} CAN1_MSG;

typedef struct msg1
{
	int id;
	char dlc;
	char rtr;
	int byteA;
	int byteB;
	
} CAN2_MSG;
/*-------------------------Function declarations----------------------*/
void CAN1_INIT(int);
void CAN1_TX(CAN1_MSG);
void CAN1_RX(CAN1_MSG *);
void CAN2_INIT(int);
void CAN2_TX(CAN2_MSG);
void CAN2_RX(CAN2_MSG *);

#endif
