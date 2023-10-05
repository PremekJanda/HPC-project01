set title "NxN blocked matrix-matrix-multiplication performance comparison"
set xlabel "Block size (N)"
set ylabel "Performance percentage average"
set grid

set terminal postscript color "Helvetica" 14
set output "performance_comparison.ps"

# plot "1/out.data" using 3:9 title "First method" with linespoints, \
#      "2/out.data" using 3:9 title "First method" with linespoints, \
#      "3/out.data" using 3:9 title "First method" with linespoints, \
#      "4/out.data" using 3:9 title "First method" with linespoints

plot "2/out.data" using 3:9 title "First method" with linespoints, \
     "3/out.data" using 3:9 title "First method" with linespoints, \
     "4/out.data" using 3:9 title "First method" with linespoints, \
     "5/out.data" using 3:9 title "Second method" with linespoints, \
     "6/out.data" using 3:9 title "Second method" with linespoints, \
     "7/out.data" using 3:9 title "Second method" with linespoints, \
     "8/out.data" using 3:9 title "Third method" with linespoints
