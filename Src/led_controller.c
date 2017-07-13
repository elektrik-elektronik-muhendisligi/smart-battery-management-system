#include "gpio.h"

void led_flash(int led_combination){

    // Reset all LEDs
    HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 0); 
    HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 0);
    HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 0);
    HAL_GPIO_WritePin(GPIOC, RLED2_Pin, 0);

    // Turn on Green LED 1
    if(led_combination % 2) {
        HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 1); 
    }

    // Turn on Green LED 2
    if(led_combination == 2 || led_combination == 3 || led_combination == 6 
       || led_combination == 7 || led_combination == 10 || led_combination == 11
       || led_combination == 15) {

        HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 1); 
    }

    // Turn on Red LED 1
    if((led_combination >= 4 && led_combination <= 7) || led_combination >= 12){
        HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 1); 
    }

    // Turn on Red LED 2
    if(led_combination >= 8) {
        HAL_GPIO_WritePin(GPIOC, RLED2_Pin, 1); 
    }

    // Add 1s delay
    HAL_Delay(1000);
}