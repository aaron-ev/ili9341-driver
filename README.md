
# TFT ili9341 driver for STM32f4xx microcontrollers

## STM32F4

The Arm® Cortex®-M4-based STM32F4 MCU series leverages ST’s NVM technology and ART Accelerator™ to reach the industry’s highest benchmark scores for Cortex-M-based microcontrollers with up to 225 DMIPS/608 CoreMark executing from Flash memory at up to 180 MHz operating frequency. The following image shows the different series. 

![STM32 series image](/docs/images/STM32F4_series.jpg)

## Hardware Abstraction Layer (HAL)
The [HAL driver layer](https://www.st.com/resource/en/user_manual/um1725-description-of-stm32f4-hal-and-lowlayer-drivers-stmicroelectronics.pdf) provides a simple, generic multi-instance set of APIs (application programming interfaces) to interact
with the upper layer (application, libraries and stacks). The HAL driver APIs are split into two categories: generic APIs, which
provide common and generic functions for all the STM32 series and extension APIs, which include specific and customized
functions for a given line or part number.

The HAL drivers include a complete set of ready-to-use APIs that simplify the user
application implementation. For example, the communication peripherals contain APIs to initialize and configure the peripheral,
manage data transfers in polling mode, handle interrupts or DMA, and manage communication errors.

## ILI9341

**ILI9341** is a 262,144-color single-chip SOC driver for a-TFT liquid crystal display 
with resolution of 240RGBx320 dots, comprising a 720-channel source driver, a 320-channel gate driver, 172,800 bytes GRAM for graphic display data of 240RGBx320 dots, and power supply circuit.

ILI9341 supports parallel 8-/9-/16-/18-bit data bus MCU interface, 6-/16-/18-bit data bus RGB interface and 3-/4-line **serial peripheral interface (SPI)** to which this driver is created.

There are three main pin groups in the following image:

* Pins for the LCD 
* Pins for the touchscreen
* Pins for the SD card

![board](/docs/images/board.png)

For now, just the pins for the LCD will explain (The driver is still in development phase).

LCD pin definitions

| Pin          |Description                                                               |
|--------------|--------------------------------------------------------------------------|
| VCC          |    Power (3.5~5V)                                                        |
| GND          |    Ground                                                                |
| CS           |    Selection control signal                                              |
| RESET        |    Reset control signal                                                  |
| DC           |    Register/data register control signal                                 |
| SDI(MOSI)    |    SPI line to write data from a device to the lcd                       |
| SCK          |    SPI block signal                                                      |
| LED          |    Backlight control signal (If you do not need it, connect it to 3.3v)  |
| SDO(MISO)    |    SPI line to read data from the lcd to the device                      |