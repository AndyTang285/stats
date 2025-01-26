#include <vector>
#include <cassert>
#include "stats.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

//NOTE: no "using namespace std;" in a .hpp file!  That's why we use "std::vector
//instead of "vector" later on.  You can add "using namespace std;" to your
//stats.cpp if you want to.

//EFFECTS: returns the count (sample size) of the numbers in v
int count(vector<double> v) {
    return v.size();
}

//REQUIRES: v is not empty
//EFFECTS: returns the sum of the numbers in v
double sum(vector<double> v) {
    
    double sum = 0;
    for (int i = 0; i < count(v); i++) {
        sum += v[i];
    }

    return sum;

}

//REQUIRES: v is not empty
//EFFECTS: returns the arithmetic mean of the numbers in v
//  http://en.wikipedia.org/wiki/Arithmetic_mean
double mean(vector<double> v) {
    return sum(v)/count(v);
}

//REQUIRES: v is not empty
//EFFECTS: returns the median of the numbers in v
//  https://en.wikipedia.org/wiki/Median#Finite_data_set_of_numbers
double median(vector<double> v) {

    int median = 0;
    int vSize = count(v);

    //sort the list 
    sort(v.begin(), v.end());
    
    //if size of the list is even
    if(vSize % 2 == 0) {
        
        int numOneIndex = vSize/2 - 1; 
        int numTwoIndex = vSize/2; 

        median = (v[numOneIndex] + v[numTwoIndex]) / 2;
        
    //if size of the list is odd 
    } else if (vSize % 2 == 1) {

        int numIndex = vSize/2;
        
        median = v[numIndex];
        
    }

    return median;
}

//REQUIRES: v is not empty
//EFFECTS: returns the min number in v
double min(vector<double> v) {
    double minValue = v[0];
    
    for (int i = 1; i < count(v); i++) {
        if (minValue > v[i]) {
            minValue = v[i];
        }
    }

    return minValue;
}

//REQUIRES: v is not empty
//EFFECTS: returns the max number in v
double max(vector<double> v) {
    
    double maxValue = v[0];

    for (int i = 1; i < count(v); i++) {
        if (maxValue < v[i]) {
            maxValue = v[i];
        }
    }

    return maxValue;
}

//REQUIRES: v contains at least 2 elements
//EFFECTS: returns the corrected sample standard deviation of the numbers in v
//  http://en.wikipedia.org/wiki/Standard_deviation#Corrected_sample_standard_deviation
double stdev(vector<double> v) {
    //Need: x bar - sample mean, xi - each data in v, n is the sample size
    //Want: Standard Deviation

    double standardDeviation = 0.0;
    int numerator = 0;

    for (int i = 0; i < count(v); i++) {
        numerator += pow((v[i] - mean(v)), 2);
        
    }

    int denominator = count(v) - 1;

    standardDeviation = (numerator / denominator);

    return standardDeviation;
    
}

//REQUIRES: v is not empty
//          p is between 0 and 1, inclusive
//EFFECTS: returns the percentile p of the numbers in v like Microsoft Excel.
//  Refer to the project spec for the formula to use.
//  NOTE: the definition in the spec uses indexing from 1.  You will need to
//  adapt it to use indexing from 0.
double percentile(vector<double> v, double p) {

    sort(v.begin(), v.end());

    double rank = p * (count(v) - 1) + 1;

    int k = rank;
    double d = rank - k;

    double percentile = v[k - 1] + d * (v[k] - v[k - 1]);

    return percentile;

}

//REQUIRES: v and criteria have the same number of elements
//EFFECTS: returns a new, filtered version of v containing the elements (and
//         only those elements) at v[x] where criteria[x] is equal to target,
//         in the same order as they originally appear in v.
//         Note: For this function, compare values to the criteria using ==.
vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target) {


    vector<double> filteredV;

    for (int i = 0; i < count(v); i++) {
        if (target == criteria[i]) {

            filteredV.push_back(v[i]);

        }
    }
                        
    return filteredV;
                        
}