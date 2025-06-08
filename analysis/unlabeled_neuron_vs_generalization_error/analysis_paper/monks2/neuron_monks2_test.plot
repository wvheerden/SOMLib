set fontpath "/usr/share/texmf/fonts/type1/public/cm-super/"
set output "neuron_monks2_test.eps"
set terminal postscript eps enhanced mono fontfile "sfss1000.pfb"
set xlabel "Percentage of neurons unlabeled"
set ylabel "Test error (overall)"
#set lmargin 0
#set rmargin 0
#set tmargin 0
#set bmargin 0
#set size 0.5, 0.5
plot "neuron_monks2.edited.txt" using 7:1 with points title ""
