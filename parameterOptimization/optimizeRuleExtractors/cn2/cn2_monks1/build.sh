gnuplot cn2_monks1_gnuplot_generalization.plot
latex cn2_monks1_generalization.tex
dvips -E cn2_monks1_generalization.dvi
gnuplot cn2_monks1_gnuplot_conditions.plot
latex cn2_monks1_conditions.tex
dvips -E cn2_monks1_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps