/*
 * ADC.c
 *
 *  Created on: Sep 24, 2013
 *      Author: B46911
 */



#include "ADC.h"

/**********************************************************************************************
* External objects
**********************************************************************************************/


/**********************************************************************************************
* Global variables
**********************************************************************************************/


/**********************************************************************************************
* Constants and macros
**********************************************************************************************/


/**********************************************************************************************
* Local types
**********************************************************************************************/


/**********************************************************************************************
* Local function prototypes
*********************************************************************************************/


/**********************************************************************************************
* Local variables
**********************************************************************************************/


/**********************************************************************************************
* Local functions
**********************************************************************************************/

/***********************************************************************************************
*
* @brief    ADC_Init - Initiates the Channel to read the value of the ADC channel
*
* @param    Channel to init and resolution
* @return   none
*
************************************************************************************************/
void ADC_Init(UINT8 channel, UINT8 mode)
{
    SIM_SCGC |= SIM_SCGC_ADC_MASK;                /* Enable bus clock in ADC*/
    /*ϵͳʱ��ѡͨADC�Ĵ���*/
    ADC_SC3 |= ADC_SC3_ADICLK(0x00);            /* Bus clock selected*/
    /* ����ʱ�ӡ���Ƶ������ģʽ   */
    ADC_SC2 |= 0x00;                            /* Software Conversion trigger, disable compare function*/
    /* �����������ȽϹ��ܽ���   */
    ADC_SC1 = 0 ;                               /* Enable ADC by setting ADCH bits as low*/
    /* */
    ADC_SC1 |= ADC_SC1_ADCO_MASK;               /* Continuous mode operation */
    /*��������ת�� */
    ADC_APCTL1 |= ADC_APCTL1_ADPC(1 << channel); /* Channel selection */
    /* ���ſ��ƣ�ģ����������ѡ��ͨ��ѡ��*/
    ADC_SC3 |= ADC_SC3_MODE(mode);              /* 8,10,12 bit mode operation */
    /* ת��ģʽѡ��mmode 8λת�� �� 0��10λ - 1��12λ - 2 */
}

/***********************************************************************************************
*
* @brief    ADC_Read - Read the selected ADC channel
* @param    ch - channel to read
* @return   result
*
************************************************************************************************/
UINT16 ADC_Read(UINT8 channel)
{

    ADC_SC1 = ADC_SC1_ADCH(channel);        /* Select channel to read */
    while (!(ADC_SC1 & ADC_SC1_COCO_MASK)); /* Wait conversion to complete */
    return ADC_R;                           /* Return adc value */

}
/***********************************************************************************************
*
* @brief    ADC_Get_diff_pos
* @param    ch - channel to read
* @return   result
*
************************************************************************************************/
int ADC_Get_diff_pos(UINT8 channel_l, UINT8 channel_r)
{
    int dis_l, dis_r;
    //dis_l = normalization(channel_l);   //���������д����ADC��ȡ�ĵ��ֵת��Ϊλ��
    // dis_r = normalization(channel_r);
    dis_l = ADC_Read(channel_l) * (-0.009) + 22;
    dis_r = ADC_Read(channel_r) * (-0.0086) + 24;
		return (int)(dis_l - dis_r+2);        //���ز�ֵ
}