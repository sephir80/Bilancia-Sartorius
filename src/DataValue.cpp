#include "DataValue.h"




DataValue::DataValue()
{
  int numero=sizeof(scaleValue);
  IDScale="";
}

void DataValue::putData(String data,unsigned int millis, String* buffer)
{

  Valore.Date=data;
  Valore.Time=millis;
  if (IDScale=="")
    IDScale=buffer[2].substring(12).c_str();
  Valore.grams=atoi(buffer[3].substring(12,16).c_str());
  Valore.gramsPerMinute=0;
}

void DataValue::putDataFake(String date,unsigned int time, int gr)
{
  unsigned long now=millis();
  this->Valore.Date=date;
  this->Valore.Time=time;
  if (IDScale=="")
    this->IDScale="FAKE";
  this->Valore.grams=gr;
  this->Valore.gramsPerMinute=0;
}

void DataValue::setGramsPerMinute(int grmin)
{
    Valore.gramsPerMinute=grmin;
}

scaleValue DataValue::GetData()
{
  return Valore;
}

/* String DataValue::GetDataToString()
{
  String result="";
  result.reserve(64);
  result.concat(IDScale.c_str());
  result.concat(";");
  result.concat(Valore.Date);
  result.concat(";");
  result.concat(Valore.Time);
  result.concat(";");
  result.concat(Valore.grams);
  result.concat(";");
  result.concat(Valore.gramsPerMinute);
  return result;
} */

void DataValue::GetDataToBuffer(char* buffer, size_t len)
{
  snprintf(buffer, len, "%s;%s;%u;%d;%d", IDScale.c_str(), Valore.Date.c_str(), Valore.Time, Valore.grams, Valore.gramsPerMinute);
}
