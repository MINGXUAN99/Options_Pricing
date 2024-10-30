#include <iostream>
#include <string>
#include <cmath> 

#include "Utilities.hpp"

using namespace std;

#ifndef Options
#define Options

// Parent Option Class
class Option{
    protected:
        double K; // strike price
        double T; // expiration date
        string type = "C"; // call or put
        string name; // underlysing asset name.

    public:
        // Instructors & Destructor
        Option();
        Option(double new_K, double new_T, string new_type, string new_name);
        Option(const Option& o);
        virtual ~Option();

        // Getting and Setting function
        double Get_K();
        void Set_K(double new_K);
        double Get_T();
        void Set_T(double new_T);
        string Get_type();
        void Set_type(string new_type);
        string Get_name();
        void Set_name(string new_name);

        // Payoff function
        double Payoff(double S);
        double Exercise(double S);
};

class EuropeanOption: public Option{
    public:
        // Instructors & Destructor
        EuropeanOption();
        EuropeanOption(double new_K, double new_T, string new_type, string new_name);
        EuropeanOption(const EuropeanOption& o);
        virtual ~EuropeanOption();

        // Black-Scholes Model
        double BSPrice(double S, double t);
        double BSDelta(double S, double t);
        double BSGamma(double S, double t);
        double BSVega(double S, double t);
        double BSTheta(double S, double t);
};

class AmericanOption: public Option{
    public:
        // Instructors & Destructor
        AmericanOption();
        AmericanOption(double new_K, double new_T, string new_type, string new_name);
        AmericanOption(const AmericanOption& o);
        virtual ~AmericanOption();
};



#endif