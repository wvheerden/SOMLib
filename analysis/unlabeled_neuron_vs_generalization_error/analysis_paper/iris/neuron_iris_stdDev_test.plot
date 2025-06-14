set fontpath "/usr/share/texmf/fonts/type1/public/cm-super/"
set output "neuron_iris_stdDev_test.eps"
set terminal postscript eps enhanced mono fontfile "sfss1000.pfb"
set xlabel "Percentage of neurons unlabeled"
set ylabel "Test error standard deviation (overall)"
plot "neuron_iris.edited.txt" using 7:2 with points title ""
