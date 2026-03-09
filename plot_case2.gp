set terminal pngcairo size 1000,700 enhanced
set output 'case2_collapse.png'

set xlabel 'Dimensionless Time t' font ",16"
set ylabel 'Dimensionless Bubble Radius R' font ",16"
set title 'Case 2: High Viscosity (tau_v = 10*tau_g, alpha = 1)' font ",18"

set grid
set key top right font ",14"

# Add horizontal line at R=0
set arrow from 0,0 to 0.15,0 nohead lt 0 lw 1.5 lc rgb "black"

# Add vertical line at collapse time
set arrow from 0.066,0 to 0.066,1.0 nohead lt 2 lw 1.5 lc rgb "green"

set label "Collapse at t = 0.066" at 0.02,0.5 font ",14"

plot 'bubble_radii_evolution.dat' using 1:2 with lines lw 3 lc rgb "blue" title 'R(t)'