gnuplot label-classification_iris_ward_gnuplot.plot
latex label-classification_iris_ward.tex
dvips -E label-classification_iris_ward.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps