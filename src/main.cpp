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
const unsigned long intervallo=3000;
 const int nElementi=15;
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
  ora=RTCTime(Rete.SyncTime());
  RTC.setTime(ora);

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
    //ValoreBilancia.putData(ScaleSerial.Receive());
    ValoreBilancia.putDataFake(grammiFake);
 //   numero=Algoritmo.addDataPoint(ValoreBilancia.grams(),adesso)?Algoritmo.getGramsPerMinute():0;
    ValoreBilancia.setGramsPerMinute(numero);
  //  Display.ShowData(ValoreBilancia.GetData().back(),Rete.isConnected());
  
    Rete.sendData("192.168.7.101",10500,"Ciao Mondo",10);
    Serial.println("Pacchetto Inviato");
  }
}
