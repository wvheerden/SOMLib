gnuplot label-classification_monks1_k-means_gnuplot.plot
latex label-classification_monks1_k-means.tex
dvips -E label-classification_monks1_k-means.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps