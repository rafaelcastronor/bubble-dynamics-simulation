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
  cout << endl;


  //Define Initial Conditions:

  double R = 1.0; // R_dimensionless(0) = 1
  double z = 0.0; // dR_dimless/dt_dimless(0) = 0
  double t = 0.0; // t_dimless at t0 = 0, t0 = 0
  

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

  
  //Open the output file and output the initial conditions to file
  ofstream outfile("bubble_radii_evolution.dat");
  outfile << "# t R z" << endl;
  outfile << setprecision(16);
  outfile << t << " " << R << " " << z << endl;

  
  //Normalizing intervals = declaring integer output integration intervals 
  //i.e. Reducing the amount of data points written in the file 
  int output_interval = N/1000;
  if (output_interval < 1){
    output_interval = 1;
  }
  
  
  
  for(int i=0; i<N; i++){

    rk4_system(t, R, z, h, 1, tv, tg, alpha);

    //Physical check to see if radius collapsed
    if (R < 0.001 || std::isnan(R) || std::isnan(z) || !std::isfinite(R)) {
      cout << "Bubble collapsed at t = " << t << ", R = " << R << endl;
      outfile << t << " " << R << " " << z << endl;
      break;
    }
    
    if (i % output_interval == 0 || i == N-1){
      outfile << t << " " << R << " " << z << endl;
    }
  }

  outfile.close();
  cout << "Final time = " << t << endl;
  cout << setprecision(16) << "Final Radius = " << R << endl;
  cout << "Results written to bubble_radii_evolution.dat" << endl;

  return 0;
}
