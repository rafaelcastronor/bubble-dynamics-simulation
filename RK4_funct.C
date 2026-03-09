#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include "header.h"
using namespace std;

//dimensionless function for the second derivative of R w.r.t t, f(t,R,z)
// where tv = tau_v - viscous timescale, and tg = tau_gamma - surface tension   timescale
double dzdt(double t, double R, double z, double tv, double tg, double alpha){

  double delta_P = 1.0 - 0.5*sin(2.0*M_PI*t/(alpha*tv));
  double ratio = tv/tg;

  return -(1.5)*z*z/R - (4.0)*z/(R*R) - (2.0)*(ratio*ratio)/(R*R) - delta_P/R;
}

//dimensionless function for the derivative of R w.r.t t, f(t,R,z)
double dRdt(double z){
  return z;
}

//RK4 method for a system of two equations
void rk4_system(double &t, double &R, double &z, double h, int N, double tv, double tg, double alpha){

  //we define variables that will evaluate our functions at I.C. (k1_i), half-timesteps (k(2,3)_i), and the final whole-timestep (k4_i) 
  double k1_R, k2_R, k3_R, k4_R; 
  double k1_z, k2_z, k3_z, k4_z;

  // we define variables that will hold the values of each variable + at a given timestep (t0 + h/2), (R0 + k1_R/2), (z0 + k1_z/2), or (q0 + (k4_q or h))
  double R_tstep, z_tstep, t_tstep;

  //Numerical method algorithm
  for(int n=0; n<N; n++){
    k1_R = h * dRdt(z);
    k1_z = h * dzdt(t, R, z, tv, tg, alpha);

    t_tstep = t + h/2.0;
    R_tstep = R + k1_R/2.0;
    z_tstep = z + k1_z/2.0;
    k2_R = h * dRdt(z_tstep);
    k2_z = h * dzdt(t_tstep, R_tstep, z_tstep, tv, tg, alpha);

    R_tstep = R + k2_R/2.0;
    z_tstep = z + k2_z/2.0;
    k3_R = h * dRdt(z_tstep);
    k3_z = h * dzdt(t_tstep, R_tstep, z_tstep, tv, tg, alpha);

    t_tstep = t + h;
    R_tstep = R + k3_R;
    z_tstep = z + k3_z;
    k4_R = h * dRdt(z_tstep);
    k4_z = h * dzdt(t_tstep, R_tstep, z_tstep, tv, tg, alpha);

    R += (k1_R + (2.0)*k2_R + (2.0)*k3_R + k4_R)/(6.0);
    z += (k1_z + (2.0)*k2_z + (2.0)*k3_z + k4_z)/(6.0);
    t += h;
  }
}
