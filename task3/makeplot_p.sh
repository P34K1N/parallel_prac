set terminal svg size 600,500
set output 'max_plot_p.svg'
set title 'Maximum time measurements (pthread)'
set dgrid3d 4,5
set zrange [0:1]
set pm3d
splot 'maxtime_grid_normed_p.dat' u 2:1:3 with lines


set output 'sum_plot_p.svg'
set title 'Summary time measurements (pthread)'
set xrange [] reverse
set yrange [] reverse
splot 'sumtime_grid_normed_p.dat' u 2:1:3 with lines


