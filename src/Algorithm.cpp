#include "Algorithm.h"

Algorithm::Algorithm(int nElem) : nelements(nElem), gramsPerMinute(0) {}

bool Algorithm::addDataPoint(scaleValue newData) {
    // Add new data point
    dataPoints.push_back({newData.grams, newData.Time});

    if (dataPoints.size() > nelements) {
        gramsPerMinute = calculateRate();
        dataPoints.erase(dataPoints.begin());
        return true;
    }

    return false;

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