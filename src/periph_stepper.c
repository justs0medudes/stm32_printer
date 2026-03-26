/*
 * @file    periph_stepper.c
 * @date    25 March 2026
 * @author  Justsomedudes
 */

#include "../inc/periph_stepper.h"

#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

#define PIN1_SET GPIOB->BSRR = (1 << 0) // pin 1 set
#define PIN1_RESET GPIOB->BSRR = (1 << (0 + 16)) // pin 1 reset
#define PIN2_SET GPIOB->BSRR = (1 << 1) // pin 2 set
#define PIN2_RESET GPIOB->BSRR = (1 << (1 + 16)) // pin 2 reset
#define PIN3_SET GPIOB->BSRR = (1 << 2) // pin 3 set
#define PIN3_RESET GPIOB->BSRR = (1 << (2 + 16)) // pin 3 reset
#define PIN4_SET GPIOB->BSRR = (1 << 10) // pin 4 set
#define PIN4_RESET GPIOB->BSRR = (1 << (10 + 16)) // pin 4 reset

static const uint8_t step_sequence[8][4] = {
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1}
};

// one step here will output exactly the combinations mapped in step_sequence (lowest level pin state)
static void stepper_handle(uint8_t step) {
    if (step_sequence[step][0]) PIN1_SET; else PIN1_RESET;
    if (step_sequence[step][1]) PIN2_SET; else PIN2_RESET;
    if (step_sequence[step][2]) PIN3_SET; else PIN3_RESET;
    if (step_sequence[step][3]) PIN4_SET; else PIN4_RESET;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        static uint8_t step = 0;
        int8_t dir = 1; // or -1
        stepper_handle(step);
        step = (step + dir + 8) % 8;
    }
}
