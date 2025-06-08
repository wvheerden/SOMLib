set fontpath "/usr/share/texmf/fonts/type1/public/cm-super"
set output "percentageUnlabeled_vs_generalization_pima_stdDev_scatterplot.eps"
set terminal postscript eps enhanced mono fontfile "sfss1000.pfb"
set xlabel "Mean Unlabeled Neurons (Percentage of Map)"
set ylabel "Standard Deviation of Generalization Error\n(Percentage Misclassifications)"
set xtics 10
set ytics 10
set xrange [-1.5:90]
set yrange [-0.625:20]
#set lmargin 0
#set rmargin 0
#set tmargin 0
#set bmargin 0
set size 1, 0.75
plot "label-classification_pima_neuron.error.summary.separated" using 12:9 with points title ""