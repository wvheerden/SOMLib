gnuplot hybridSOM-c4-5_pima_gnuplot_generalization.plot
latex hybridSOM-c4-5_pima_generalization.tex
dvips -E hybridSOM-c4-5_pima_generalization.dvi
gnuplot hybridSOM-c4-5_pima_gnuplot_conditions.plot
latex hybridSOM-c4-5_pima_conditions.tex
dvips -E hybridSOM-c4-5_pima_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps