set fontpath "/usr/share/texmf/fonts/type1/public/cm-super/"
set output "neuron_monks3_testUnclassified.eps"
set terminal postscript eps enhanced mono fontfile "sfss1000.pfb"
set xlabel "Percentage of neurons unlabeled"
set ylabel "Percentage of test set examples unclassified"
set xtics 10
set ytics 10
plot [-2:85] [-1.5:40] "neuron_monks3.edited.txt" using 7:5 with points title ""
