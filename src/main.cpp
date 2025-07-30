#include "Monitor.h"
#include "ComData.h"
#include "DataValue.h"
#include "Remote.h"


Monitor Oled;
int numero;
String buffer="";
String* stampa;
ComData ScaleSerial;
DataValue ValoreBilancia;
Remote WiFiRemote("192.168.7.155",5000);
unsigned long tempoprecedente=0;
const unsigned long intervallo=1000;
bool connected = false;

char c;
void setup() {
  // put your setup code here, to run once:
  Oled.Begin();
  Oled.SplashScreen();
  ScaleSerial.Begin();
  connected= WiFiRemote.Connect();
  delay(5000);
  Oled.ShowString("IP: " + WiFiRemote.GetIPAddress());
  delay(2000);
}

void loop() 
{
  if (connected) {
    Oled.ShowString("Connected to WiFi");
    delay(1000);
    WiFiRemote.SendMsg("Hello from Arduino");
    Oled.ShowString("Sending data to server...");
  } else {
    Oled.ShowString("WiFi connection failed");
    connected= WiFiRemote.Connect();
    delay(2000);
    Oled.ShowString("IP: " + WiFiRemote.GetIPAddress());
    delay(2000);
  }
  delay(2000);
  // unsigned long adesso=millis();
  // if (adesso-tempoprecedente>=intervallo)
  // {
  //   tempoprecedente=adesso;
  //   stampa=ScaleSerial.Receive();
  //   ValoreBilancia.putData(stampa);
  //   Oled.ShowData(ValoreBilancia.GetData());
  // }
}
