/*
 * ADC.h
 *
 *  Created on: Sep 24, 2013
 *      Author: B46911
 */

#ifndef ADC_H_
#define ADC_H_
/*******************************************************************************
* Includes
********************************************************************************/

#include "derivative.h"

	
/*******************************************************************************
* Constants
********************************************************************************/


/*******************************************************************************
* Macros
********************************************************************************/
#define EIGHT_BIT 	2
#define TEN_BIT 	1
#define TWELVE_BIT 	2
                
/*******************************************************************************
* Types
********************************************************************************/


/*******************************************************************************
* Variables
********************************************************************************/


/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Global Functions
********************************************************************************/
/***********************************************************************************************
*
* @brief    ADC_Init - Initiates the Channeln to read the value of the ADC channel
* 			 
* @param    Channel to init and resolution
* @return   none
*
************************************************************************************************/  
void ADC_Init(UINT8 channel, UINT8 mode);

/***********************************************************************************************
*
* @brief    ADC_Read - Read the selected ADC channel
* @param    ch - channel to read
* @return   result
*
************************************************************************************************/
UINT16 ADC_Read(UINT8 channel);
/***********************************************************************************************
*
* @brief    ADC_Get_diff_pos 
* @param    ch - channel to read
* @return   result
*
************************************************************************************************/
int ADC_Get_diff_pos(UINT8 channel_l ,UINT8 channel_r);

#endif /* ADC_H_ */
