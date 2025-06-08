gnuplot sig_ionosphere_gnuplot_generalization.plot
latex sig_ionosphere_generalization.tex
dvips -E sig_ionosphere_generalization.dvi
gnuplot sig_ionosphere_gnuplot_conditions.plot
latex sig_ionosphere_conditions.tex
dvips -E sig_ionosphere_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps