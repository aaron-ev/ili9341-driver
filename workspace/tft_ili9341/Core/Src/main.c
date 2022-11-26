

#include <string.h>
#include <stdint.h>
#include "main.h"
#include "tft_ili9341.h"
#include "tft_ili9341_touch.h"

UART_HandleTypeDef huart;
extern SPI_HandleTypeDef hspi;

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
        HAL_GPIO_TogglePin(LED_BUILD_IN_BOARD_PORT, LED_BUILD_IN_BOARD_PIN);
    }
}

void SystemClock_Config(void){}


static void UART_Init(void)
{
    huart.Instance = USART2;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        Error_Handler();
    }
}   

static void GPIO_init(void)
{
    GPIO_InitTypeDef gpio_init_def  = {0};

    /*Configure LED built in the nucleo board*/
    gpio_init_def.Pin = LED_BUILD_IN_BOARD_PIN;
    gpio_init_def.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_def.Pull = GPIO_NOPULL;
    gpio_init_def.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_BUILD_IN_BOARD_PORT, &gpio_init_def);
}

void touchInit(void)
{
    GPIO_InitTypeDef gpioTouchConfig  = {0};

    /* TOUCH IRQ pin settings */
    gpioTouchConfig.Pin = ILI9341_TOUCH_IRQ_PIN_NUM;
    gpioTouchConfig.Mode = GPIO_MODE_IT_FALLING;
    gpioTouchConfig.Pull = GPIO_NOPULL;
    gpioTouchConfig.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ILI9341_TOUCH_IRQ_GPIO_PORT, &gpioTouchConfig);

    /* TOUCH CS pin settings */
    gpioTouchConfig.Pin = ILI9341_TOUCH_CS_PIN_NUM;
    gpioTouchConfig.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(ILI9341_TOUCH_CS_GPIO_PORT, &gpioTouchConfig);

    /* Enable interrups */
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

int main(void)
{
    char *msg_success = "Hello world!\n";
    uint16_t len_str_msg = strlen(msg_success);

    /*Low level initialization*/
    HAL_Init();

    /*Clock initialization*/
    SystemClock_Config();

    /*GPIOs initialization*/
    GPIO_init();

    /*UART initialization*/
    UART_Init();

    /* TFT ILI9341 initialization */
    tft_ili9341_init();
    /* Enable touch feature */
    touchInit();
    tft_ili9341_fill_screen(YELLOW);
    while (1)
    {
    }
}



/* Handle for touch IQR line */
 void EXTI0_IRQHandler(void)
 {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
 }

 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin)
 {
    //todo: read coordinates and display them on the screen
 }
