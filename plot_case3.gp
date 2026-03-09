set terminal pngcairo size 1000,700 enhanced
set output 'case3_slow_collapse.png'

set xlabel 'Dimensionless Time t' font ",16"
set ylabel 'Dimensionless Bubble Radius R' font ",16"
set title 'Case 3: Low Viscosity (tau_v = 0.1*tau_g, alpha = 1)' font ",18"

set grid
set key top right font ",14"

set label "Slow collapse - at t = 12.94" at 2,0.3 font ",12"

plot 'bubble_radii_evolution.dat' using 1:2 with lines lw 3 lc rgb "orange" title 'R(t)'