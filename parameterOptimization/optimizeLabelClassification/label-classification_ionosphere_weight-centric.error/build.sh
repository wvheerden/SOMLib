gnuplot label-classification_ionosphere_weight-centric_gnuplot.plot
latex label-classification_ionosphere_weight-centric.tex
dvips -E label-classification_ionosphere_weight-centric.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps