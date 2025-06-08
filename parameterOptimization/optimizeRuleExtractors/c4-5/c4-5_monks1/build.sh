gnuplot c4-5_monks1_gnuplot_generalization.plot
latex c4-5_monks1_generalization.tex
dvips -E c4-5_monks1_generalization.dvi
gnuplot c4-5_monks1_gnuplot_conditions.plot
latex c4-5_monks1_conditions.tex
dvips -E c4-5_monks1_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps