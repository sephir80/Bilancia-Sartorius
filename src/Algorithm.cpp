#include "Algorithm.h"

Algorithm::Algorithm(int nElem,int thresholdVal)
{
    dataPoints.reserve(nElem);
    nelements = nElem;
    threshold = thresholdVal;
    gramsPerMinute = 0;
}

int Algorithm::addDataPoint(scaleValue newData) {
    int num;
    // Add new data point
    if (dataPoints.empty()) {
        dataPoints.push_back({newData.grams, newData.Time});
    }
    else if (calculateRateOk(newData)) {
        dataPoints.push_back({newData.grams, newData.Time});
    }
    num =dataPoints.size();
    if (dataPoints.size() == nelements) {
        if (gramsPerMinute == 0) {
            gramsPerMinute = calculateRate();
        }
        else {
            gramsPerMinute = calculateRateAdjustedAvg(gramsPerMinute);
        }
        dataPoints.clear(); // Remove all data points
    }

    return gramsPerMinute;

}

int Algorithm::calculateRate() {

    const auto& oldest = dataPoints.front(); 
    const auto& newest = dataPoints.back();

    int weightDiff = oldest.totalWeight - newest.totalWeight;
    unsigned long timeDiff = newest.timestampedWeight - oldest.timestampedWeight;

    if (timeDiff == 0) return 0; // Prevent division by zero

    // Calculate grams per minute
    return static_cast<int>((weightDiff * 60000) / timeDiff);
}




bool Algorithm::calculateRateOk(const scaleValue& newest) {
    int gramsProjected;
    if (dataPoints.size() < 2) return true;

    const auto& oldest = dataPoints.back();

    int weightDiff = oldest.totalWeight - newest.grams;
    unsigned long timeDiff = newest.Time - oldest.timestampedWeight;

    if (timeDiff == 0) return false; // Prevent division by zero

    // Calculate grams per minute
    gramsProjected = static_cast<int>((weightDiff * 60000) / timeDiff);
    if (gramsProjected > 150) 
        return false;
    else
       return true;
}

int Algorithm::calculateRateAdjustedAvg(int previousgramsPerMinute) {
    int currentRate = calculateRate();
    // Adjust the rate using a simple moving average
    return (previousgramsPerMinute + currentRate) / 2;
}