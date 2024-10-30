#include<cmath>

#ifndef Utilities
#define Utilities

// Market related
double r; // risk-free rate

// Asset related
double q; // dividend yield
double sig; // variance of asset

// Utility functions
double normal_generator();

double pnorm(double x); // CDF of standard normal distribution
double dnorm(double x); // PDF of standard normal distribution
#endif