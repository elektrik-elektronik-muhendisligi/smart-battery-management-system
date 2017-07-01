/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"
#include "init.h"
#include "fsm.h"

void main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_CAN_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USART3_UART_Init();

 State currentState = idle;

  while (1)
  {
    currentState = (State)currentState();
  }

}

State idle(void){
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 0);
  return (State)start;
}

State start(void){
  HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 0); 
  return (State)measure;
}

State measure(void){
  HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 0);   
  return (State)estimate_soc;
}

State estimate_soc(void){
  HAL_GPIO_WritePin(GPIOC, RLED2_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, RLED2_Pin, 0); 
  return (State)compute_resistance;

}

State compute_resistance(void){
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 1); 
  HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 0); 
  HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 0); 
  return (State)compute_capacity;
}

State compute_capacity(void){
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 1); 
  HAL_GPIO_WritePin(GPIOC, RLED2_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 0); 
  HAL_GPIO_WritePin(GPIOC, RLED2_Pin, 0); 
  return (State)balancing;
}

State balancing(void){
  HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 1); 
  HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 0); 
  HAL_GPIO_WritePin(GPIOC, RLED1_Pin, 0); 
  return (State)send_data;

}
State send_data(void){
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 1); 
  HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 1); 
  HAL_Delay(1000);
  HAL_GPIO_WritePin(GPIOC, GLED1_Pin, 0); 
  HAL_GPIO_WritePin(GPIOC, GLED2_Pin, 0); 
  return (State)shutdown;

}

State shutdown(void){
  HAL_Delay(1000);
  return (State)idle;
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
