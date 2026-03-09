set terminal png size 1000,700
set output 'case1_collapse.png'

set xlabel 'Dimensionless Time t'
set ylabel 'Dimensionless Bubble Radius R'
set title 'Case 1: Balanced Timescales (tau_v = tau_g = alpha = 1)'

set grid
set key top right

# Add horizontal line at R=0 to show collapse threshold
set arrow from 0,0 to 1.8,0 nohead lt 0 lw 1.5 lc rgb "black"

# Add vertical line at collapse time
set arrow from 1.66,0 to 1.66,1.0 nohead lt 2 lw 1.5

set label "Collapse at t ~ 1.66" at 1.1,0.5

plot 'bubble_radii_evolution.dat' using 1:2 with lines lw 3 lc rgb "red" title 'R(t)'