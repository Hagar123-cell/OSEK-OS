 /******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: Alarm.c
 *
 * Description: Source file for Alarm management
 *
 * Author: Yasmin Afifi
 ******************************************************************************/

#include "Alarm.h"


/************************************************************************************
* Service Name: GetAlarmBase
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm
* Parameters (out): Info  - Reference to structure with constants of the alarm base. 
* Description: The system service GetAlarmBase reads the alarm base 
*               characteristics. The return value <Info> is a structure in which 
*               the information of data type AlarmBaseType is stored.
************************************************************************************/
StatusType GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info )
{
  if(AlarmID < No_ALARMS)
  {
    
    Info = &Alarm_Configuration[AlarmID];
    return(E_OK);
    
  }
  else{
    
    return(E_OS_ID);
    
  }
  
  
  
}


/************************************************************************************
* Service Name: GetAlarm
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm
* Parameters (out): Tick Relative value in ticks before the alarm <AlarmID> expires. 
* Description: The system service GetAlarm returns the relative value in ticks 
*               before the alarm <AlarmID> expires. 
************************************************************************************/
StatusType GetAlarm ( AlarmType AlarmID, TickRefType Tick )
{
  
  
  
  
}



/************************************************************************************
* Service Name: SetRelAlarm
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm
*                  increment - Relative value in ticks 
*                  cycle - Cycle value in case of cyclic alarm. In case of single alarms, cycle shall be zero.
* Parameters (out): None
* Description: The system service occupies the alarm <AlarmID> element. 
*               After <increment> ticks have elapsed, the task assigned to the 
*               alarm <AlarmID> is activated or the assigned event (only for 
*               extended tasks) is set or the alarm-callback routine is called. 
************************************************************************************/
StatusType SetRelAlarm ( AlarmType AlarmID, TickRefType increment, TickType cycle )
{
  
  
  
  
}


/************************************************************************************
* Service Name: SetAbsAlarm
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm
*                  start - Absolute value in ticks 
*                  cycle - Cycle value in case of cyclic alarm. In case of single alarms, cycle shall be zero.
* Parameters (out): None
* Description: The system service occupies the alarm <AlarmID> element. 
*               When <start> ticks are reached, the task assigned to the alarm
*               <AlarmID> is activated or the assigned event (only for extended 
*               tasks) is set or the alarm-callback routine is called.
************************************************************************************/
StatusType SetAbsAlarm ( AlarmType AlarmID, TickRefType start, TickType cycle )
{
  
  
  
  
}



/************************************************************************************
* Service Name: CancelAlarm
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm 
* Parameters (out): None
* Description: The system service cancels the alarm <AlarmID>.
************************************************************************************/
StatusType CancelAlarm ( AlarmType AlarmID )
{
  
  
  
  
}