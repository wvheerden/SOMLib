gnuplot label-classification_monks3_k-means_gnuplot.plot
latex label-classification_monks3_k-means.tex
dvips -E label-classification_monks3_k-means.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps