#include "MonteCarlo.hpp"

using namespace std;

// Plain Monte Carlo Simulation to compute European option price and Greeks.
vector<double> EuropeanMCPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t){
    double tau = o.Get_T() - t;
    int M = tau / TimeDiff;
    double td = 0;
    double Z = 0;

    double V = 0;
    double delta = 0;
    double vega = 0;
    vector<double> result;

    for (long int i = 0; i < N; i++){
        double Si = S;
        td = TimeDiff;
        for (long int j = 0; j < M; j++){
            double td;
            Z = normal_generator();
            if (j == M - 1){
                td = tau - M * TimeDiff;
            }
            Si *= exp((r - q - sig * sig / 2) * td + sig * sqrt(td) * Z);
        }
        V += exp(- r * tau) * o.Payoff(Si);
        delta += exp(- r * tau) * Si / S * o.Exercise(Si);
        vega += exp(- r * tau) * (log(Si / S) - (r + sig * sig / 2) * tau) / sig * Si * o.Exercise(Si);
    }

	result.push_back(V / N);
	result.push_back(delta / N);
	result.push_back(vega / N);

	return result;
}

// MC with Control Variate Technique. 
double EuropeanMCCVPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t){
    // Use known unbiased estimator of S to reduce variance.
    double tau = o.Get_T() - t;
    int M = tau / TimeDiff;
    double td = 0;
    double Z = 0;

    double VSum = 0;
    double SSum = 0;
    double VSSum = 0;
    double S2Sum = 0;

    for (long int i = 0; i < N; i++){
        double Si = S;
        double Vi = 0;
        td = TimeDiff;
        for (long int j = 0; j < M; j++){
            Z = normal_generator();
            if (j == M - 1){
                td = tau - M * TimeDiff;
            }
            Si *= exp((r - q - sig * sig / 2) * td + sig * sqrt(td) * Z);
        }
        Vi = exp(- r * tau) * o.Payoff(Si);
        SSum += Si;
        VSum += Vi;
        VSSum += Vi * Si;
        S2Sum += Si * Si;
    }

    double Vbar = VSum / N;
    double Sbar = SSum / N;
    double c = -(VSSum - N * Vbar * Sbar) / (S2Sum - N * Sbar * Sbar); // c = -cov(V,S) / var(S).

    return Vbar + c * (Sbar - exp(r * tau) * S / N);
}

// MC with Antithetic Variates.
double EuropeanMCAVPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t){
    // Use Z and 1 - Z in each time step to generate corresponding paths.
    double tau = o.Get_T() - t;
    int M = tau / TimeDiff;
    double td = 0;
    double Z = 0;

    double VSum = 0;
   
    for (long int i = 0; i < N; i++){
        double S1 = S;
        double S2 = S;
        td = TimeDiff;
        for (long int j = 0; j < M; j++){
            Z = normal_generator();
            if (j == M - 1){
                td = tau - M * TimeDiff;
            }
            S1 *= exp((r - q - sig * sig / 2) * td + sig * sqrt(td) * Z);
            S2 *= exp((r - q - sig * sig / 2) * td + sig * sqrt(td) * (1-Z));
        }
        VSum += exp(- r * tau) * o.Payoff(S1) + exp(- r * tau) * o.Payoff(S2);
    }

    return VSum / (2 * N);
}

// MC with Moment Matching.
double EuropeanMCMMPricer(EuropeanOption o, long int N, double TimeDiff, double S, double t){
    // Collect a bunch of asset prices, reweight them and compute average payoff.
    double tau = o.Get_T() - t;
    int M = tau / TimeDiff;
    double td = 0;
    double Z = 0;

    vector<double> SVec;
    double SSum = 0;
   
    for (long int i = 0; i < N; i++){
        double Si = S;
        td = TimeDiff;
        for (long int j = 0; j < M; j++){
            Z = normal_generator();
            if (j == M - 1){
                td = tau - M * TimeDiff;
            }
            Si *= exp((r - q - sig * sig / 2) * td + sig * sqrt(td) * Z);
        }
        SVec.push_back(Si);
        SSum += Si;
    }
    double Sbar = SSum / N;
    double VSum = 0;
    for (long int i = 0; i < N; i++){
        SVec[i] *= exp(- r * tau) / Sbar;
        VSum += o.Payoff(SVec[i]);
    }

    return VSum / N;
}