#include "DataValue.h"

struct AnalisisData {
  int totalWeight;
  unsigned long timestampedWeight;
};



class Algorithm {
public:
    Algorithm(int nElem);
    bool addDataPoint(scaleValue newData);
    int getGramsPerMinute() const { return gramsPerMinute; }    
private:
    int nelements;
    std::vector<AnalisisData> dataPoints;
    int calculateRate();
    int gramsPerMinute;
};