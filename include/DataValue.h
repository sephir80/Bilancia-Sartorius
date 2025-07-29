#ifndef DATAVALUE_H
#define DATAVALUE_H

#include <Arduino.h>

struct scaleValue {
  String Date;
  String Time;
  String IDScale;
  int grams;
  int gramsPerMinute;
};

// struct DataShow
// {
//   String date;
//   String time;
//   String gMin;
//   String weight;
// };

class DataValue {
private:
  scaleValue Valore;
  int Pesi[10];
  int indexPesi;
  int CalcGramsPerMinute(int g);
  void ArrayMove(int g);
public:
  DataValue();
  void putData(String* buffer);
  scaleValue GetData();
  String gramsPerMinute();
};

#endif