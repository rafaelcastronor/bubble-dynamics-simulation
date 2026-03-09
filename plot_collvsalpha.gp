set terminal pngcairo size 1000,700 enhanced
set output 'collapse_time_vs_alpha.png'

set xlabel 'Driving Frequency {/Symbol a}' font ",16"
set ylabel 'Collapse Time t' font ",16"
set title 'Effect of Driving Frequency on Collapse Time' font ",18"

set logscale x
set grid

plot 'varying_alpha.dat' using 1:2 with linespoints lw 2 pt 7 ps 1.5 lc rgb "purple" title 'Collapse time'