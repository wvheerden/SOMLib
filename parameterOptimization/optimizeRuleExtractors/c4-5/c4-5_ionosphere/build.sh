gnuplot c4-5_ionosphere_gnuplot_generalization.plot
latex c4-5_ionosphere_generalization.tex
dvips -E c4-5_ionosphere_generalization.dvi
gnuplot c4-5_ionosphere_gnuplot_conditions.plot
latex c4-5_ionosphere_conditions.tex
dvips -E c4-5_ionosphere_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps