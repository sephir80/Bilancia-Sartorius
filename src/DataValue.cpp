#include "DataValue.h"

int DataValue::CalcGramsPerMinute(int g)    //todo testare la funzionalita di questo blocco
{
  int gmin=0;
  if (indexPesi==9) 
  {
    Pesi[indexPesi]=g;
    gmin=(Pesi[0]-Pesi[9])*6;
    indexPesi++;
  }
  else if (indexPesi==10)
  {
    DataValue::ArrayMove(g);
    gmin=(Pesi[0]-Pesi[9])*6;   
  }
  else 
  {
    Pesi[indexPesi]=g;
    indexPesi++;
  }
  if (gmin<0)
  {
    gmin=0;
  }
  return gmin;
}

void DataValue::ArrayMove(int g)
{
  for (int i=1;i<10;i++) 
  {
    Pesi[i-1]=Pesi[i];
  }
  Pesi[9]=g;
}

DataValue::DataValue()
{
  indexPesi=0;
}

void DataValue::putData(String* buffer)
{
  char *end;
  Valore.Date=buffer[0].substring(0,10).c_str();
  Valore.Time=buffer[0].substring(15).c_str();
  Valore.IDScale=buffer[2].substring(12).c_str();
  Valore.grams=atoi(buffer[3].substring(12,16).c_str());
  Valore.gramsPerMinute=CalcGramsPerMinute(Valore.grams);
}

scaleValue DataValue::GetData()
{
  return Valore;
}

String DataValue::gramsPerMinute()
{
  return "expression";
}
