gnuplot sig_pima_gnuplot_generalization.plot
latex sig_pima_generalization.tex
dvips -E sig_pima_generalization.dvi
gnuplot sig_pima_gnuplot_conditions.plot
latex sig_pima_conditions.tex
dvips -E sig_pima_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps