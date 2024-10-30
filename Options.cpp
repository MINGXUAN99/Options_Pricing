#include "MonteCarlo.hpp"

using namespace std;

// Parent class: Option

// Constructors.
Option::Option() {};
Option::Option(double new_K, double new_T, string new_type, string new_name): K(new_K), T(new_T), name(new_name){
    if (new_type == "C" || new_type == "Call"){
        new_type = "C";
    } 
    else if (new_type == "P" || new_type == "Put"){
        new_type = "P";
    }
    else{

    }
}
Option::Option(const Option& o): K(o.K), T(o.T), type(o.type), name(o.name){};
// Desctructor.
Option::~Option(){};

 // Getting and Setting function
double Option::Get_K(){
    return K;
}
void Option::Set_K(double new_K){
    K = new_K;
    cout<<"New Strike Price set as: "<<K<<endl;
}
double Option::Get_T(){
    return T;
}
void Option::Set_T(double new_T){
    T = new_T;
    cout<<"New Maturity Time set as: "<<T<<endl;
}
string Option::Get_type(){
    return type;
}
void Option::Set_type(string new_type){
    if (new_type == "C"|| new_type == "Call"){
        type = "C";
        cout<<"This is a Call Option."<<endl;
    } 
    else if (new_type == "P"|| new_type == "Put"){
        type = "P";
        cout<<"This is a Put Option."<<endl;
    }
    else{

    }
}
string Option::Get_name(){
    return name;
}
void Option::Set_name(string new_name){
    name = new_name;
    cout<<"This is Option of "<<name<<endl;
}

// Payoff function
double Option::Payoff(double S){
    if (type == "C"){
        return max(S - K, 0.0);
    }
    else{
        return max(K - S, 0.0);
    }
}
double Option::Exercise(double S){
    if (type == "C"){
        return int(S > K);
    }
    else{
        return int(S < K);
    }
}

// Child Class: European Option
// Constructors.
EuropeanOption::EuropeanOption(){};
EuropeanOption::EuropeanOption(double new_K, double new_T, string new_type, string new_name){
    Option(new_K, new_T, new_type, new_name);
}
EuropeanOption::EuropeanOption(const EuropeanOption& o){
    Option(o.K, o.T, o.type, o.name);
}
// Desctructor.
EuropeanOption::~EuropeanOption(){};

// Black-Scholes Model
double EuropeanOption::BSPrice(double S, double t){
    double tau = T - t;
    double d1 = (log(S / K) + (r - q + sig * sig * 0.5 * tau)) / (sig * sqrt(tau));
    double d2 = d1 - sqrt(tau);
    if (type == "C"){
        return pnorm(d1) * S * exp(-q * tau) - pnorm(d2) * K * exp(-r * tau);
    }
    else{
        return pnorm(-d2) * K * exp(-r * tau) - pnorm(-d1) * S * exp(-q * tau);
    }
}
double EuropeanOption::BSDelta(double S, double t){
    double tau = T - t;
    double d1 = (log(S / K) + (r - q + sig * sig * 0.5 * tau)) / (sig * sqrt(tau));
    if (type == "C"){
        return exp(-q * T) * pnorm(d1);
    }
    else{
        return -exp(-q * T) * pnorm(-d1);
    }
}
double EuropeanOption::BSGamma(double S, double t){
    double tau = T - t;
    double d1 = (log(S / K) + (r - q + sig * sig * 0.5 * tau)) / (sig * sqrt(tau));
    return (exp(-q * T) * dnorm(d1)) / (S * sig * sqrt(T));
}
double EuropeanOption::BSVega(double S, double t){
    double tau = T - t;
    double d1 = (log(S / K) + (r - q + sig * sig * 0.5 * tau)) / (sig * sqrt(tau));
    return S * exp(-q * tau) * sqrt(tau) * dnorm(d1);
}
double EuropeanOption::BSTheta(double S, double t){
    double tau = T - t;
    double d1 = (log(S / K) + (r - q + sig * sig * 0.5 * tau)) / (sig * sqrt(tau));
    double d2 = d1 - sqrt(tau);
    if (type == "C"){
        return -(S * sig * exp(-q * tau) * dnorm(d1)) / (2 * sqrt(tau)) + q * S * exp(-q * tau) * pnorm(d1) - r * K * exp(-r * tau) * pnorm(d2);
    }
    else{
        return -(S * sig * exp(-q * tau) * dnorm(d1)) / (2 * sqrt(tau)) - q * S * exp(-q * tau) * pnorm(-d1) + r * K * exp(-r * tau) * pnorm(-d2);
    }
}

// Child Class: American Option
// Constructors.
AmericanOption::AmericanOption(){};
AmericanOption::AmericanOption(double new_K, double new_T, string new_type, string new_name){
    Option(new_K, new_T, new_type, new_name);
}
AmericanOption::AmericanOption(const AmericanOption& o){
    Option(o.K, o.T, o.type, o.name);
}
// Desctructor.
AmericanOption::~AmericanOption(){};