#include <string>
#include "clib/u8g2.h"
#include "Monitor.h"

Monitor::Monitor():u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE){}

void Monitor::Begin()
{
  u8g2.begin();
}

void Monitor::ShowTest()
{

    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_6x13_me);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(0,9,"18/07/2025");
    u8g2.drawStr(90,9,"12:34");
    u8g2.drawLine(0,11,128,11);
    u8g2.setFont(u8g2_font_inb33_mn);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(20,49,"40");
    u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(80,40,"gr/min ");
    u8g2.drawLine(0,51,128,51);
    u8g2.setFont(u8g2_font_6x13_me);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(0,63,"peso attuale");
    u8g2.drawStr(90,63,"1234 ");
    u8g2.sendBuffer();					// transfer internal memory to the display
}

void Monitor::ShowData(scaleValue value)
{

    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_6x13_me);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(0,9,value.Date.c_str());
    u8g2.drawStr(90,9,value.Time.c_str());
    u8g2.drawLine(0,11,128,11);
    u8g2.setFont(u8g2_font_inb33_mn);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(20,49,std::to_string(value.gramsPerMinute).c_str());
    u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(80,40,"gr/min ");
    u8g2.drawLine(0,51,128,51);
    u8g2.setFont(u8g2_font_6x13_me);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
    u8g2.drawStr(0,63,"peso attuale");
    u8g2.drawStr(90,63,std::to_string(value.grams).c_str());
    u8g2.sendBuffer();					// transfer internal memory to the display

}

void Monitor::SplashScreen()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_courB14_tf);
  u8g2.drawStr(2, 12,"FLAME SPRAY");
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font    u8g2.drawStr(0,10,buffer.c_str());	// write something to the internal memory
  u8g2.drawStr(7, 30,"Analisi Delta Peso");
  u8g2.drawStr(0, 60,"ver 2.0.0");          
  u8g2.sendBuffer();
}

void Monitor::ShowString(const String &str)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x13_me);
  u8g2.drawStr(0, 10, str.c_str());
  u8g2.sendBuffer();
}