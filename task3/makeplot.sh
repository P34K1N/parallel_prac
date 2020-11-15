set terminal svg size 600,500
set output 'max_plot.svg'
set title 'Maximum time measurements'
set dgrid3d 4,5
set zrange [0:1]
set pm3d
splot 'maxtime_grid_normed.dat' u 2:1:3 with lines

set output 'sum_plot.svg'
set title 'Summary time measurements'
set xrange [] reverse
splot 'sumtime_grid_normed.dat' u 2:1:3 with lines


