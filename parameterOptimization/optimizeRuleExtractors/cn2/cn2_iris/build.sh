gnuplot cn2_iris_gnuplot_generalization.plot
latex cn2_iris_generalization.tex
dvips -E cn2_iris_generalization.dvi
gnuplot cn2_iris_gnuplot_conditions.plot
latex cn2_iris_conditions.tex
dvips -E cn2_iris_conditions.dvi
mv cn2_iris_generalization.ps cn2_iris_generalization.eps
mv cn2_iris_conditions.ps cn2_iris_conditions.eps
latex sample.tex
dvips -f < sample.dvi > sample.ps
