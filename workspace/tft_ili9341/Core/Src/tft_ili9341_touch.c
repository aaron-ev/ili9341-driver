
#include "stm32f4xx_hal.h"
#include "tft_ili9341_touch.h"

#define ILI9341_TOUCH_MIN_RAW_X 1500
#define ILI9341_TOUCH_MAX_RAW_X 31000
#define ILI9341_TOUCH_MIN_RAW_Y 3276
#define ILI9341_TOUCH_MAX_RAW_Y 30110

#define READ_X 0xD0
#define READ_Y 0x90

static void ili9341_selectTouchChip(void)
{
    HAL_GPIO_WritePin(ILI9341_TOUCH_CS_GPIO_PORT, ILI9341_TOUCH_CS_PIN_NUM, GPIO_PIN_RESET);
}

static void ili9341_unselectTouchChip(void)
{
    HAL_GPIO_WritePin(ILI9341_TOUCH_CS_GPIO_PORT, ILI9341_TOUCH_CS_PIN_NUM, GPIO_PIN_SET);
}

TouchStatus ili9341_isTouchPressed(void)
{
    return HAL_GPIO_ReadPin(ILI9341_TOUCH_IRQ_GPIO_PORT, ILI9341_TOUCH_IRQ_PIN_NUM) == GPIO_PIN_RESET;
}

TouchStatus ili93411_getTouchXY(uint16_t* x, uint16_t* y)
{
    static const uint8_t cmd_read_x[] = { READ_X };
    static const uint8_t cmd_read_y[] = { READ_Y };
    static const uint8_t zeroes_tx[] = { 0x00, 0x00 };
    uint32_t raw_x;
    uint32_t raw_y;
    uint32_t avg_x = 0;
    uint32_t avg_y = 0;
    uint8_t nsamples = 0;
    uint8_t i;

    ili9341_selectTouchChip();
    for ( i = 0; i < 16; i++ )
    {
        if(!ili9341_isTouchPressed())
        {
            break;
        }
        nsamples++;
        HAL_SPI_Transmit(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)cmd_read_y, sizeof(cmd_read_y), HAL_MAX_DELAY);
        uint8_t y_raw[2];
        HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)zeroes_tx, y_raw, sizeof(y_raw), HAL_MAX_DELAY);
        HAL_SPI_Transmit(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)cmd_read_x, sizeof(cmd_read_x), HAL_MAX_DELAY);
        uint8_t x_raw[2];
        HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)zeroes_tx, x_raw, sizeof(x_raw), HAL_MAX_DELAY);
        avg_x += (((uint16_t)x_raw[0]) << 8) | ((uint16_t)x_raw[1]);
        avg_y += (((uint16_t)y_raw[0]) << 8) | ((uint16_t)y_raw[1]);
    }
    ili9341_unselectTouchChip();
    if(nsamples < 16)
    {
        return TOUCH_NO_PRESSED;
    }

    raw_x =  ( avg_x / 16);
    if ( raw_x < ILI9341_TOUCH_MIN_RAW_X)
    {
        raw_x = ILI9341_TOUCH_MIN_RAW_X;
    }
    if ( raw_x > ILI9341_TOUCH_MAX_RAW_X )
    {
        raw_x = ILI9341_TOUCH_MAX_RAW_X;
    }

    raw_y =  ( avg_y / 16  );
    if ( raw_y < ILI9341_TOUCH_MIN_RAW_X )
    {
        raw_y = ILI9341_TOUCH_MIN_RAW_Y;
    }
    if ( raw_y > ILI9341_TOUCH_MAX_RAW_Y )
    {
        raw_y = ILI9341_TOUCH_MAX_RAW_Y;
    }

    *x =  ( raw_x - ILI9341_TOUCH_MIN_RAW_X  ) * ( ILI9341_TOUCH_WEIGHT / ( ILI9341_TOUCH_MAX_RAW_X - ILI9341_TOUCH_MIN_RAW_X ));
    *y =  ( raw_y - ILI9341_TOUCH_MIN_RAW_Y  ) * ( ILI9341_TOUCH_HEIGHT / ( ILI9341_TOUCH_MAX_RAW_Y - ILI9341_TOUCH_MIN_RAW_Y ));

    return TOUCH_PRESSED;
}

