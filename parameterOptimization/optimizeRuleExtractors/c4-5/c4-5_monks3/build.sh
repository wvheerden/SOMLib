gnuplot c4-5_monks3_gnuplot_generalization.plot
latex c4-5_monks3_generalization.tex
dvips -E c4-5_monks3_generalization.dvi
gnuplot c4-5_monks3_gnuplot_conditions.plot
latex c4-5_monks3_conditions.tex
dvips -E c4-5_monks3_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps