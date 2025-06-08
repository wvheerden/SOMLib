set fontpath "/usr/share/texmf/fonts/type1/public/cm-super/"
set output "neuron_ionosphere_testMisclassified.eps"
set terminal postscript eps enhanced mono fontfile "sfss1000.pfb"
set xlabel "Percentage of neurons unlabeled"
set ylabel "Percentage of test set examples misclassified"
set xtics 10
set ytics 10
plot [-2:85] [-2.6:80] "neuron_ionosphere.edited.txt" using 7:3 with points title ""
