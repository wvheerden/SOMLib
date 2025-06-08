gnuplot label-classification_pima_k-means_gnuplot.plot
latex label-classification_pima_k-means.tex
dvips -E label-classification_pima_k-means.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps