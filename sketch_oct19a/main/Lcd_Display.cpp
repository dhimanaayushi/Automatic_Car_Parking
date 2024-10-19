#include "Lcd_Display.h"

LCD_I2C lcd(LCD_ADDRESS);

void lcdInit(void)
{
  lcd.begin();
  
}
