#include "Monitor.h"
#include "ComData.h"
#include "DataValue.h"
#include "Algorithm.h"

Monitor Oled;
int numero;
int grammiFake;
unsigned long tempoprecedente=0;
const unsigned long intervallo=1000;
const int nElementi=15;
String buffer="";
String* stampa;
ComData ScaleSerial;
DataValue ValoreBilancia;
Algorithm Algoritmo(nElementi);


char c;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Inizializzazione...");
  Oled.Begin();
  Oled.SplashScreen();
  ScaleSerial.Begin();
  delay(2000);
  grammiFake=5000;
}

void loop() 
{
  unsigned long adesso=millis();
  if (adesso-tempoprecedente>=intervallo)
  {
    grammiFake-=1;
    if (grammiFake==4790)
      grammiFake=4790;
    tempoprecedente=adesso;
    //ValoreBilancia.putData(ScaleSerial.Receive());
    ValoreBilancia.putDataFake(grammiFake);
    numero=Algoritmo.addDataPoint(ValoreBilancia.grams(),adesso)?Algoritmo.getGramsPerMinute():0;
    ValoreBilancia.setGramsPerMinute(numero);
    Oled.ShowData(ValoreBilancia.GetData().back());
  }
}
