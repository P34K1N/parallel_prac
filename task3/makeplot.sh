set terminal svg size 600,500
set output 'max_plot.svg'
set title 'Maximum time measurements'
set dgrid3d 8,5
set xrange [] reverse
set zrange [0:1]
set pm3d
splot 'maxtime_grid.dat' u 2:1:3 with lines

set output 'max_plot_1.svg'
set title 'Maximum time mesurements (from dif-t perspective)'
set xrange [] noreverse
splot 'maxtime_grid.dat' u 2:1:3 with lines

set output 'sum_plot.svg'
set title 'Summary time measurements'
set xrange [] reverse
splot 'sumtime_grid.dat' u 2:1:3 with lines


