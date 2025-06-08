gnuplot label-classification_iris_k-means_gnuplot.plot
latex label-classification_iris_k-means.tex
dvips -E label-classification_iris_k-means.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps