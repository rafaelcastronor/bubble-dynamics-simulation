set terminal pngcairo size 1000,700 enhanced
set output 'convergence_annotated.png'

set xlabel 'Step Size h' font ",16"
set ylabel 'Absolute Error' font ",16"
set title 'Self-Convergence Test (tau_v = tau_g = 1, alpha = 1, t = 1.0)' font ",16"

set logscale xy
set grid
set key top left font ",13"

set format y "10^{%L}"

set xrange [0.0005:0.015]
set yrange [1e-12:1e-8]

set label "Observed Orders:" at 0.003,5e-9 font ",12"
set label "N=100->200: 4.10" at 0.003,2e-9 font ",11"
set label "N=200->400: 4.05" at 0.003,8e-10 font ",11"  
set label "N=400->800: 4.11" at 0.003,3.5e-10 font ",11"
set label "Expected: 4.00" at 0.003,1.5e-10 font ",11" tc rgb "red"

# Adjusted coefficient and thicker line
plot 'convergence_errors.dat' using 1:2 with linespoints lw 3 pt 7 ps 1.8 lc rgb "blue" title 'Measured Error', \
     1.5e-5*x**4 with lines lw 3 lc rgb "red" title 'O(h^4) Reference'