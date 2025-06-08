gnuplot hybridSOM-c4-5_monks1_gnuplot_generalization.plot
latex hybridSOM-c4-5_monks1_generalization.tex
dvips -E hybridSOM-c4-5_monks1_generalization.dvi
gnuplot hybridSOM-c4-5_monks1_gnuplot_conditions.plot
latex hybridSOM-c4-5_monks1_conditions.tex
dvips -E hybridSOM-c4-5_monks1_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps