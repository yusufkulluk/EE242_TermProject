#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32l0xx_hal.h"  // Bu kesin olmalı

// LCD Pin tanımlamaları
#define LCD_RS_Pin GPIO_PIN_0
#define LCD_RS_GPIO_Port GPIOA
#define LCD_EN_Pin GPIO_PIN_1
#define LCD_EN_GPIO_Port GPIOA
#define LCD_D4_Pin GPIO_PIN_4
#define LCD_D4_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D5_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_6
#define LCD_D6_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_7
#define LCD_D7_GPIO_Port GPIOA

// LCD fonksiyon prototipleri
void lcd_init(void);
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_puts(char* str);
void lcd_clear(void);

#endif /* INC_LCD_H_ */

static void lcd_send_nibble(uint8_t nibble) {
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (nibble >> 0) & 0x01);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (nibble >> 1) & 0x01);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (nibble >> 2) & 0x01);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (nibble >> 3) & 0x01);

    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

void lcd_send_cmd(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd & 0x0F);
    HAL_Delay(2);
}

void lcd_send_data(uint8_t data) {
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
    HAL_Delay(2);
}

void lcd_puts(char* str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_clear(void) {
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_init(void) {
    HAL_Delay(50);
    lcd_send_cmd(0x02); // 4-bit başlat
    lcd_send_cmd(0x28); // 4-bit, 2 satır, 5x8
    lcd_send_cmd(0x0C); // Display ON, cursor OFF
    lcd_send_cmd(0x06); // Auto-increment cursor
    lcd_send_cmd(0x01); // Ekranı temizle
    HAL_Delay(2);
}
