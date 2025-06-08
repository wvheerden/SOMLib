gnuplot sig_iris_gnuplot_generalization.plot
latex sig_iris_generalization.tex
dvips -E sig_iris_generalization.dvi
gnuplot sig_iris_gnuplot_conditions.plot
latex sig_iris_conditions.tex
dvips -E sig_iris_conditions.dvi
mv sig_iris_generalization.ps sig_iris_generalization.eps
mv sig_iris_conditions.ps sig_iris_conditions.eps
latex sample.tex
dvips -f < sample.dvi > sample.ps
