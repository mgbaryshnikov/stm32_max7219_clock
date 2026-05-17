#include "../Inc/max_func.h"
#include "../Inc/aux_func.h"
#include "main.h"
#include "stm32f103xb.h"


SPI_HandleTypeDef hspi1;

void send_all_data(uint8_t reg, uint8_t data) 
{
    uint8_t tx[8];

    for(int i = 0; i < 4; i++)
    {
        tx[i * 2]     = reg;
        tx[i * 2 + 1] = data;
    }

    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, tx, 8, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void max_init() {
  send_all_data(0x0C, 0x01);
  send_all_data(0x09, 0x00);
  send_all_data(0x0A, 0x04);
  send_all_data(0x0B, 0x07);
  send_all_data(0x0F, 0x00);
}


void create_array(uint8_t (*arr)[8]) {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      if (j % 2 == 0) arr[i][j] = i + 1;
      else arr[i][j] = 0b00000000;
    }
  }
}

void refresh_max(uint8_t (*arr)[8]) {
  for (uint8_t i = 0; i < 8; i++) {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, arr[i], 8, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
  }
}

void change_row(uint8_t (*arr)[8], uint8_t max_number, uint8_t row, uint8_t data) {
  uint8_t mon_num = get_disp(max_number);
  arr[row - 1][mon_num] = data;
}

void change_dot(uint8_t (*arr)[8], uint8_t max_number, uint8_t column, uint8_t row, uint8_t data) {
  uint8_t mon_num = get_disp(max_number);
  arr[column - 1][mon_num] &= ~(1 << (row - 1));
  arr[column - 1][mon_num] |= (data << (row - 1));
}

void change_column(uint8_t (*arr)[8], uint8_t max_number, uint8_t column, uint8_t data) {
  data = reverse_byte_mask(data);
  uint8_t mon_num = get_disp(max_number);
  for (uint8_t i = 0; i < 8; i++) {
    change_dot(arr, max_number, i + 1, column, ((data >> i) & 1));
  }
}

void draw_disp(uint8_t (*arr)[8], uint8_t max_number, uint8_t *data) {
  for (int i = 0; i < 8; i++) {
    if (max_number < 3) {
      change_row(arr, max_number, i + 1, data[i] << 2);
    }
    else {
      change_row(arr, max_number, i + 1, data[i]);
    }
  }
}