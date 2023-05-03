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
  StatusType ret = E_OK;
  OsCounterRefType counter;

  if(AlarmID < No_ALARMS)
  {

    counter = Alarms[AlarmID].OsAlarmCounterRef;

    Info->maxallowedvalue = counter->OsCounterMaxAllowedValue;
    Info->mincycle = counter->OsCounterMinCycle;
    Info->ticksperbase = counter->OsCounterTicksPerBase;
    
    
  }
  else{
    
    ret = E_OS_ID;
    
  }
  
  return ret;
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
  StatusType ret = E_OK;

  if(AlarmID < No_ALARMS)
  {
    if(Alarms[AlarmID].AlarmState == 0)
    {

      ret = E_OS_NOFUNC;

    }
    else
    {

      *Tick = Alarms[AlarmID].AlarmTime;

    }    
    
  }
  else{
    
    ret = E_OS_ID;
    
  }
  
  return ret;  
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
StatusType SetRelAlarm ( AlarmType AlarmID, TickType increment, TickType cycle )
{
  StatusType ret = E_OK;
  OsCounterRefType counter;
  counter = Alarms[AlarmID].OsAlarmCounterRef;

  if(AlarmID >= No_ALARMS)
  {

    ret = E_OS_ID;
    
  }
  else if( ( increment < 0 ) || ( increment > (counter->OsCounterMaxAllowedValue) ) || 
            ( (cycle != 0) && 
              ( (cycle > (counter->OsCounterMaxAllowedValue)) || 
                (cycle < (counter->OsCounterMinCycle)) ) ) )
            {

              ret = E_OS_VALUE;

            }

            else
            {
              if(Alarms[AlarmID].AlarmState == 1)
              {

               ret = E_OS_STATE; 

              }
              else
              {

                DisableAllInterrupts();

                Alarms[AlarmID].AlarmState = 1;
                Alarms[AlarmID].AlarmTime = increment;
                Alarms[AlarmID].AlarmCycleTime = cycle;

                EnableAllInterrupts();

              }

            }
    
  return ret;
  
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
StatusType SetAbsAlarm ( AlarmType AlarmID, TickType start, TickType cycle )
{
  StatusType ret = E_OK;
  OsCounterRefType counter;
  counter = Alarms[AlarmID].OsAlarmCounterRef;

  if(AlarmID >= No_ALARMS)
  {

    ret = E_OS_ID;
    
  }
  else if( ( start < 0 ) || ( start > (counter->OsCounterMaxAllowedValue) ) || 
            ( (cycle != 0) && 
              ( (cycle > (counter->OsCounterMaxAllowedValue)) || 
                (cycle < (counter->OsCounterMinCycle)) ) ) )
            {

              ret = E_OS_VALUE;

            }

            else
            {
              if(Alarms[AlarmID].AlarmState == 1)
              {

               ret = E_OS_STATE; 

              }
              else
              {

                DisableAllInterrupts();

                Alarms[AlarmID].AlarmState = 1;
                Alarms[AlarmID].AlarmTime = GetCounter(counter) + start;
                Alarms[AlarmID].AlarmCycleTime = cycle;

                EnableAllInterrupts();

              }

            }
    
  return ret;
  
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
  StatusType ret = E_OK;

  if(AlarmID < No_ALARMS)
  {
    
    if(Alarms[AlarmID].AlarmState == 0)
    {

      ret = E_OS_NOFUNC;

    }
    else
    {
      
      Alarms[AlarmID].AlarmState == 0;

    }
    
  }
  else
  {
    
    ret = E_OS_ID;
    
  } 

  return ret;

}