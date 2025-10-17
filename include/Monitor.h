//#include <Wire.h>
//#include <U8g2lib.h>
#include "DataValue.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


class Monitor
{
  private:
  LiquidCrystal_I2C lcd;  // set the LCD address to 0x27 for a 16 chars and 2 line display
 //   U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
  public:
    Monitor();
    void Begin();
    void ShowTest();
    void ShowData(scaleValue value,bool connected);
    void ShowText(const char* text, int row);
    void Clear();
    void SplashScreen();
};