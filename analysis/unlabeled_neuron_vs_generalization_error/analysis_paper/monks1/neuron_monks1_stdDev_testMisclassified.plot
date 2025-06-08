set fontpath "/usr/share/texmf/fonts/type1/public/cm-super/"
set output "neuron_monks1_stdDev_testMisclassified.eps"
set terminal postscript eps enhanced mono fontfile "sfss1000.pfb"
set xlabel "Percentage of neurons unlabeled"
set ylabel "Test error standard deviation (misclassified examples)"
#set lmargin 0
#set rmargin 0
#set tmargin 0
#set bmargin 0
#set size 0.5, 0.5
plot "neuron_monks1.edited.txt" using 7:4 with points title ""
