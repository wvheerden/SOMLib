gnuplot sig_monks3_gnuplot_generalization.plot
latex sig_monks3_generalization.tex
dvips -E sig_monks3_generalization.dvi
gnuplot sig_monks3_gnuplot_conditions.plot
latex sig_monks3_conditions.tex
dvips -E sig_monks3_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps