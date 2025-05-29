#include "keypad.h"

/* --- Keypad pinleri --- */
#define ROW_NUM 4
#define COL_NUM 4

// Satır pinleri (ters sırada)
uint16_t row_pins[4] = {GPIO_PIN_3, GPIO_PIN_2, GPIO_PIN_1, GPIO_PIN_0};
GPIO_TypeDef* row_ports[4] = {GPIOB, GPIOB, GPIOB, GPIOB};

// Sütun pinleri (ters sırada)
uint16_t col_pins[4] = {GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_4};
GPIO_TypeDef* col_ports[4] = {GPIOB, GPIOB, GPIOB, GPIOB};


// Tuş haritası
char key_map[4][4] = {
    {'D','C','B','A'},
    {'#','9','6','3'},
    {'0','8','5','2'},
    {'*','7','4','1'}
};


char keypad_get_key(void)
{
    for (int row = 0; row < ROW_NUM; row++)
    {
        // Tüm satırları 1 yap
        for (int i = 0; i < ROW_NUM; i++)
        {
            HAL_GPIO_WritePin(row_ports[i], row_pins[i], GPIO_PIN_SET);
        }

        // Sadece seçili satırı 0 yap
        HAL_GPIO_WritePin(row_ports[row], row_pins[row], GPIO_PIN_RESET);

        for (int col = 0; col < COL_NUM; col++)
        {
            if (HAL_GPIO_ReadPin(col_ports[col], col_pins[col]) == GPIO_PIN_RESET)
            {
                HAL_Delay(150); // debounce
                return key_map[row][col];
            }
        }
    }

    return '\0'; // tuşa basılmadı
}
