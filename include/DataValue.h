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
  std::vector<scaleValue> Valori;
  std::string IDScale;
public:
  DataValue();
  void putData(String* buffer);
  void putDataFake(int gr);
  int grams();
  void setGramsPerMinute(int grmin);
  std::vector<scaleValue> GetData();
};

#endif