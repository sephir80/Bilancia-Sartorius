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

   if (dataPoints.size() > nelements)
   {
        if (dataPoints.size() > nelements / 2 &&
            dataPoints[nelements/2].totalWeight - dataPoints.back().totalWeight <= 1)
        {
            dataPoints.clear(); // Remove all data points
            gramsPerMinute=0;
        }
        else
        {
         // Calculate grams per minute using Ordinary Least Squares
         gramsPerMinute = static_cast<int>(-ordinaryLeastSquares(num, dataPoints) * 60000);
         dataPoints.erase(dataPoints.begin()); // Remove the oldest data point
        }
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
    if (currentRate <= 5) return 0; // If the current rate is very low, return 0
    // Adjust the rate using a simple moving average
    return (previousgramsPerMinute + currentRate) / 2;
}

double Algorithm::ordinaryLeastSquares(int n, const std::vector<AnalisisData>& points) {
    if (n < 2) return 0.0; // Not enough points to calculate a trend

    double sumX = 0.0;
    double sumY = 0.0;
    double sumXY = 0.0;
    double sumX2 = 0.0;

    for (const auto& point : points) {
        double x = static_cast<double>(point.timestampedWeight);
        double y = static_cast<double>(point.totalWeight);
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
    }

    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    return slope; // This represents the rate of change of weight over time
}