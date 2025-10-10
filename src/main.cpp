#include "Monitor.h"
#include "ComData.h"
#include "DataValue.h"
#include "Algorithm.h"
#include "Network.h"
#include <RTC.h>
#include "ntpClient.h"



Monitor Display;
int numero;
int grammiFake;
unsigned long tempoprecedente=0;
const unsigned long intervallo=500;
 const int nElementi=30;
String buffer="";
String* stampa;
ComData ScaleSerial;
DataValue ValoreBilancia;
Algorithm Algoritmo(nElementi);

//impostazioni wifi
IPAddress localIP(192,168,6,30);
IPAddress gateway(192,168,6,254);
IPAddress subnet(255,255,255,0);
IPAddress primaryDNS(192,168,6,254);

//Network Rete(localIP,gateway, subnet, primaryDNS);
Network Rete;
RTCTime ora;

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
  delay(1000);
  if (Rete.Connect())
  {
    Display.ShowText("Connesso! IP:",0);
    Display.ShowText(Rete.getLocalIP().c_str(),1);
    delay(4000);
  }
  Serial.begin(9600);
  Serial.println("Setup completato");
  RTC.getTime(ora);
  if (!RTC.isRunning()or (ora.getYear()<2025))
  {
    RTC.begin();
    Display.ShowText("Sync Time NTP",0);
    ora=RTCTime(Rete.SyncTime());
    RTC.setTime(ora);
  }
  RTC.getTime(ora);
  Display.ShowText("RTC Time:",0);

  Display.ShowText(ora.toString().c_str(),1);
  delay(4000);
}

void loop() 
{
   unsigned long adesso=millis();
  if (adesso-tempoprecedente>=intervallo)
  {
    tempoprecedente=adesso;
    grammiFake-=1;
    RTC.getTime(ora);
    //ValoreBilancia.putData(ScaleSerial.Receive());
    ValoreBilancia.putDataFake(ora.toString(),adesso, grammiFake);
    numero=Algoritmo.addDataPoint(ValoreBilancia.GetData());
    ValoreBilancia.setGramsPerMinute(numero);
    Display.ShowData(ValoreBilancia.GetData(),Rete.isConnected());
    String data=ValoreBilancia.GetDataToString();
    Rete.sendData("192.168.7.101",10500,data.c_str(),data.length());
    Serial.println("Pacchetto Inviato");
  }
}
