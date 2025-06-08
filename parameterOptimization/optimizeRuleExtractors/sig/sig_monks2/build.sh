gnuplot sig_monks2_gnuplot_generalization.plot
latex sig_monks2_generalization.tex
dvips -E sig_monks2_generalization.dvi
gnuplot sig_monks2_gnuplot_conditions.plot
latex sig_monks2_conditions.tex
dvips -E sig_monks2_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps