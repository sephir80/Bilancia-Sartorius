#ifndef DATAVALUE_H
#define DATAVALUE_H

#include <Arduino.h>
#include <vector>

struct scaleValue {
  String Date;
  String Time;
  int grams;
  int gramsPerMinute;
};


class DataValue {
private:
  scaleValue Valori;
  std::string IDScale;
public:
  DataValue();
  void putData(String* buffer);
  void putDataFake(int gr);
  void setGramsPerMinute(int grmin);
  scaleValue GetData();
};

#endif