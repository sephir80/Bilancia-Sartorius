#ifndef DATAVALUE_H
#define DATAVALUE_H

#include <Arduino.h>
#include <vector>

struct scaleValue {
  String Date;
  unsigned int Time;
  int grams;
  int gramsPerMinute;
};


class DataValue {
private:
  scaleValue Valore;
  std::string IDScale;
public:
  DataValue();
  void putData(String data,unsigned int millis, String* buffer);
  void putDataFake(String date,unsigned int time,int gr);
  void setGramsPerMinute(int grmin);
  scaleValue GetData();
  String GetDataToString();
};

#endif  