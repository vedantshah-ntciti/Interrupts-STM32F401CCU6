# STM32F401 Interrupts Learning Lab

This repository contains code examples and notes focused on understanding, configuring, and handling interrupts on the **STM32F401CCU6 (Cortex-M4)** microcontroller.

## 🚀 Covered Concepts
* **EXTI (External Interrupts):** Handling button presses via GPIO lines.
* **NVIC Configuration:** Setting interrupt.
* **SysTick Interrupt:** Basic system ticking and timekeeping.

## 🛠️ Hardware Used
* STM32F401CCU6 "Black Pill" development board.

## Tools used:
arm-none-eabi-gcc, arm-none-eabi-objdump, dfu-util and Makefile.

Linker and Startup code from official stm32 github repository.

You just upload to the board using the upload script, this reduces the need to type the command in the terminal again and again.
