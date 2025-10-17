#include "DataValue.h"

struct AnalisisData {
  int totalWeight;
  unsigned long timestampedWeight;
};



class Algorithm {
public:
    Algorithm(int nElem,int threshold=2);
    int addDataPoint(scaleValue newData);
    //int getGramsPerMinute() const { return gramsPerMinute; }    
private:
    int nelements;
    int threshold;
    std::vector<AnalisisData> dataPoints;
    int calculateRate();
    double ordinaryLeastSquares();
    int calculateRateAdjustedAvg(int previousgramsPerMinute);
    bool calculateRateOk(const scaleValue& newest);
    int gramsPerMinute;
};