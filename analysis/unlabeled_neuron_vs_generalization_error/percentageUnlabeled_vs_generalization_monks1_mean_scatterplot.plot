set fontpath "/usr/share/texmf/fonts/type1/public/cm-super"
set output "percentageUnlabeled_vs_generalization_monks1_mean_scatterplot.eps"
set terminal postscript eps enhanced mono fontfile "sfss1000.pfb"
set xlabel "Mean Unlabeled Neurons (Percentage of Map)"
set ylabel "Mean Generalization Error\n(Percentage Misclassifications)"
set xtics 10
set ytics 10
set xrange [-1.5:80]
set yrange [-3:80]
#set lmargin 0
#set rmargin 0
#set tmargin 0
#set bmargin 0
set size 1, 0.75
plot "label-classification_monks1_neuron.error.summary.separated" using 12:8 with points title ""