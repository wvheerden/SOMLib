gnuplot cn2_monks3_gnuplot_generalization.plot
latex cn2_monks3_generalization.tex
dvips -E cn2_monks3_generalization.dvi
gnuplot cn2_monks3_gnuplot_conditions.plot
latex cn2_monks3_conditions.tex
dvips -E cn2_monks3_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps