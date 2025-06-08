gnuplot hybridSOM-cn2_monks2_gnuplot_generalization.plot
latex hybridSOM-cn2_monks2_generalization.tex
dvips -E hybridSOM-cn2_monks2_generalization.dvi
gnuplot hybridSOM-cn2_monks2_gnuplot_conditions.plot
latex hybridSOM-cn2_monks2_conditions.tex
dvips -E hybridSOM-cn2_monks2_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps