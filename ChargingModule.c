#define ChargingModule_Source
#include "ChargingModule.h"
#undef ChargingModule_Source
#include<stdint.h>

extern void vSendCANMsg(char caseID, char Current_Percentage);
void vChargingModule(void)
{
    float SOC = 0.0;                  // INIT LOCAL VARIABLE 
    static char sChargingPer = 100;   // INIT CONSTANT CURRENT CHARGING VALUE = 100% OF RATING 1C
    static _Bool boUpdatePer = FALSE; // CC VALUE UPDATED AT LATER STAGE 
    
    

/* GET ALL REQUIRED DATA */
     vGetBatTemperature();            // GET PACK TEMPERATURE MAX, MIN 
     vGetBatCurrent();                // GET CURRENT 
     vGetBatVoltage();                // GET PACK VOLTAGE & CELL VOLTAGE  
     vGetCellVoltage();               // GET INDIVIDUAL CELL VOLTAGE 
     SOC = fGetSOC();                 // GET SOC OF BATTERY 


/* CHECK CONDITION TO SET CURRENT */
  // CHECK TEMPERATURE & ANY RELEVANT ERROR & CURRENT VALUE (<= 0) (NEGATIVE CURRENT FOR DISCHARGING)
    if((Battery.fMaxTemperature < TEMP_CUTOFF_TH) && (Battery.boErrorFlag == FALSE) && (Battery.fPackCurrent <= Charger.fSetCurrent))
    {
        // CHECK PACK VOLTAGE 
        if((Battery.fPackVoltage < PEAK_VOLTAGE) || (SOC < 100))
        { 
            // boUpdatePer WILL REMAIN FALSE FOR FIRST CC CYCLE
            if(boUpdatePer == FALSE) 
            {
                // CHECK UNDER VOLTAGE CONDITION
                if(Battery.fPackVoltage > PACK_MIN_VOLTAGE)
                {
                    vSendCANMsg(CURRENT,sChargingPer);        // set constant current for charging till charge upto max
                }
               else 
                {
                    // PRECHARGE IS USED 
                    vSendCANMsg(CURRENT,10);                // pre-charge current 10% of rating current // set as per requirement 
                }
            }
            

            // CHECK CELL BALANCING 
            if(Battery.fMaxCellVoltage - Battery.fMinCellVoltage > CELL_BALANCE_CUTIN)
            {
                // cell balancing start if high voltage cell > CELL_BAL_MIN_VOLTAGE
                // cell balacing is checked beween two consecutive cells 
                // Trigger cell balancing using AFE
                // max 50% of cell can be balanced
                // define a time interval as balancing time (optional)
                vStart_Cell_Balancing();
                //check & then start 
            }
            else
            {
            	// check for stop ongoing cell balancing 
            	// if difference between consecutive cells is < 20 mv stop cell balancing 
                vStop_Cell_Balancing();
                // check & Then stop cell balancing using AFE
            }
                
        }
        else 
        {
             if(sChargingPer > 20)sChargingPer -= 10;      // CHANGE LEVEL OF CHARGIN CURRENT FOR NEXT CYCLE 
             else if(sChargingPer > 5)sChargingPer -= 5;   // CHANGE LEVEL OF CHARGIN CURRENT FOR NEXT CYCLE
             
             if(sChargingPer <= 5) // TO DETECT OVER CHARGE / OVER VOLTAGE CONDITION
             {
                //set timer for 5 min to check over voltage condition 
                // set Timer  = 300 seconds 
                // check after 5 min 
                // if((Timer == 0) && (SOC == 100)
                //{
                //    sChargingPer = 0;
                //}
                //CHARGING MOSFET OFF

             }
             vSendCANMsg(CURRENT,sChargingPer);              // set new constant current for charging till charge upto max 
             boUpdatePer = TRUE;
        }
    }
    else 
    {
            vSendCANMsg(ERROR,0);
            //ALL MOSFET OFF
    }

}
void vGetBatTemperature(void)
{
    // get temperature value using NTC by AFE/MCU
    //
}            
void vGetBatCurrent(void)
{
    // get bat current 
    // Positive = charging current 
    // negative = discharging current 
}               
void vGetBatVoltage(void)
{
    // battery pack voltage 
}                 
void vGetCellVoltage(void)
{
    // battey individual cell voltage 
}            
void vStart_Cell_Balancing(void)
{
    // cell balancing started using AFE 
}
void vStop_Cell_Balancing(void)
{
    // cell balancing stopped using AFE
}
float fGetSOC(void)
{
    float soc;
    // get SOC from AFE
    return soc;
}


