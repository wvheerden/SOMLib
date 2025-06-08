gnuplot cn2_monks2_gnuplot_generalization.plot
latex cn2_monks2_generalization.tex
dvips -E cn2_monks2_generalization.dvi
gnuplot cn2_monks2_gnuplot_conditions.plot
latex cn2_monks2_conditions.tex
dvips -E cn2_monks2_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps