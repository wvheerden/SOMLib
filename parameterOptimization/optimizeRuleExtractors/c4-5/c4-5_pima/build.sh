gnuplot c4-5_pima_gnuplot_generalization.plot
latex c4-5_pima_generalization.tex
dvips -E c4-5_pima_generalization.dvi
gnuplot c4-5_pima_gnuplot_conditions.plot
latex c4-5_pima_conditions.tex
dvips -E c4-5_pima_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps