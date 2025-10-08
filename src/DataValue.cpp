#include "DataValue.h"




DataValue::DataValue()
{
  int numero=sizeof(scaleValue);
  IDScale="";
}

void DataValue::putData(String* buffer)
{
  scaleValue Valore;

  Valore.Date=buffer[0].substring(0,10).c_str();
  Valore.Time=buffer[0].substring(15).c_str();
  if (IDScale=="")
    IDScale=buffer[2].substring(12).c_str();
  Valore.grams=atoi(buffer[3].substring(12,16).c_str());
  Valore.gramsPerMinute=0;
  Valori.push_back(Valore);
}

void DataValue::putDataFake(int gr)
{
  scaleValue Valore;
  unsigned long now=millis();
  Valore.Date=String(now).c_str();
  Valore.Time=String(now).c_str();
  if (IDScale=="")
    IDScale="FAKE";
  Valore.grams=gr;
  Valore.gramsPerMinute=0;
  Valori.push_back(Valore);
  if (Valori.size()>100)
    Valori.erase(Valori.begin());
}

int DataValue::grams()
{
  if (Valori.size()>0)
    return Valori.back().grams;
  else
    return 0;
}


void DataValue::setGramsPerMinute(int grmin)
{
  if (Valori.size()>0)
    Valori.back().gramsPerMinute=grmin;
}

std::vector<scaleValue> DataValue::GetData()
{
  return Valori;
}

