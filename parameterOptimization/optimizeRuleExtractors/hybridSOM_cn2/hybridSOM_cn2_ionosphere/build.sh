gnuplot hybridSOM-cn2_ionosphere_gnuplot_generalization.plot
latex hybridSOM-cn2_ionosphere_generalization.tex
dvips -E hybridSOM-cn2_ionosphere_generalization.dvi
gnuplot hybridSOM-cn2_ionosphere_gnuplot_conditions.plot
latex hybridSOM-cn2_ionosphere_conditions.tex
dvips -E hybridSOM-cn2_ionosphere_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps