/*
 * KBI.c
 *
 *  Created on: Sep 26, 2013
 *      Author: B46911
 */

#include "KBI.h"
#include "GPIO.h"


/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/
pt2FuncU8 KBI_Callback;//等价于void(*KBI_Callback)(UINT8);

/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/
void KBI0_IRQHandler(void);
int MODE = 0;

/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/


/**********************************************************************************************
* Global functions
**********************************************************************************************/


/***********************************************************************************************
*
* @brief    KBI_Init - Enable Keyboard interrupts on channels 24 and 25 (SW1 and SW2)
* @param    none
* @return   none
*
************************************************************************************************/
void KBI_Init()
{

    SIM_SCGC |=  SIM_SCGC_KBI0_MASK;   /* Enable bus clock on KBI0 */
    KBI0_SC = 0;                       /* Clearing mechanism 清算机制*/
    KBI0_ES |= KBI_ES_KBEDG(0x200000);    /* Polarity setting, falling edge low level ,SW1 极性设置，下降沿低电平，SW1。*/
    //KBI0_ES |= KBI_ES_KBEDG(0x2000000);    /* Polarity setting,falling edge low level,SW2 */
    KBI0_PE |= KBI_PE_KBIPE(0x200000);   /* Enable KBI0 channel 21 , SW1 */
    //KBI0_PE |= KBI_PE_KBIPE(0x2000000);   /* Enable KBI0 channel 25 , SW2 */
    KBI0_SC = 0;                        /* Clearing flags*/
    KBI0_SC |= KBI_SC_RSTKBSP_MASK;     /* Clearing RSTKBSP bit*/
    KBI0_SC |= KBI_SC_KBIE_MASK;  /* Enable  KBI0 Interrupts */

}
/***********************************************************************************************
*
* @brief    KBI_SetCallback - Set a callback function to execute on a falling edge of an enabled KBI pin
* @param    pointer to function with an UINT8 argument
* @return   none
*
************************************************************************************************/

void KBI_SetCallback(pt2FuncU8 ptr)//(pt2FuncU8 ptr)等价于void(*ptr)(UINT8);
{
    KBI_Callback = ptr;
}


/***********************************************************************************************
*
* @brief    KBI0_IRQHandler - KBI interrupt routine, calls the user callabck
* @param    none
* @return   none
*
************************************************************************************************/
void KBI0_IRQHandler()

{

    KBI0_SC |= KBI_SC_KBACK_MASK;   /*Clear flag*/


    if ((KBI0_SP & KBI_SP_SP(0x200000))) /* If SW1 has been pressed */
    {
        KBI_Callback(0);

    }

    if ((KBI0_SP & KBI_SP_SP(0x2000000))) /* If SW2 has been pressed */
    {
        KBI_Callback(1);

    }


}



/***********************************************************************************************
*
* @brief    KBI_Interrupt(UINT8 ch). Callback function called by the KBI module on each interrupt
* @param    KBI channel
* @return   none
*
************************************************************************************************/

void KBI_Interrupt(UINT8 ch)
{
    //int MODE = 1;
    switch (ch)
    {
    case 0:
          MODE = ~MODE ;
				//OUTPUT_CLEAR(PTF, PTF1);
        //OUTPUT_CLEAR(PTF, PTF0);
      if (MODE)
        {
            OUTPUT_SET(PTF, PTF1); //电机使能
            OUTPUT_SET(PTF, PTF0);
					//OUTPUT_SET(PTG,PTG1);
        }
        else
        {
            OUTPUT_CLEAR(PTF, PTF1);
            OUTPUT_CLEAR(PTF, PTF0);
					//OUTPUT_CLEAR(PTG,PTG1);
        }
        break;
        //case 1:
        //OUTPUT_CLEAR(PTF,PTF1);
        //OUTPUT_CLEAR(PTF,PTF0);
        //break;

    }
}




