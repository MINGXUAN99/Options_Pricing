#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "Utilities.hpp"
#include "Options.hpp"

using namespace std;

#ifndef MonteCarlo;
#define MonteCarlo;

// Plain Monte Carlo Simulation to compute European option price and Greeks.
vector<double> EuropeanMCPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t);
// MC with Control Variate Technique. 
double EuropeanMCCVPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t);
// MC with Antithetic Variates.
double EuropeanMCAVPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t);
// MC with Moment Matching.
double EuropeanMCMMPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t);






#endif