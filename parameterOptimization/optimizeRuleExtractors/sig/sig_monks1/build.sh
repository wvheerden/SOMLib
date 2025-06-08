gnuplot sig_monks1_gnuplot_generalization.plot
latex sig_monks1_generalization.tex
dvips -E sig_monks1_generalization.dvi
gnuplot sig_monks1_gnuplot_conditions.plot
latex sig_monks1_conditions.tex
dvips -E sig_monks1_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps