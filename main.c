#include<stdio.h>
#include<stdint.h>
#include "ChargingModule.h"


/*  CAN DUMMY STRUCTURE */
typedef struct
{
  uint32_t StdId;           // standard ID
  uint32_t ExtId;           // extendad ID
  uint8_t IDE;              // Current used ID 
  uint8_t RTR;              // data or remote         
  uint8_t DLC;              // data length 
  uint8_t Data[8];          // actual data 
}CanTxMsg;

CanTxMsg TxMessage;


/*  CAN DUMMY STRUCTRE END HERE */
void CAN_Transmit(CanTxMsg* msg);
_Bool boGetStatus(void);
void delay(uint32_t time);
void main(void)
{


  while (1)
  {
    Charger.boStatus = boGetStatus();   // get charger connection status 
    if(Charger.boStatus == CONNECTED)
    {
        vChargingModule();              // call this function periodically after a certain interval as per requirement say 1 sec 
    }
    delay(1000); // 1000 mili second // 
  }
  
    

}
/*  dummy code */
_Bool boGetStatus(void)
{
    /*
        Get data through CAN Communication 
    */
    return CONNECTED;
}
/*  
DUMMY CAN TRANSMITTER MESSAGE STRUCTRE 
*/
void vSendCANMsg(char caseID, char Current_Percentage)
{
    uint32_t Current_ma = 0;

    TxMessage.StdId = 0x123;
    TxMessage.ExtId = 0x01;
    TxMessage.RTR = 0;              // data mode 
    TxMessage.IDE = 0;              // stdID selected 
    uint32_t *ptr; 
    

    switch (caseID)
    {
        case CURRENT : TxMessage.DLC = 4;
                       Charger.fSetCurrent = BATT_CAPACITY*Current_Percentage;
                       Current_ma = (uint32_t)(Charger.fSetCurrent*1000);
                       ptr = (uint32_t*)(&TxMessage.Data[0]);
                       *ptr = Current_ma;
                       break;
        case ERROR   : TxMessage.DLC = 8;
                       TxMessage.Data[0] = 0xFF;
                       TxMessage.Data[1] = 0xFF;
                       TxMessage.Data[2] = 0xFF;
                       TxMessage.Data[3] = 0xFF;
                       TxMessage.Data[4] = 0xFF;
                       TxMessage.Data[5] = 0xFF;
                       TxMessage.Data[6] = 0xFF;
                       TxMessage.Data[7] = 0xFF;
                       break;
        default : break;
    }

    CAN_Transmit(&TxMessage);
}
/*
DUMMY CODE 
*/
void CAN_Transmit(CanTxMsg* msg)
{
    // send message over CAN 
}
void delay(uint32_t time)
{
    while (time != 0)
    {
       time--;
       // decrement per mili second 
    }
    
}
