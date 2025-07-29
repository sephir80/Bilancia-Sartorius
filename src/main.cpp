#include "Monitor.h"
#include "ComData.h"
#include "DataValue.h"


Monitor Oled;
int numero;
String buffer="";
String* stampa;
ComData ScaleSerial;
DataValue ValoreBilancia;
unsigned long tempoprecedente=0;
const unsigned long intervallo=1000;

char c;
void setup() {
  // put your setup code here, to run once:
  Oled.Begin();
  Oled.SplashScreen();
  ScaleSerial.Begin();
  delay(2000);

}

void loop() 
{
  unsigned long adesso=millis();
  if (adesso-tempoprecedente>=intervallo)
  {
    tempoprecedente=adesso;
    stampa=ScaleSerial.Receive();
    ValoreBilancia.putData(stampa);
    Oled.ShowData(ValoreBilancia.GetData());
  }
}
