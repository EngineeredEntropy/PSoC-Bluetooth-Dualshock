/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include "Arduino.h"
    #include "iprintf.h"

#ifdef __cplusplus
extern "C" {
#endif

	// PSoC include, this has to be wrapped
	//#include "project.h"

#ifdef __cplusplus
}
#endif
void delay(unsigned long value)
{
    //CyDelay(
    CyDelay( (uint32)value);
    //TCPWM_1_ReadCounter();
}

unsigned long milliValue = 0;
unsigned long lastMilli = 0;
unsigned long currentMilli = 0;
unsigned long milliCount = 0;
#define MAX_MILLI 0xFFFF

unsigned long millis(void)
{
    //iprintf("Time: %d\r\n",TCPWM_1_ReadCounter());
    currentMilli = Millis_Timer_ReadCounter();
    if(lastMilli>currentMilli)
        milliCount++;
    lastMilli = currentMilli;
    return currentMilli+milliCount*MAX_MILLI;
    
}