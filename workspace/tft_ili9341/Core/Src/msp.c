#include "main.h"

void HAL_MspInit(void)
{
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_def  = {0};

    __HAL_RCC_USART2_CLK_ENABLE();

    /*UART initialization*/
    gpio_init_def.Pin = UART_TX_PIN;
    gpio_init_def.Mode = GPIO_MODE_AF_PP;
    gpio_init_def.Pull = GPIO_PULLUP;
    gpio_init_def.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_init_def.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &gpio_init_def);
    gpio_init_def.Pin = UART_RX_PIN;
    HAL_GPIO_Init(GPIOA, &gpio_init_def);

    /* NVIC initializations*/
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    HAL_NVIC_SetPriority(USART2_IRQn,15,0);
}
