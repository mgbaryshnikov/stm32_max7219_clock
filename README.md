# STM32 MAX7219 Clock

Simple digital clock based on STM32 and MAX7219.

Current time is sent from a Python script over UART to the STM32, then displayed on the MAX7219 LED matrix.

## Features

- Custom MAX7219 driver
- UART communication
- Python PC utility
- No external display libraries

## Hardware

- STM32F103C8T6
- MAX7219 LED matrix
- USB-UART adapter

## How to Run

1. Flash firmware to STM32
2. Connect UART adapter to PC
3. Run Python script:

```bash
python send_time.py
