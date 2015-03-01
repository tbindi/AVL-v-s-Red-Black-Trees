set terminal jpeg

set output "avlrb.jpg"

set title "AVL vs. RED-BLACK"
set xlabel "no. of elements inserted"
set ylabel "time in seconds"

set xrange [0:40000]
set yrange [0:80]
set xtics 5000
set ytics 10

plot  'avl.txt' using 1:2 with lines title 'AVL insertion' lw 3 ,'red-black.txt' using 1:2 with lines title 'RED-BLACK insertion'  lw 3
