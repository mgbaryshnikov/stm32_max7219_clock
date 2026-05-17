#include "../Inc/aux_func.h"

uint8_t get_disp(uint8_t max_number) {
    uint8_t mon_num = 1;
    if (max_number == 2) mon_num = 3;
    if (max_number == 3) mon_num = 5;
    if (max_number == 4) mon_num = 7;
    return mon_num;
}

uint8_t reverse_byte_mask(uint8_t b) {
    b = ((b & 0x55) << 1) | ((b & 0xAA) >> 1); 
    b = ((b & 0x33) << 2) | ((b & 0xCC) >> 2); 
    b = ((b & 0x0F) << 4) | ((b & 0xF0) >> 4); 
    return b;
}
