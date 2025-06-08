gnuplot c4-5_monks2_gnuplot_generalization.plot
latex c4-5_monks2_generalization.tex
dvips -E c4-5_monks2_generalization.dvi
gnuplot c4-5_monks2_gnuplot_conditions.plot
latex c4-5_monks2_conditions.tex
dvips -E c4-5_monks2_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps