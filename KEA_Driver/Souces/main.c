#include "CLK.h"
#include "derivative.h"
#include "GPIO.h"
#include "FTM.h"
#include "ADC.h"
#include "UART.h"
#include "stdio.h"
#include "motor_strategy.h"
#include "KBI.h"
/*
    Private funtion
*/
#ifdef  __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
#endif /* __GNUC__ */

void Enable_Interrupt(UINT8 vector_number);
void Enable_Interrupt(UINT8 vector_number);
void Uart_Interrupt(UINT8 data);
//void delay (uint32_t i);

int position_now;
int position_old;

void KBI_Interrupt(UINT8 ch);

int main()
{
    int counter = 0;

    Clk_Init();             /* Configure clocks to run at 20 Mhz */
    GPIO_Init();        /* Configure button pins as inputs and LED pins as outputs */
    UART_Init();
    KBI_Init();
    ADC_Init(8, EIGHT_BIT); /* Configure ADC channel 3 in 8-bit resolution mode 配置ADC通道10在12位分辨率模式,通道10既是选择引脚，12位既是2^12=4096只能打印小于4096的值*/
    ADC_Init(9, EIGHT_BIT);
    Uart_SetCallback(Uart_Interrupt); /* Set the callback function that the UART driver will call when receiving a char */
    NVIC_EnableIRQ(UART1_IRQn);
    PWM8khz_Init(10);
    PWM8khz_Init_2(10);
    LED0_OFF;

    Uart_PutString("HELLO WOLD\r\n");
    KBI_SetCallback(KBI_Interrupt);   /* Set the KBI callback function to be called on each button press */
    NVIC_EnableIRQ(KBI0_IRQn);    /* Enable KBI0 Interrupt */

    for (;;)
    {
        counter++;


        position_now = ADC_Get_diff_pos(8, 9);      //计算据距离差值
        motor_strategy(position_now);                       //计算电机差速   diff_pos=position_now
			
        
			
        position_old = position_now;

        printf("num = %d , pos = %d \r\n", counter, position_old); //打印温度模拟量
    }
}
PUTCHAR_PROTOTYPE
{
    //Place your implementation of fputc here
    Uart_SendChar(ch);
    return ch;
}


void Uart_Interrupt(UINT8 data)
{
    Uart_SendChar(data); /* Echos data that is received*/
}

/*void delay(uint32_t i)
{
    while(i--);
}*/

