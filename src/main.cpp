#include "Monitor.h"
#include "ComData.h"
#include "DataValue.h"
#include "Algorithm.h"
#include "Network.h"
#include <RTC.h>
#include "ntpClient.h"


int grammiFake=5000;
Monitor Display;
int numero;
unsigned long tempoprecedente=0;
const unsigned long intervallo=500;
const int nElementi=30;
char msg[128];

unsigned long adesso;
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
int nvariazioni=0;
char c;

void setup() {
  // put your setup code here, to run once:
  Display.Begin();
  Display.SplashScreen();
   ScaleSerial.Begin();
  delay(2000);
  // grammiFake=5000; // Removed unused test variable
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
  Display.ShowText("Attesa Bilancia",0);
  Display.ShowText("",1);
}

void loop() 
{

  adesso=millis();
  if (adesso-tempoprecedente>=intervallo*2)
  {
    tempoprecedente=adesso;
    if ((nvariazioni>0)and (nvariazioni<=30))
        grammiFake-=0;
    else if ((nvariazioni>30)and (nvariazioni<=150))
        grammiFake-=1;
    else if ((nvariazioni>150) and (nvariazioni<=270))
      grammiFake-=2;
    else if ((nvariazioni>270) and (nvariazioni<=330))
      grammiFake-=0;
    else if ((nvariazioni>330) and (nvariazioni<=390))
      grammiFake-=1;
      nvariazioni++;
  }
  if (adesso-tempoprecedente>=intervallo)
  {

    

    RTC.getTime(ora);
    
   //ValoreBilancia.putData(ora.toString(), adesso, ScaleSerial.Receive());
   ValoreBilancia.putDataFake(ora.toString(),adesso,abs(grammiFake+random(-1,+1)));
    ValoreBilancia.setGramsPerMinute(Algoritmo.addDataPoint(ValoreBilancia.GetData()));
    Display.ShowData(ValoreBilancia.GetData(),Rete.isConnected());
//     String data=ValoreBilancia.GetDataToString();
    ValoreBilancia.GetDataToBuffer(msg,sizeof(msg));
    Rete.sendData("192.168.1.110",10500,msg,strlen(msg));
  }
}
