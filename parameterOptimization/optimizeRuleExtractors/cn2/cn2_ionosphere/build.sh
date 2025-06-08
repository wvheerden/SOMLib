gnuplot cn2_ionosphere_gnuplot_generalization.plot
latex cn2_ionosphere_generalization.tex
dvips -E cn2_ionosphere_generalization.dvi
gnuplot cn2_ionosphere_gnuplot_conditions.plot
latex cn2_ionosphere_conditions.tex
dvips -E cn2_ionosphere_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps