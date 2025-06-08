gnuplot label-classification_ionosphere_ward_gnuplot.plot
latex label-classification_ionosphere_ward.tex
dvips -E label-classification_ionosphere_ward.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps