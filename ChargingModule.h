#ifndef CHARGING_MODULE_H
#define	CHARGING_MODULE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TRUE            1
#define FALSE           0

#define DISCONNECTED    0
#define CONNECTED       1

#define CURRENT         0
#define ERROR           1


#define PEAK_VOLTAGE    73
#define NOMINAL_VOLTAGE 64
#define PACK_MIN_VOLTAGE 50

#define CELL_BALANCE_CUTIN  50 //50 mv 
#define CELL_BAL_MIN_VOLTAGE 3200// 3.2 volt

#define TEMP_CUTOFF_TH   70
#define TEMP_CUTIN_TH    65

#define BATT_CAPACITY    50 // 50AH

typedef struct 
{
    float fVoltage;
    float fCurrent;
    float fSetCurrent;
    _Bool boStatus;
}rchargerData_S;

typedef struct 
{
    float fPackVoltage;        //voltage 
    float fPackCurrent;        // amp
    float fMaxTemperature;     // Degree Celcius
    float fMinTemperature;     // Degree Celcius
    float fMaxCellVoltage;     // mili volt
    float fMinCellVoltage;     // mili volt 
    float CellVoltage[18];     // mili volt
    _Bool boOverVoltage;
    _Bool boUnderVoltage;
    _Bool boOverCurrent;
    _Bool boErrorFlag;
}rBatteryData_S;
 
#ifdef ChargingModule_Source
#define SOURCE 
#else 
#define SOURCE extern
#endif
SOURCE rchargerData_S   Charger;
SOURCE rBatteryData_S   Battery;


void vChargingModule(void);
void vGetBatTemperature(void);             
void vGetBatCurrent(void);                 
void vGetBatVoltage(void);                 
void vGetCellVoltage(void);               
void vStart_Cell_Balancing(void);
void vStop_Cell_Balancing(void);
float fGetSOC(void);


#ifdef	__cplusplus
}
#endif

#endif	/* CHARGING_MODULE_H */

