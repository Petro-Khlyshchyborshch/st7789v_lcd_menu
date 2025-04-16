/*
 * Menu.c
 *
 *  Created on: Apr 6, 2025
 *      Author: Petro
 */


#include "st7789.h"

/*
typedef struct
{
	char * text;
	uint16_t btnId;
} MenuItem;


void DrawMenu(MenuItem* MenuVector, uint16_t MenuVectorLen, FontDef font, uint16_t color)
{
	if(!MenuVector)
	{
		return;
	}

	MenuItem* MenuRow = MenuVector;
	uint16_t YSpace = font.height*0.2; // 20% of font.heigh for Y offset between row

	for(uint16_t i = 0; i<MenuVectorLen;i++)
	{
		uint16_t TextLen = ST7789_GetStringPixelSize(MenuRow->text, font);

		uint16_t XOffset = (ST7789_WIDTH-TextLen)/2;
		uint16_t YOffset = (font.height + YSpace) * i;
		ST7789_WriteString(XOffset, YOffset, MenuRow->text, font, WHITE, BLACK);
		MenuRow++;
	}
}

void Menu()
{

	MenuItem MenuVector[] =
	{
			{"Item 0",0},
			{"Item 1",1},
			{"Item 2",2}
	};

	DrawMenu(MenuVector,(sizeof(MenuVector)/sizeof(MenuItem)),Font_16x26,WHITE);






}

*/


typedef struct
{
    char *text;
    uint16_t btnId;
} MenuItem;

typedef enum
{
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_OK
} ButtonState;

int16_t currentSelection = 1; // Поточний вибір
uint16_t scrollOffset = 0;     // Зсув для прокручування меню


unsigned char isUp()
{
	return 0;
}
unsigned char isDown()
{
	return 1;
}

// Функція для малювання меню з прокручуванням
void DrawMenu(MenuItem* MenuVector, uint16_t MenuVectorLen,FontDef font, uint16_t color)
{
    if(!MenuVector)
    {
        return;
    }

    MenuItem* MenuRow = MenuVector;
    uint16_t YSpace = font.height * 0.2; // 20% від висоти шрифту для відстані між рядками

    // Розрахунок кількості видимих елементів на екрані
    uint16_t MAX_VISIBLE_ITEMS = ST7789_HEIGHT / (font.height + YSpace);

    // Перевірка циклічності для currentSelection
    if (currentSelection < 0)
    {
        currentSelection = MenuVectorLen - 1;  // Переходить до останнього елемента, якщо currentSelection < 0
        scrollOffset = MenuVectorLen - MAX_VISIBLE_ITEMS;  // Встановлює scrollOffset так, щоб показувати останні елементи
    }
    else if (currentSelection >= MenuVectorLen)
    {
        currentSelection = 0;  // Повертається на перший елемент
        scrollOffset = 0;  // Встановлює scrollOffset на початок
    }

    // Прокручування меню
    if ((scrollOffset + MAX_VISIBLE_ITEMS) <= currentSelection)
    {
        scrollOffset++;  // Збільшуємо scrollOffset, щоб перемістити меню вниз
    }

    if (scrollOffset > currentSelection)
    {
        scrollOffset--;  // Зменшуємо scrollOffset, щоб перемістити меню вверх
    }

    for(uint16_t i = 0; i < MAX_VISIBLE_ITEMS; i++)
    {
    	uint16_t itemIndex = scrollOffset + i;
    	if(itemIndex > MenuVectorLen)
    	{
    		break;
    	}

        uint16_t TextLen = ST7789_GetStringPixelSize(MenuRow[itemIndex].text, font);
        uint16_t XOffset = (ST7789_WIDTH - TextLen) / 2;
        uint16_t YOffset = (font.height + YSpace) * i;

        uint16_t textColor = (itemIndex == currentSelection) ? BLUE : WHITE;  // Виділений елемент червоним, інші білим


        //ST7789_Fill(0,YOffset,ST7789_WIDTH-1,YOffset+font.height,BLACK);

        ST7789_WriteString(XOffset, YOffset, MenuRow[itemIndex].text, font, textColor, BLACK);
    }

}

void Menu()
{
    // Ініціалізація початкових параметрів меню
    MenuItem MenuVector[] =
    {
        {"Item 0", 0},
        {"Item 1", 1},
        {"Item 2", 2},
        {"Item 3", 3},
        {"Item 4", 4},
        {"Item 5", 5},
        {"Item 6", 6},
        {"Item 7", 7},
        {"Item 8", 8},
        {"Item 9", 9},
        {"Item 10", 10},
        {"Item 11", 11}
    };

    // Спочатку малюємо меню
    DrawMenu(MenuVector, (sizeof(MenuVector)/sizeof(MenuItem)),Font_16x26, WHITE);
    HAL_Delay(500);
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
    {
    	currentSelection--;
    }
    else
    {
    currentSelection++;
    }

}




