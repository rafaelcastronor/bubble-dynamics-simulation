#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include "header.h"
#include <fstream>
using namespace std;



int main ()
{

  double tv, tg, alpha; // where tv = tau_v - viscous timescale, and tg = tau_gamma - surface tension   timescale

  cout << "Enter viscous timescale tau_v (tv) = " << endl;
  cin >> tv;
  cout << "Enter surface tension timescale tau_gamma (tg) = " << endl;
  cin >> tg;
  cout << endl;

  //Integration parameters
  double t_final;
  int N;

  cout << "<<< Enter integration parameters >>>" << endl << endl;
  cout << "Enter final time (t_final) = " << endl;
  cin >> t_final;
  cout << "Enter number of steps (N) = " << endl;
  cin >> N;
  cout << endl;

  double h = t_final/N; //step size

  int n_alpha = 10;
  double alpha_values[n_alpha];

  //We create a loop that will calculate and store the values of alpha in logspace 
  for(int i=0; i<n_alpha; i++){
    double log_alpha = -1.0 + (2.0*i)/(n_alpha - 1.0);// = log_10(10^log_alpha)
    alpha_values[i] = pow(10.0,log_alpha);
  }

  ofstream rofa_file("varying_alpha.dat");
  rofa_file << "# alpha  collapse_time  final_R  collapsed(1=yes,0=no)" << endl;
  rofa_file << setprecision(16);

  for (int j=0; j<n_alpha; j++){
    double alpha = alpha_values[j];

    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Running simulation " << (j+1) << "/" << n_alpha << endl;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;


  //Define Initial Conditions:

  double R = 1.0; // R_dimensionless(0) = 1
  double z = 0.0; // dR_dimless/dt_dimless(0) = 0
  double t = 0.0; // t_dimless at t0 = 0, t0 = 0
  

  char filename[100];
  sprintf(filename, "alpha_%.4f.dat", alpha);
  ofstream data_file(filename);
  data_file << "# t  R  z  (alpha = " << alpha << ")" << endl;
  data_file << setprecision(16);

  data_file << t << " " << R << " " << z << endl;

  //Normalizing intervals = declaring integer output integration intervals 
  //i.e. Reducing the amount of data points written in the file 
  int output_interval = N/1000;
  if (output_interval < 1){
    output_interval = 1;
  }
  
  bool collapsed = false;
  double collapse_time = t_final;


  for(int i=0; i<N; i++){

    rk4_system(t, R, z, h, 1, tv, tg, alpha);

    //Physical check to see if radius collapsed
    if (R < 0.015 || R <= 0.0 || std::isnan(R) || std::isnan(z) || !std::isfinite(R)) {
      collapsed = true;
      collapse_time = t;
      cout << "Bubble collapsed at t = " << t << ", R = " << R << endl;
      data_file << t << " " << R << " " << z << endl;
      break;
    }
    
    if (i % output_interval == 0 || i == N-1){
      data_file << t << " " << R << " " << z << endl;
    }
  }

  data_file.close();
  
  if (!collapsed){
    cout << "  Simulation completed: R = " << R << " at t = " << t_final << endl;
  }

  rofa_file << alpha << " " << collapse_time << " " << R << " " << (collapsed ? 1:0) << endl;

  }

  rofa_file.close();
  

  cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
  cout << "All simulations complete!" << endl; 
  cout << "R(alpha) written to varying_alpha.dat" << endl;
  cout << "Individual files: alpha_$$$$.dat" << endl;
  cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;


  return 0;
}
