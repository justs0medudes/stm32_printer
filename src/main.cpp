/*
 * @file    main.cpp
 * @data    25 March 2026
 * @author  Justsomedudes
 *
 */
#include "stm32f4xx_hal.h"

#include "sys_clock.h"
#include "sys_gpio.h"
#include "sys_timer.h"

// TODO Write a prescaler to convert steps per seconds (steps/s) input into timer rate

int main()
{
    HAL_Init();
    clock_init();
    gpio_init();
    tim2_init();

    while (true)
    {   

    }
}

