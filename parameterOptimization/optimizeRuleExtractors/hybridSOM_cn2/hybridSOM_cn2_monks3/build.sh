gnuplot hybridSOM-cn2_monks3_gnuplot_generalization.plot
latex hybridSOM-cn2_monks3_generalization.tex
dvips -E hybridSOM-cn2_monks3_generalization.dvi
gnuplot hybridSOM-cn2_monks3_gnuplot_conditions.plot
latex hybridSOM-cn2_monks3_conditions.tex
dvips -E hybridSOM-cn2_monks3_conditions.dvi
latex sample.tex
dvips -f < sample.dvi > sample.ps