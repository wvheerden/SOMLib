gnuplot hybridSOM-c4-5_monks3_gnuplot_generalization.plot
latex hybridSOM-c4-5_monks3_generalization.tex
dvips -E hybridSOM-c4-5_monks3_generalization.dvi
gnuplot hybridSOM-c4-5_monks3_gnuplot_conditions.plot
latex hybridSOM-c4-5_monks3_conditions.tex
dvips -E hybridSOM-c4-5_monks3_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps