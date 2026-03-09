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
  cout << "Enter driving frequency (alpha) = " << endl;
  cin >> alpha;


  //Define Initial Conditions:

  double R = 1.0; // R_dimensionless(0) = 1
  double z = 0.0; // dR_dimless/dt_dimless(0) = 0
  double t = 0.0; // t_dimless at t0 = 0, t0 = 0
  

  //Integration parameters
  double t_final;
  int N_array_size; // we define a variable that will allow the user to determine how many different step sizes they will like to use.
  cout << "How many different mesh point values would you like to test? " << endl;
  cin >> N_array_size;

  int N[N_array_size]; // we declare an array that will store the different step size values i.e. 100, 200, 400, etc.

  cout << "Enter " << N_array_size << " step size values (N)" << endl;
  for (int i=0; i<N_array_size; i++){
    cin >> N[i]; // we ask the user to read the step size values
  }

  cout << "Enter final time (t_final) = " << endl;
  cin >> t_final;


  double h[N_array_size];// array to store h for each step size
  double R_final[N_array_size]; // array to store R for each step size

  
  //Open the output file and output the initial conditions to file
  ofstream convergence_file("convergence.dat");
  convergence_file << "# N h R_final" << endl;
  convergence_file << setprecision(16);

  for(int j=0; j<N_array_size; j++){

  //Define Initial Conditions:

  double R = 1.0; // R_dimensionless(0) = 1
  double z = 0.0; // dR_dimless/dt_dimless(0) = 0
  double t = 0.0; // t_dimless at t0 = 0, t0 = 0

  h[j] = t_final/N[j]; //Calculat step size for each N
  
  cout << "\n<<< Running with N = " << N[j] << ", h = " << h[j] << " >>>" <<  endl;
  
  
  for(int i=0; i<N[j]; i++){

    rk4_system(t, R, z, h[j], 1, tv, tg, alpha);

    //Physical check to see if radius collapsed
    if (R < 0.001 || std::isnan(R) || std::isnan(z) || !std::isfinite(R)) {
      cout << "Bubble collapsed at t = " << t << ", R = " << R << endl;
      break;
    }
  }

  R_final[j] = R; 

  cout << "Final time = " << t << endl;
  cout << "Final R = " << R << endl;

  convergence_file << N[j] << " " << h[j] << " " << R_final[j] << endl;

  }

  convergence_file.close();

  cout << "\n<<< Convergence Analysis >>>" << endl;
  cout << "\n N \t\t h \t\t R_final \t\t error " << endl;
  
  double R_reference = R_final[N_array_size - 1]; //Store the most likely accurate value of R to be used as the reference point for comparison

  ofstream errors_file("convergence_errors.dat");
  errors_file << "h absolute_error" << endl;
  errors_file << setprecision(16);

  for(int j=0; j<N_array_size; j++){
    
    double error = fabs(R_final[j] - R_reference);
    cout << setprecision(16) << N[j] << "\t\t" << h[j] << "\t\t" << R_final[j] << "\t\t" << error<< endl;
    errors_file << h[j] << " " <<  error << endl;
  }

  errors_file.close();

  if(N_array_size >= 3){
    
    cout << "\n<<< Order of Convergence >>> " << endl;

    for(int j=0; j<N_array_size; j++){
      double error1 = fabs(R_final[j] - R_reference);
      double error2 = fabs(R_final[j+1] - R_reference);

      if(error1 > 0 && error2 > 0){
	double order = log(error1/error2)/log(h[j]/h[j+1]);
	cout << "\n Between N = " << N[j] << " and N = " << N[j+1] << endl;
	cout << "Order is of approximately: " << order << endl;
      }
    }
    cout << "Exprected order for RK4 : 4" << endl;
    cout << "R_reference = " << R_reference << endl;
  }

  cout << "Results written to convergence_file.dat and convergence_errors.dat" << endl;

  return 0;
}
