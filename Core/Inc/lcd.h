#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32l0xx_hal.h"

void lcd_init(void);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_puts(char* str);
void lcd_clear(void);

#endif /* INC_LCD_H_ */
