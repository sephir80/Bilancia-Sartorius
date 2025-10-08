#include "Monitor.h"
#include "ComData.h"
#include "DataValue.h"
#include "Algorithm.h"
#include "Network.h"

Monitor Display;
int numero;
int grammiFake;
unsigned long tempoprecedente=0;
const unsigned long intervallo=3000;
const int nElementi=15;
String buffer="";
String* stampa;
ComData ScaleSerial;
DataValue ValoreBilancia;
Algorithm Algoritmo(nElementi);
Network Rete("192.168.1.110",10500);


char c;
void setup() {
  // put your setup code here, to run once:
  Display.Begin();
  Display.SplashScreen();
  ScaleSerial.Begin();
  delay(2000);
  grammiFake=5000;
  Display.Clear();
  Display.ShowText("Connessione WiFi",0);
  delay(10000);
  if (Rete.Connect())
  {
    Display.ShowText("Connesso! IP:",0);
    Display.ShowText(Rete.getLocalIP().c_str(),1);
    delay(2000);
  }
  Serial.begin(9600);
  Serial.println("Setup completato");
}

void loop() 
{
  unsigned long adesso=millis();
  if (adesso-tempoprecedente>=intervallo)
  {
/*    grammiFake-=1;
    if (grammiFake==4790)
      grammiFake=4790;
    tempoprecedente=adesso;
    //ValoreBilancia.putData(ScaleSerial.Receive());
    ValoreBilancia.putDataFake(grammiFake);
    numero=Algoritmo.addDataPoint(ValoreBilancia.grams(),adesso)?Algoritmo.getGramsPerMinute():0;
    ValoreBilancia.setGramsPerMinute(numero);
    Display.ShowData(ValoreBilancia.GetData().back(),Rete.isConnected());*/
    Rete.sendData("Ciao Mondo",10);
    Serial.println("Pacchetto Inviato");
  }
}
