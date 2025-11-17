#include "CAN.h"

void CAN1_INIT(int n)
{
	PINSEL1=0x40000;
	VPBDIV=1;
	C1MOD=RM;
	if(n==1)
	AFMR=ALL_MSG;
	else
		AFMR=ENABLED_IDs;
	C1BTR=0x001C001D;//   125kbps speed
	C1MOD=0;
	
}
void CAN2_INIT(int n)
{
	PINSEL1=0x14000;
	VPBDIV=1;
	C2MOD=RM;
	if(n==1)
	AFMR=ALL_MSG;
	else
		AFMR=ENABLED_IDs;
	C2BTR=0x001C001D;//   125kbps speed
	C2MOD=0;
	
}
void CAN1_TX(CAN1_MSG m1)
{
	C1TFI1=SF|dlc(m1.dlc);
	C1TID1 = m1.id;
	if(m1.rtr==0)
	{
		C1TFI1&=~(RTR);
		C1TDA1=m1.byteA;
		C1TDB1=m1.byteB;
		
	}
	else
		C1TFI1=RTR;
	C1CMR=TX|TX_B1;
	while(((C1GSR>>TCS)&1)==0);
	
}
void CAN2_TX(CAN2_MSG m1)
{
	C2TFI1=SF|dlc(m1.dlc);
	C2TID1 = m1.id;
	if(m1.rtr==0)
	{
		C2TFI1&=~(RTR);
		C2TDA1=m1.byteA;
		C2TDB1=m1.byteB;
		
	}
	else
		C2TFI1=RTR;
	C2CMR=TX|TX_B1;
	while(((C2GSR>>TCS)&1)==0);
	
}
void CAN1_RX(CAN1_MSG *m1)
{
	while(((C1GSR>>RBS)&1)==0);
	m1->id=C1RID;
	m1->dlc=(C1RFS>>16)&0xf;
	m1->rtr=(C1RFS>>30)&0x01;
	if(m1->rtr==0)
	{
		m1->byteA=C1RDA;
		m1->byteB=C1RDB;
	}
	
	C1CMR= RRB;
	
}
void CAN2_RX(CAN2_MSG *m1)
{
	while(((C2GSR>>RBS)&1)==0);
	m1->id=C2RID;
	m1->dlc=(C2RFS>>16)&0xf;
	m1->rtr=(C2RFS>>30)&0x01;
	if(m1->rtr==0)
	{
		m1->byteA=C2RDA;
		m1->byteB=C2RDB;
	}
	
	C2CMR= RRB;
	
}
