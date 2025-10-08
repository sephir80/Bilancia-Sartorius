#include "DataValue.h"

struct AnalisisData {
  int totalWeight;
  unsigned long timestampedWeight;
};



class Algorithm {
public:
    Algorithm(int nElem);
    bool addDataPoint(int weight, unsigned long timestamp);
    int getGramsPerMinute() const { return gramsPerMinute; }    
private:
    int nelements;
    std::vector<AnalisisData> dataPoints;
    int calculateRate();
    int gramsPerMinute;
};