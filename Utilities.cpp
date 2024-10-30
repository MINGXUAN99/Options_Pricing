#include "Utilities.hpp"

using namespace std;

const double PI = 3.1415926;

// CDF of standard normal distribution
double pnorm(double x){
    return 0.5 * (1 + erf(x / sqrt(2)));
}
// PDF of standard normal distribution
double dnorm(double x){
    return exp(-x * x / 2) / sqrt(2 * PI);
}