#include "Arduino.h"
#include "ComData.h"

ComData::ComData()
{

}

void ComData::Begin()
{
  Serial1.begin(9600);
  Serial.begin(9600);

}

String* ComData::Receive()
{
  static String messaggio[8];
  int i = 0;
  Serial1.write(command,sizeof(command));
 // Serial.println("Attendo 8 righe...");
  while (i < 8)
  {
    if (Serial1.available()>0)
    {
      messaggio[i] = Serial1.readStringUntil('\n'); 
      messaggio[i].trim(); 
      Serial.print("Letto messaggio[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.println(messaggio[i]);
      i++;
    }
  }

  return messaggio;
}

void ComData::Send(String *str)
{
  for (int j =0;j<7;j++)
  {
    Serial.println(str[j]);
  }
}

void ComData::SendTest(String str)
{
  Serial.println(str.c_str());
}