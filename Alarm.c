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
StatusType GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
  /* \req OSEK_Alarm_6: The system service StatusType
	 ** GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info )
	 ** shall be defined */

  // \req OSEK_Alarm_7: The GetAlarmBase API should return E_OK in Standard mode
  StatusType ret = E_OK;

#if (OS_EXTENDED_ERROR == TRUE)

  //check that the AlarmID is in range
  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    // \req OSEK_Alarm_8: The GetAlarmBase API should return E_OS_ID in Extended mode
    ret = E_OS_ID;

  }
  else

#endif
 {

    /* \req OSEK_Alarm_9: The system service GetAlarmBase reads the alarm base characteristics. 
    ** The return value Info is a structure in which the information of data type 
    ** AlarmBaseType is stored */


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
StatusType GetAlarm(AlarmType AlarmID, TickRefType Tick)
{
  /* \req OSEK_Alarm_1: The system service StatusType
	 ** GetAlarm ( AlarmType AlarmID, TickRefType Tick)
	 ** shall be defined */

  // \req OSEK_Alarm_2: The GetAlarm API should return E_OK in Standard mode
  StatusType ret = E_OK;
#if (OS_EXTENDED_ERROR == TRUE)

  //check that the AlarmID is in range
  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    // \req OSEK_Alarm_3: The GetAlarm API should return E_OS_ID in Extended mode
    ret = E_OS_ID;

  }
  else

#endif
 {
    //check if the alarm is not running
    if(Alarms[AlarmID].AlarmState == Disable)
    {

      // \req OSEK_Alarm_4: The GetAlarm API should return E_OS_NOFUNC in Standard mode if Alarm is not used
      ret = E_OS_NOFUNC;

    }
    else
    {
      /* \req OSEK_Alarm_5: The system service GetAlarm shall return 
      ** the relative value in ticks before the alarm AlarmID expires */
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
StatusType SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle)
{

  /* \req OSEK_Alarm_10: The system service StatusType
	 ** SetRelAlarm ( AlarmType AlarmID, TickType Increment, TickType Cycle )
	 ** shall be defined */

  // \req OSEK_Alarm_11: The SetRelAlarm API should return E_OK in Standard mode
  StatusType ret = E_OK;

#if (OS_EXTENDED_ERROR == TRUE)

  //check that the AlarmID is in range
  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {
    // \req OSEK_Alarm_13: The SetRelAlarm API may return E_OS_ID in Extended mode
    ret = E_OS_ID;
    
  }
  //check that increment and cycle are in range
  else if( ( increment < 0 ) || ( increment > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue) ) ||
            ( (cycle != 0) && 
              ( (cycle > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue)) ||
                (cycle < (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMinCycle)) ) ) )
            {

              // \req OSEK_Alarm_14: The SetRelAlarm API may return E_OS_VALUE in Extended mode
              ret = E_OS_VALUE;

            }

            else
#endif
            {
              //check if the alarm is running
              if(Alarms[AlarmID].AlarmState == Enable)
              {

               /* \req OSEK_Alarm_12: The SetRelAlarm API should 
               * return E_OS_STATE in Standard mode if Alarm is already in use */
               ret = E_OS_STATE; 

              }
              else
              {

                DISABLE_INTERRUPTS();

                //Enable Alarm
                Alarms[AlarmID].AlarmState = Enable;
                //Set Alarm
                Alarms[AlarmID].AlarmTime = increment;
                Alarms[AlarmID].AlarmCycleTime = cycle;

                ENABLE_INTERRUPTS();

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
StatusType SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle)
{
  /* \req OSEK_Alarm_15: The system service StatusType
	 ** SetAbsAlarm ( AlarmType AlarmID, TickType start, TickType Cycle )
	 ** shall be defined */

  // \req OSEK_Alarm_16: The SetAbsAlarm API should return E_OK in Standard mode
  StatusType ret = E_OK;


#if (OS_EXTENDED_ERROR == TRUE)

  //check that the AlarmID is in range
  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    // \req OSEK_Alarm_18: The SetAbsAlarm API may return E_OS_ID in Extended mode
    ret = E_OS_ID;
    
  }
  //check that increment and cycle are in range
  else if( ( start < 0 ) || ( start > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue) ) ||
            ( (cycle != 0) && 
              ( (cycle > (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue)) ||
                (cycle < (Alarms[AlarmID].OsAlarmCounterRef->OsCounterMinCycle)) ) ) )
            {

              // \req OSEK_Alarm_19: The SetAbsAlarm API may return E_OS_VALUE in Extended mode
              ret = E_OS_VALUE;

            }

            else
#endif
            {
              //check if the alarm is running
              if(Alarms[AlarmID].AlarmState == Enable)
              {
               
               /* \req OSEK_Alarm_17: The SetAbsAlarm API should 
               * return E_OS_STATE in Standard mode if Alarm is already in use */
               ret = E_OS_STATE; 

              }
              else
              {

            	  DISABLE_INTERRUPTS();

                //Enable Alarm
                Alarms[AlarmID].AlarmState = Enable;
                //Set Alarm
                Alarms[AlarmID].AlarmTime = Alarms[AlarmID].OsAlarmCounterRef->Time + start;
                Alarms[AlarmID].AlarmCycleTime = cycle;

                ENABLE_INTERRUPTS();

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
StatusType CancelAlarm(AlarmType AlarmID)
{
  /* \req OSEK_Alarm_20: The system service StatusType
	 ** CancelAlarm ( AlarmType AlarmID ) shall be defined */

  // \req OSEK_Alarm_21: The CancelAlarm API should return E_OK in Standard mode
  StatusType ret = E_OK;

#if (OS_EXTENDED_ERROR == TRUE)

  //check that the AlarmID is in range
  if(AlarmID >= OSALARM_NUMBER_OF_ALARMS)
  {

    // \req OSEK_Alarm_23: The CancelAlarm API may return E_OS_ID in Extended mode
    ret = E_OS_ID;

  }
  else

#endif
  {
    //check if the alarm is not running  
    if(Alarms[AlarmID].AlarmState == Disable)
    {

      /* \req OSEK_Alarm_22: The CancelAlarm API should 
      * return E_OS_NOFUNC in Standard mode if Alarm is not used */
      ret = E_OS_NOFUNC;

    }
    else
    {
      
      // \req OSEK_Alarm_24: The system service CancelAlarm shall cancel the alarm AlarmID
      Alarms[AlarmID].AlarmState = Disable;

    }
    
  } 

  return ret;

}

/************************************************************************************
* Service Name: IncrementCounter
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm 
*                  Increment_value - Value we will be using 
* Parameters (out): minimal increment
* Description: The system service used to increment the counter.
************************************************************************************/
#if OSALARM_NUMBER_OF_ALARMS 
TickType IncrementCounter(AlarmType AlarmID, TickType Increment_value)
{

  //AlarmType AlarmID;
  TickType MinimalCount = -1;
  TickType Temp;

  //increment counter time
	Alarms[AlarmID].OsActionInfo->OsAlarmCounter->Time++;

  //check overflow
	while (Alarms[AlarmID].OsActionInfo->OsAlarmCounter->Time >= Alarms[AlarmID].OsActionInfo->OsAlarmCounter->OsCounterMaxAllowedValue)
	{

    // Wrap around the counter value to zero
    Alarms[AlarmID].OsActionInfo->OsAlarmCounter->Time -= Alarms[AlarmID].OsActionInfo->OsAlarmCounter->OsCounterMaxAllowedValue;

  }

  /* Multiple of alarms on same counter
  for(int i = 0; i < allarm count; i++)
  {
    AlarmID = Counters[CounterID].AlarmRef[i];

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
    //Increment alarm and get the next alarm time
    Temp = AlarmManagement(AlarmID, Increment_value);

    //if the actual count is smaller
    if(MinimalCount > Temp)
    {
      //Set it as minimal count
      MinimalCount = Temp;

    }
    else
    {

    }
  }
  return MinimalCount;
}
#endif


/************************************************************************************
* Service Name: Alarm_init
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): None
* Parameters (out): None
* Description: The system service used to initialize the alarm.
************************************************************************************/
#if OSALARM_NUMBER_OF_ALARMS 
void Alarm_init(void)
{

  AlarmType AlarmID;
  for(AlarmID = 0; AlarmID < OSALARM_NUMBER_OF_ALARMS; AlarmID++){

    if(Alarms[AlarmID].Alarmautostar == True){

      SetRelAlarm(AlarmID, Alarms[AlarmID].AlarmTime, Alarms[AlarmID].AlarmCycleTime);

    }
  }

}
#endif


/************************************************************************************
* Service Name: AlarmManagement
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in): AlarmID - Reference to alarm 
*                  Increment_value - Value we will be using 
* Parameters (out): Rest of increment
* Description: The system service used to increment the alarm.
************************************************************************************/
#if OSALARM_NUMBER_OF_ALARMS
TickType AlarmManagement(AlarmType AlarmID, TickType Increment_value)
{

  TickType RestIncrement;
  TickType AlarmCount;
  TickType CounterIncrement;

  //Init arlarms count
  AlarmCount = 0;


   //Check if the increment is smaller than the expiration time 
  if (Alarms[AlarmID].AlarmTime > Increment_value){

    //Decrement the alarm
    Alarms[AlarmID].AlarmTime -= Increment_value;

    //Alarm will not expire
    RestIncrement = Alarms[AlarmID].AlarmTime;

  }
  else
  {

    //Check if alarm is cyclic or single shot

    //Single Shot
    if(Alarms[AlarmID].AlarmCycleTime == 0){

      //In case of single shot, expires 1 time
      AlarmCount = 1;

      //Set time to zero
      Alarms[AlarmID].AlarmTime = 0;

      //Disable the alarm
      Alarms[AlarmID].AlarmState = Disable;

      //Set rest of increment to zero
      RestIncrement = 0;
    }

    else
    {

      //Cyclic Alarm

      while(Alarms[AlarmID].AlarmTime <= Increment_value){

        //Add cycle time
        Alarms[AlarmID].AlarmTime += Alarms[AlarmID].AlarmCycleTime;

        //Increment Alarms expiration times
        AlarmCount ++;
      }

      //Decrement the alarm
      Alarms[AlarmID].AlarmTime -= Increment_value;

      //Alarm will not expire
      RestIncrement = Alarms[AlarmID].AlarmTime;

    }

    //Alarm Actions

    if(Alarms[AlarmID].OsAction == OsAlarmIcrementCounter)
    {

      //Call counter increment function
      CounterIncrement = IncrementCounter(AlarmID, AlarmCount); 
      //Re-calculate the rest of the increments
      RestIncrement += Alarms[AlarmID].AlarmCycleTime * (CounterIncrement -1 );

    }

    else
    {
      //Execute the alarm so many times as needed
      for(; AlarmCount >0; AlarmCount--)
      {
        //Check alarm actions
        switch (Alarms[AlarmID].OsAction)
        {
            case OsAlarmActiveTask:

              //Activate task  
              ActivateTask(Alarms[AlarmID].OsActionInfo->TaskID);
              break;

            case OsAlarmCallback:

              //Callback function
              if(Alarms[AlarmID].OsActionInfo->OsAlarmCallbackFunction != NULL_PTR)
              {
                Alarms[AlarmID].OsActionInfo->OsAlarmCallbackFunction();
              }
              break;

            case OsAlarmSetEvent:

              //Set event
              SetEvent(Alarms[AlarmID].OsActionInfo->TaskID, Alarms[AlarmID].OsActionInfo->Event);
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