gnuplot hybridSOM-c4-5_iris_gnuplot_generalization.plot
latex hybridSOM-c4-5_iris_generalization.tex
dvips -E hybridSOM-c4-5_iris_generalization.dvi
gnuplot hybridSOM-c4-5_iris_gnuplot_conditions.plot
latex hybridSOM-c4-5_iris_conditions.tex
dvips -E hybridSOM-c4-5_iris_conditions.dvi
mv hybridSOM-c4-5_iris_generalization.ps hybridSOM-c4-5_iris_generalization.eps
mv hybridSOM-c4-5_iris_conditions.ps hybridSOM-c4-5_iris_conditions.eps
latex sample.tex
dvips -f < sample.dvi > sample.ps
