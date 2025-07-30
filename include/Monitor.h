#include <Wire.h>
#include <U8g2lib.h>
#include "DataValue.h"


class Monitor
{
  private:
    U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
  public:
    Monitor();
    void Begin();
    void ShowTest();
    void ShowData(scaleValue value);
    void ShowString(const String &str);
    void SplashScreen();
};