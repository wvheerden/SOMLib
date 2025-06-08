gnuplot hybridSOM-cn2_monks1_gnuplot_generalization.plot
latex hybridSOM-cn2_monks1_generalization.tex
dvips -E hybridSOM-cn2_monks1_generalization.dvi
gnuplot hybridSOM-cn2_monks1_gnuplot_conditions.plot
latex hybridSOM-cn2_monks1_conditions.tex
dvips -E hybridSOM-cn2_monks1_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps