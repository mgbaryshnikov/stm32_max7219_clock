#ifndef MAX_FUNC_H
#define MAX_FUNC_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi1;

void send_all_data(uint8_t reg, uint8_t data);

void max_init();

void create_array(uint8_t (*arr)[8]);

void refresh_max(uint8_t (*arr)[8]);

void change_row(uint8_t (*arr)[8], uint8_t max_number, uint8_t row, uint8_t data);

void change_dot(uint8_t (*arr)[8], uint8_t max_number, uint8_t column, uint8_t row, uint8_t data);

void change_column(uint8_t (*arr)[8], uint8_t max_number, uint8_t column, uint8_t data);

void draw_disp(uint8_t (*arr)[8], uint8_t max_number, uint8_t *data);

void get_rx (uint8_t (*arr)[8], uint8_t max_number, char digit);

#endif