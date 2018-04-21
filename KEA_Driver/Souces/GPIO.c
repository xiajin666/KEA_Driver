#include "GPIO.h"

void GPIO_Init()
{
	CONFIG_PIN_AS_GPIO(PTG,PTG0,OUTPUT); /* Configure LED 0 (PTC0) as an output */
	CONFIG_PIN_AS_GPIO(PTG,PTG1,OUTPUT); /* Configure LED 1 (PTC1) as an output */
	CONFIG_PIN_AS_GPIO(PTG,PTG2,OUTPUT); /* Configure LED 2 (PTC2) as an output */
//	CONFIG_PIN_AS_GPIO(PTC,PTC3,OUTPUT); /* Configure LED 3 (PTC3) as an output */
	
	CONFIG_PIN_AS_GPIO(PTC,PTC0,INPUT); /* ADC引脚初始化，温度采集 将PTC2设置为输入引脚*/	
	CONFIG_PIN_AS_GPIO(PTC,PTC1,INPUT);
	ENABLE_INPUT(PTC,PTC0);			 /* Enable input SW1 对PTC2进行输入使能*/	
	ENABLE_INPUT(PTC,PTC1);
	CONFIG_PIN_AS_GPIO(PTF,PTF0,OUTPUT);//
	CONFIG_PIN_AS_GPIO(PTF,PTF1,OUTPUT);
	OUTPUT_SET(PTF,PTF1);//电机使能
	OUTPUT_SET(PTF,PTF0);
	
	//OUTPUT_CLEAR(PTF,PTF1);
	//OUTPUT_CLEAR(PTF,PTF0);
	
	CONFIG_PIN_AS_GPIO(PTC,PTC5,INPUT); /* Configure SW1 (PTD0) as an input */	
	//CONFIG_PIN_AS_GPIO(PTD,PTD1,INPUT); /* Configure SW2 (PTD1) as an input */
	ENABLE_INPUT(PTC,PTC5);			 /* Enable input SW1*/	
	//ENABLE_INPUT(PTD,PTD1);			/*  Enable input SW2*/
	
	//OUTPUT_CLEAR(PTF,PTF1);
	//OUTPUT_CLEAR(PTF,PTF0);
	
	OUTPUT_SET(PTG,PTG0);//LED使能
  OUTPUT_SET(PTG,PTG1);
	OUTPUT_SET(PTG,PTG2);
	
	LED0_ON;							/* Turn off LED0 */
	LED1_ON;							/* Turn off LED1 */
	LED2_ON;							/* Turn off LED2 */
	//LED3_OFF;							/* Turn off LED3 */

}
