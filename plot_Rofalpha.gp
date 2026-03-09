set terminal pngcairo size 1200,700 enhanced
set output 'alpha_trajectories.png'

set xlabel 'Dimensionless Time t' font ",16"
set ylabel 'Dimensionless Bubble Radius R' font ",16"
set title 'Bubble Evolution for Different {/Symbol a} ({/Symbol t}_v = {/Symbol t}_g = 1)' font ",18"

set grid
set key top right font ",12"

plot 'alpha_0.1000.dat' using 1:2 with lines lw 2 title '{/Symbol a} = 0.1', \
     'alpha_0.7743.dat' using 1:2 with lines lw 2 title '{/Symbol a} = 0.77', \
     'alpha_1.2915.dat' using 1:2 with lines lw 2 title '{/Symbol a} = 1.29', \
     'alpha_3.5938.dat' using 1:2 with lines lw 2 title '{/Symbol a} = 3.59', \
     'alpha_5.9948.dat' using 1:2 with lines lw 2 title '{/Symbol a} = 5.99', \
     'alpha_10.0000.dat' using 1:2 with lines lw 2 title '{/Symbol a} = 10'