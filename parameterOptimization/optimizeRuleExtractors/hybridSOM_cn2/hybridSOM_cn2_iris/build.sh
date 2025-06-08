gnuplot hybridSOM-cn2_iris_gnuplot_generalization.plot
latex hybridSOM-cn2_iris_generalization.tex
dvips -E hybridSOM-cn2_iris_generalization.dvi
gnuplot hybridSOM-cn2_iris_gnuplot_conditions.plot
latex hybridSOM-cn2_iris_conditions.tex
dvips -E hybridSOM-cn2_iris_conditions.dvi
mv hybridSOM-cn2_iris_generalization.ps hybridSOM-cn2_iris_generalization.eps
mv hybridSOM-cn2_iris_conditions.ps hybridSOM-cn2_iris_conditions.eps
latex sample.tex
dvips -f < sample.dvi > sample.ps
