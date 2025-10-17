#include <string>
#include "Monitor.h"


Monitor::Monitor():lcd(0x27,16,2){}

void Monitor::Begin()
{
  lcd.init();
  lcd.backlight();
}

void Monitor::ShowTest()
{
  lcd.clear();
  lcd.print("Gr/min: ");
  lcd.setCursor(9,0);
  lcd.print("60.5");
  lcd.setCursor(0,1);
  lcd.print("Grammi:");
  lcd.setCursor(9,1);
  lcd.print("1234");
}

void Monitor::ShowData(scaleValue value, bool connected)
{
  lcd.clear();
  lcd.print("Gr/min: ");
  lcd.setCursor(9,0);
  lcd.print(value.gramsPerMinute);
  if (connected)
  {
    lcd.setCursor(14,0);
    lcd.print(" N");
  }
  lcd.setCursor(0,1);
  lcd.print("Grammi:");
  lcd.setCursor(9,1);
  lcd.print(value.grams);
}

void Monitor::SplashScreen()
{
  lcd.print("FLAME SPRAY");
  lcd.setCursor(0,1);
  lcd.print("Analisi Delta Peso");
  delay(2000);
}

void Monitor::ShowText(const char* text, int row)
{
  if (row<0 || row>1) return;
  lcd.setCursor(0,row);
  lcd.print("                ");
  lcd.setCursor(0,row);
  lcd.print(text);
}
void Monitor::Clear()
{
  lcd.clear();
}