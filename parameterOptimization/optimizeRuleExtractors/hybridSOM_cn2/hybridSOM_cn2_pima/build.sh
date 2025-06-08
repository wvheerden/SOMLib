gnuplot hybridSOM-cn2_pima_gnuplot_generalization.plot
latex hybridSOM-cn2_pima_generalization.tex
dvips -E hybridSOM-cn2_pima_generalization.dvi
gnuplot hybridSOM-cn2_pima_gnuplot_conditions.plot
latex hybridSOM-cn2_pima_conditions.tex
dvips -E hybridSOM-cn2_pima_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps