#include "stm32f4xx_hal.h"

#include "sys_clock.h"
#include "sys_gpio.h"
#include "sys_timer.h"

#define MS 200
#define LED1_SET GPIOB->ODR |= (1 << 0);
#define LED1_RESET GPIOB->ODR &= ~(1 << 0);
#define LED1_TOGGLE GPIOB->ODR ^= (1 << 0);
#define LED2_SET GPIOB->ODR |= (1 << 1);
#define LED2_RESET GPIOB->ODR &= ~(1 << 1);
#define LED2_TOGGLE GPIOB->ODR ^= (1 << 1);
#define LED3_SET GPIOB->ODR |= (1 << 2);
#define LED3_RESET GPIOB->ODR &= ~(1 << 2);
#define LED3_TOGGLE GPIOB->ODR ^= (1 << 2);
#define LED4_SET GPIOB->ODR |= (1 << 10);
#define LED4_RESET GPIOB->ODR &= ~(1 << 10);
#define LED4_TOGGLE GPIOB->ODR ^= (1 << 10);


int main()
{
    HAL_Init();
    clock_init();
    gpio_init();
    tim2_init();
    while (true)
    {   
        //1+2
        LED1_SET;
        LED2_SET;
        LED3_RESET;
        LED4_RESET;
        HAL_Delay(MS);
        //2+3
        LED1_RESET;
        LED2_SET;
        LED3_SET;
        LED4_RESET;
        HAL_Delay(MS);
        //3+4
        LED1_RESET;
        LED2_RESET;
        LED3_SET;
        LED4_SET;
        HAL_Delay(MS);
        //4+1
        LED1_SET;
        LED2_RESET;
        LED3_RESET;
        LED4_SET;
        HAL_Delay(MS);
    }
}

