gnuplot c4-5_iris_gnuplot_generalization.plot
latex c4-5_iris_generalization.tex
dvips -E c4-5_iris_generalization.dvi
gnuplot c4-5_iris_gnuplot_conditions.plot
latex c4-5_iris_conditions.tex
dvips -E c4-5_iris_conditions.dvi
mv c4-5_iris_generalization.ps c4-5_iris_generalization.eps
mv c4-5_iris_conditions.ps c4-5_iris_conditions.eps
latex sample.tex
dvips -f < sample.dvi > sample.eps
