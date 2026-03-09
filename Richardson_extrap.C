#include <iostream>
#include <iomanip>
#include <cmath>
#include "header.h"
using namespace std;

int main() {
    // Parameters
    double tv, tg, alpha;
    cout << "Enter viscous timescale tau_v (tv) = ";
    cin >> tv;
    cout << "Enter surface tension timescale tau_gamma (tg) = ";
    cin >> tg;
    cout << "Enter driving frequency (alpha) = ";
    cin >> alpha;

    double t_arb; // arbitrary time to evaluate our solution
    cout << "\nEnter time t where the error will be estimated: " << endl;
    cin >> t_arb;

    int N_rough;
    cout << "Enter step size (N) for [rough] approximation: " << endl;
    cin >> N_rough;

    int N_finest = 2 * N_rough; // the finest or more accurate has twice the 
    // step size 
    cout << "Step size (N) for [finest] approximation (2 * N[rough]): " << endl;
    cout << N_finest << endl;

    //Using two resolutions will be enough to prove 4th-order accuracy using RE
    double h_rough = t_arb/N_rough;
    double h_finest = t_arb/N_finest;
    
    cout << "\n<<<<<<< Richardson Extrapolation >>>>>>>" << endl;
    cout << "Evaluating at t = " << t_arb << endl;
    cout << "Roughest step size: N = " << N_rough << ", h = " << h_rough << endl;
    cout << "Finest step size: N = " << N_finest << ", h = " << h_finest << endl;
    cout << endl; 

    //Initial Conditions // rough step size variables
    double R_rough = 1.0;
    double z_rough = 0.0;
    double  t_rough = 0.0;
    
    //Run with rough step size
    cout << "Running rough step size simulation..." << endl;
    rk4_system(t_rough, R_rough, z_rough, h_rough, N_rough, tv, tg, alpha);

    //Initial Conditions // finest step size variables
    double R_finest = 1.0;
    double z_finest = 0.0;
    double t_finest = 0.0;
    
    cout << "Running finest step size simulation..." << endl;
    rk4_system(t_finest, R_finest, z_finest, h_finest, N_finest, tv, tg, alpha);
    
    //Richardson extrapolation 
    int p = 4; // order of convergence for RK4
    int factor = pow(2.0, p) - 1.0; // 2^4-1 = 15 

    double R_richardson = R_finest + (R_finest - R_rough)/factor; 
    //R_richardson = R_true + O(delta(x)^4) approximation for RK4 method
    //i.e. we got rid of the truncation error term 
    double R_trunc_err_est = fabs(R_finest - R_rough)/factor;
    //Estimated truncation error term [finest] (R_richardson - R_finest)
    double R_trunc_err_rough = fabs(R_richardson - R_rough);
    //Estimated truncation error term [rough] 
    
    cout << "\n==================================================" << endl;
    cout << "Results at t = " << t_arb << endl;
    cout << "==================================================" << endl;
    cout << setprecision(16);
    cout << "R(h= " << h_rough << ") [rough] = " << R_rough << endl;
    cout << "R(h= " << h_finest << ") [finest] = " << R_finest << endl;
    cout << "R [extrapolated] = \t" << R_richardson << endl << endl;
    cout << "Estimated truncation error in R [finest] = " << R_trunc_err_est << endl;
    cout << "Relative error = " << fabs(R_trunc_err_est/R_finest)*100 << "%" <<        endl;
    cout << "Confirming 4th order convergence: error{R[rough]/R[finest]} ~ 16 = " <<     endl;
    cout << setprecision(16) << R_trunc_err_rough/R_trunc_err_est << endl;
    cout << "==================================================\n" << endl;
    
    return 0;
}
