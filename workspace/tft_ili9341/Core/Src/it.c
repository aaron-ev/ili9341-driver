#include "main.h"
#include "stm32f4xx_it.h"

void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}
