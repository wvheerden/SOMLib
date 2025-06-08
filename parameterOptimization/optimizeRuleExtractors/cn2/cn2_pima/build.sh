gnuplot cn2_pima_gnuplot_generalization.plot
latex cn2_pima_generalization.tex
dvips -E cn2_pima_generalization.dvi
gnuplot cn2_pima_gnuplot_conditions.plot
latex cn2_pima_conditions.tex
dvips -E cn2_pima_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps