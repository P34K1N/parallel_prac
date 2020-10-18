set terminal svg size 600,500
set output 'wtime.svg'
set title 'Wall time'
plot 'wtime_ijk_32.dat' with linespoints title "ijk 32", \
     'wtime_ikj_32.dat' with linespoints title "ikj 32", \
     'wtime_ikj_opt.dat' with linespoints title "ikj optimal"

set output 'l1miss.svg'
set title 'L1 cache miss'
plot 'l1miss_ijk_32.dat' with linespoints title "ijk 32", \
     'l1miss_ikj_32.dat' with linespoints title "ikj 32", \
     'l1miss_ikj_opt.dat' with linespoints title "ikj optimal"

set output 'l2miss.svg'
set title 'L2 cache miss'
plot 'l2miss_ijk_32.dat' with linespoints title "ijk 32", \
     'l2miss_ikj_32.dat' with linespoints title "ikj 32", \
     'l2miss_ikj_opt.dat' with linespoints title "ikj optimal"

set output 'totcyc.svg'
set title 'Total cycles'
plot 'totcyc_ijk_32.dat' with linespoints title "ijk 32", \
     'totcyc_ikj_32.dat' with linespoints title "ikj 32", \
     'totcyc_ikj_opt.dat' with linespoints title "ikj optimal"

set output 'flop.svg'
set title 'Total floating-point operations'
plot 'flop_ijk_32.dat' with linespoints title "ijk 32", \
     'flop_ikj_32.dat' with linespoints title "ikj 32", \
     'flop_ikj_opt.dat' with linespoints title "ikj optimal"

