gnuplot label-classification_monks2_ward_gnuplot.plot
latex label-classification_monks2_ward.tex
dvips -E label-classification_monks2_ward.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps