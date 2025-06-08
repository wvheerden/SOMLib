gnuplot label-classification_pima_ward_gnuplot.plot
latex label-classification_pima_ward.tex
dvips -E label-classification_pima_ward.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps