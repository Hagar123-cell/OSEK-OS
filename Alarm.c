 /******************************************************************************
 *
 * Module: Alarm
 *
 * File Name: Alarm.c
 *
 * Description: Source file for Alarm management
 *
 * Author:
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

#if (OS_EXTENDED_ERROR == TRUE)

  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    ret = E_OS_ID;

  }
  else

#endif
 {



    Info->maxallowedvalue = Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue;
    Info->mincycle = Alarms[AlarmID].OsAlarmCounterRef->OsCounterMinCycle;
    Info->ticksperbase = Alarms[AlarmID].OsAlarmCounterRef->OsCounterTicksPerBase;
    

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
#if (OS_EXTENDED_ERROR == TRUE)

  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    ret = E_OS_ID;

  }
  else

#endif
 {

    if(Alarms[AlarmID].AlarmState == Disable)
    {

      ret = E_OS_NOFUNC;

    }
    else
    {

      *Tick = Alarms[AlarmID].AlarmTime;

    }
    
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

#if (OS_EXTENDED_ERROR == TRUE)

  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    ret = E_OS_ID;
    
  }
  else if( ( increment < 0 ) || ( increment > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue) ) ||
            ( (cycle != 0) && 
              ( (cycle > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue)) ||
                (cycle < (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMinCycle)) ) ) )
            {

              ret = E_OS_VALUE;

            }

            else
#endif
            {
              if(Alarms[AlarmID].AlarmState == Enable)
              {

               ret = E_OS_STATE; 

              }
              else
              {

                //DisableAllInterrupts();

                Alarms[AlarmID].AlarmState = 1;
                Alarms[AlarmID].AlarmTime = increment;
                Alarms[AlarmID].AlarmCycleTime = cycle;

                //EnableAllInterrupts();

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


#if (OS_EXTENDED_ERROR == TRUE)

  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    ret = E_OS_ID;
    
  }
  else if( ( start < 0 ) || ( start > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue) ) ||
            ( (cycle != 0) && 
              ( (cycle > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue)) ||
                (cycle < (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMinCycle)) ) ) )
            {

              ret = E_OS_VALUE;

            }

            else
#endif
            {
              if(Alarms[AlarmID].AlarmState == 1)
              {

               ret = E_OS_STATE; 

              }
              else
              {

            	//DisableAllInterrupts();

                Alarms[AlarmID].AlarmState = 1;
                Alarms[AlarmID].AlarmTime = Alarms[AlarmID].OsAlarmCounterRef->Time + start;
                Alarms[AlarmID].AlarmCycleTime = cycle;

                //EnableAllInterrupts();

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

#if (OS_EXTENDED_ERROR == TRUE)

  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    ret = E_OS_ID;

  }
  else

#endif
  {
    
    if(Alarms[AlarmID].AlarmState == 0)
    {

      ret = E_OS_NOFUNC;

    }
    else
    {
      
      Alarms[AlarmID].AlarmState = 0;

    }
    
  } 

  return ret;

}

#if OSALARM_NUMBER_OF_ALARMS 
TickType IncrementCounter(AlarmType AlarmID, TickType Increment_value){

  //AlarmType AlarmID;
  TickType MinimalCount = -1;
  TickType Temp;

  //increment counter time
	Alarms[AlarmID].OsActionInfo.OsAlarmCounter->Time++;

  //check overflow
	while (Alarms[AlarmID].OsActionInfo.OsAlarmCounter->Time >= Alarms[AlarmID].OsActionInfo.OsAlarmCounter->OsCounterMaxAllowedValue)
	{
	        // Wrap around the counter value to zero
		      Alarms[AlarmID].OsActionInfo.OsAlarmCounter->Time -= Alarms[AlarmID].OsActionInfo.OsAlarmCounter->OsCounterMaxAllowedValue;
  }

  /*/
  for(int i = 0; i < allarm count; i++)
  {
    AlarmID = get el id mn struct el counter

    if(Alarms[AlarmID].AlarmState = Enable)
    {
      Temp = IncrementAlarm(AlarmID, Increment_Value);

      if(MinimalCount > Temp)
      {
        MinimalCount = Temp;
      }
      else
      {

      }
    }


  }
  */

  if(Alarms[AlarmID].AlarmState = Enable)
    {
      Temp = IncrementAlarm(AlarmID, Increment_value);

      if(MinimalCount > Temp)
      {
        MinimalCount = Temp;
      }
      else
      {

      }
    }

  return MinimalCount;
}
#endif


#if OSALARM_NUMBER_OF_ALARMS 

void Alarm_init(void)
{

AlarmType AlarmID;
for(AlarmID = 0; AlarmID < OSALARM_NUMBER_OF_ALARMS; AlarmID++){

  //create counter ll alarm dah

  if(Alarms[AlarmID].Alarmautostar == True){


    SetRelAlarm(AlarmID, Alarms[AlarmID].AlarmTime, Alarms[AlarmID].AlarmCycleTime);

  }

}

}
#endif

#if OSALARM_NUMBER_OF_ALARMS

TickType IncrementAlarm(AlarmType AlarmID, TickType Increment_value){

  TickType RestIncrement;
  TickType AlarmCount;
  TickType CounterIncrement;

  //init arlarms count
  AlarmCount = 0;


   //check if the increment is smaller than the expiration time 
  if (Alarms[AlarmID].AlarmTime > Increment_value){

    //decrement the alarm
    Alarms[AlarmID].AlarmTime -= Increment_value;

    // alarm will not expire
    RestIncrement = Alarms[AlarmID].AlarmTime;

  }
  else
  {

    //check if alarm is cyclic or single shot

    //Single Shot
    if(Alarms[AlarmID].AlarmCycleTime == 0){

      //in case of single shot, expires 1 time
      AlarmCount = 1;

      //set time to zero
      Alarms[AlarmID].AlarmTime = 0;

      //disable the alarm
      Alarms[AlarmID].AlarmState = Disable;

      //set rest of increment to zero
      RestIncrement = 0;
    }

    else
    {

      //Cyclic Alarm

      while(Alarms[AlarmID].AlarmTime <= Increment_value){

        //add cycle time
        Alarms[AlarmID].AlarmTime += Alarms[AlarmID].AlarmCycleTime;

        //increment Alarms expiration times
        AlarmCount ++;
      }

      //decrement the alarm
      Alarms[AlarmID].AlarmTime -= Increment_value;

      // alarm will not expire
      RestIncrement = Alarms[AlarmID].AlarmTime;

    }

    //Alarm Actions

    if(Alarms[AlarmID].OsAction == OsAlarmIcrementCounter)
    {
      // call counter increment function
      CounterIncrement = IncrementCounter(AlarmID, AlarmCount); 

      RestIncrement += Alarms[AlarmID].AlarmCycleTime * (CounterIncrement -1 );

    }

    else
    {
      for(; AlarmCount >0; AlarmCount--)
      {

        switch (Alarms[AlarmID].OsAction)
        {
            case OsAlarmActiveTask:

              //activate task  
              ActivateTask(Alarms[AlarmID].OsActionInfo.TaskID);

              break;

      //callback function
            case OsAlarmCallback:

              if(Alarms[AlarmID].OsActionInfo.OsAlarmCallbackFunction != NULL_PTR)
              {

                Alarms[AlarmID].OsActionInfo.OsAlarmCallbackFunction();
          
              }


              break;
//#if ll events
            case OsAlarmSetEvent:

              //set event
              SetEvent(Alarms[AlarmID].OsActionInfo.TaskID, Alarms[AlarmID].OsActionInfo.Event);

              break;

      
            default:
              break;
          }


      }
      

    }



  }
  return RestIncrement;

}
#endif